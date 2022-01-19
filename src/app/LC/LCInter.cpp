#include <rs274ngc_interp.hh>
#include <interp_base.hh>
#include <tooldata.hh>

#ifdef Log
# undef Log
#endif
#ifdef toLine
# undef toLine
#endif

#include <LCInter.h>
#include <lcproperties.h>
#include <tooltable.h>
#include <core.h>
#include <canonif.h>

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QEventLoop>
#include <QTextStream>
#include <QVector3D>
#include <QProcess>
#include <QThread>
#include <QDir>
#include <QDebug>

#include <iostream>


/**
 * this is junk that you have to define in exactly this way because of how mah
 * implemented the python "remap" functionality of the interpreter
 * (and it needs Python.h for the definition of struct inttab)
 */
int       _task = 0;
struct LineCodes
{
  LineCodes() { reset(); }

  void reset() {
    memset(settings, 0, sizeof(double) * ACTIVE_SETTINGS);
    memset(gCodes,   0, sizeof(int)    * ACTIVE_G_CODES);
    memset(mCodes,   0, sizeof(int)    * ACTIVE_M_CODES);
    }
  double settings[ACTIVE_SETTINGS];
  int    gCodes[ACTIVE_G_CODES];
  int    mCodes[ACTIVE_M_CODES];
  } lineCodes;
extern "C" PyObject* PyInit_interpreter(void);
extern "C" PyObject* PyInit_emccanon(void);
extern "C" struct _inittab builtin_modules[];
struct _inittab builtin_modules[] = {
    { "interpreter", PyInit_interpreter },
    { "emccanon",    PyInit_emccanon },
    { NULL, NULL }
};
/** end junk */

class LCInterfaceP
{
public:
  LCInterfaceP(CanonIF& cif, LcProperties& lcProps, ToolTable& tt)
    : pInter(nullptr)
    , canon(cif)
    , lcProperties(lcProps)
    , toolTable(tt)
    , lastSeqNum(-1)
    , emcStatus(nullptr)
    , toolStatus(new EMC_TOOL_STAT)
    , xLast(0)
    , yLast(0)
    , zLast(0) {
     }
  InterpBase*    pInter;
  CanonIF&       canon;
  LcProperties&  lcProperties;
  ToolTable&     toolTable;
  int            lastSeqNum;
  int            errInter;
  QProcess*      child;
  EMC_STAT*      emcStatus;
  EMC_TOOL_STAT* toolStatus;
  double         xLast;
  double         yLast;
  double         zLast;
  };


LCInterface::LCInterface(CanonIF& cif, LcProperties& lcProps, ToolTable& tt)
 : p(new LCInterfaceP(cif, lcProps, tt)) {
  assert(p);
  tool_mmap_creator(p->toolStatus, true);
  }


LCInterface::~LCInterface() {
  delete p;
  }


void LCInterface::maybeNewLine() {
  if (!p->pInter) return;
  maybeNewLine(p->pInter->sequence_number());
  }


void LCInterface::maybeNewLine(int seqNum) {
  if (!p->pInter)              return;
  if (p->errInter)             return;
  if (seqNum == p->lastSeqNum) return;

  lineCodes.reset();
  p->pInter->active_settings(lineCodes.settings);
  p->pInter->active_g_codes(lineCodes.gCodes);
  p->pInter->active_m_codes(lineCodes.mCodes);
  lineCodes.gCodes[0] = seqNum;
  p->lastSeqNum = seqNum;
  }


std::pair<QVector3D, QVector3D> LCInterface::machineLimits() const {
  CANON_POSITION g5xO = p->canon.g5xOffset(p->canon.selectedOffset());
  CANON_POSITION g92O = p->canon.g92Offset();
  double         rot  = p->canon.xyRotation();  //TODO!
  LcProperties&  lcp  = p->canon.lcProperties();

  qDebug() << "showLimits() - g5x:" << g5xO.x << "/" << g5xO.y << "/" << g5xO.z
           << "\tg92: " << g92O.x << "/" << g92O.y << "/" << g92O.z
           << "\trot: " << rot;
  QVector3D min(lcp.value("AXIS_X", "MIN_LIMIT").toDouble() - g5xO.x - g92O.x
              , lcp.value("AXIS_Y", "MIN_LIMIT").toDouble() - g5xO.y - g92O.y
              , lcp.value("AXIS_Z", "MIN_LIMIT").toDouble() - g5xO.z - g92O.z);
  QVector3D max(lcp.value("AXIS_X", "MAX_LIMIT").toDouble() - g5xO.x - g92O.x
              , lcp.value("AXIS_Y", "MAX_LIMIT").toDouble() - g5xO.y - g92O.y
              , lcp.value("AXIS_Z", "MAX_LIMIT").toDouble() - g5xO.z - g92O.z);

  return std::pair<QVector3D, QVector3D>(min, max);
  }


void LCInterface::parseInline(const QString& fileName) {
  int rv = -1;
  QString msg = tr("Error #%1 - failed to create interpreter!").arg(rv);

  if (!p->pInter) p->pInter = makeInterp();
  for (;;) {
      if (!p->pInter) break;
      p->pInter->init();
#ifdef TOOL_NML
      tool_nml_register( (CANON_TOOL_TABLE*)(&((Interp*)pInter)->_setup.tool_table));
      // check tool_table
      for (int i=0; i < 8; ++i) {
          qDebug() << i << ") tool-entry: #" << ((Interp*)pInter)->_setup.tool_table[i].toolno
                        << " slot: " << ((Interp*)pInter)->_setup.tool_table[i].pocketno
                        << " length: " << ((Interp*)pInter)->_setup.tool_table[i].offset.tran.z
                        << " dia: " << ((Interp*)pInter)->_setup.tool_table[i].diameter;
          }
#endif
      if ((rv = p->pInter->open(fileName.toStdString().c_str()))) break;
      maybeNewLine();
      QString     initCodes = p->lcProperties.value("RS274NGC", "RS274NGC_STARTUP_CODE").toString();
      QString     unit      = p->lcProperties.value("TRAJ", "LINEAR_UNITS").toString();
      QString     unitCode  = QString("G2") + ((!unit.compare("mm") || !unit.compare("cm")) ? "1" : "0");
      QStringList codes     = initCodes.split(QRegularExpression("\\s+"));

      codes.append(unitCode);
      for (int i=0; i < codes.size(); ++i) {
          QString code = codes.at(i);

          if ((rv = readExec(code))) break;
          }
      if (rv > INTERP_MIN_ERROR) {
         msg = tr("Error #%1 - failed to interpret init codes").arg(rv);
         break;
         }
      int lineNumber = -1;

      while (1) {
            if ((rv = p->pInter->read())) break;
            lineNumber = p->pInter->line();
            rv = p->pInter->execute();

            if (!(!rv || rv == 2)) break;
            }
      if (rv > INTERP_MIN_ERROR) {
         msg = tr("Error #%1 - interpreter failed to execute line %2 (%3)")
                 .arg(rv)
                 .arg(lineCodes.gCodes[0])
                 .arg(lineNumber);
         break;
         }
      p->pInter->close();
      return;
      }
  if (p->pInter) p->pInter->close();
  Core().riseError(msg);
  }


int LCInterface::readExec(const QString &line) {
  int result = p->pInter->read(line.toLatin1());

  if (result > INTERP_MIN_ERROR) {
     Core().riseError(tr("Error #%1 - failed to read line \"%2\"")
                        .arg(result)
                        .arg(line));
     return result;
     }
  result = p->pInter->execute();
  if (result > INTERP_MIN_ERROR) {
     Core().riseError(tr("Error #%1 - failed to execute line \"%2\"")
                        .arg(result)
                        .arg(line));
     return result;
     }
  return result;
  }


void LCInterface::setupToolTable() {
  CANON_TOOL_TABLE ctt;

  for (const ToolEntry* te : p->toolTable) {
      te->toCanon(&ctt);
      tooldata_put(ctt, te->lineNum());
      }
  }
