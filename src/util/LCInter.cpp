#include <canon.hh>
#include <iostream>
#include <tooldata.hh>
#include <rs274ngc_interp.hh>
#include <emc_nml.hh>

#ifdef toLine
#undef toLine
#endif

#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QEventLoop>
#include <QTextStream>
#include <QProcess>
#include <QThread>
#include <QDir>
#include <QDebug>

#include <LCInter.h>
#include <lcproperties.h>
//#include <gcodewriter.h>
#include <tooltable.h>

//#define WANT_RAW

/**
 * this is junk that you have to define in exactly this way because of how mah
 * implemented the python "remap" functionality of the interpreter
 * (and it needs Python.h for the definition of struct inttab)
 */
int  _task = 0;

extern "C" PyObject* PyInit_interpreter(void);
extern "C" PyObject* PyInit_emccanon(void);
extern "C" struct _inittab builtin_modules[];
struct _inittab builtin_modules[] = {
    { "interpreter", PyInit_interpreter },
    { "emccanon", PyInit_emccanon },
    { NULL, NULL }
};


LCInterface::LCInterface(LcProperties& lcProps, ToolTable& tt)
 : pInter(nullptr)
 , lcProperties(lcProps)
 , toolTable(tt)
 , lastSeqNum(-1)
 , emcStatus(nullptr)
 , toolStatus(new EMC_TOOL_STAT)
 , xLast(0)
 , yLast(0)
 , zLast(0) {
  tool_mmap_creator(toolStatus, true);
  }


LCInterface::~LCInterface() {
  delete toolStatus;
  }


void LCInterface::maybeNewLine() {
  if (!pInter) return;
  maybeNewLine(pInter->sequence_number());
  }


void LCInterface::maybeNewLine(int seqNum) {
  if (!pInter)              return;
  if (errInter)             return;
  if (seqNum == lastSeqNum) return;

  lineCodes.reset();
  pInter->active_settings(lineCodes.settings);
  pInter->active_g_codes(lineCodes.gCodes);
  pInter->active_m_codes(lineCodes.mCodes);
  lineCodes.gCodes[0] = seqNum;
  lastSeqNum = seqNum;
  }


void LCInterface::parseInline(const QString& fileName) {
  int rv = -1;
  QString msg = QString("Error #") + QString::number(rv) + " - failed to create interpreter!";

  if (!pInter) pInter = makeInterp();
  for (;;) {
      if (!pInter) break;
      pInter->init();
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
      if ((rv = pInter->open(fileName.toStdString().c_str()))) break;
      maybeNewLine();
      QString     initCodes = lcProperties.value("RS274NGC", "RS274NGC_STARTUP_CODE").toString();
      QString     unit      = lcProperties.value("TRAJ", "LINEAR_UNITS").toString();
      QString     unitCode  = QString("G2") + ((!unit.compare("mm") || !unit.compare("cm")) ? "1" : "0");
      QStringList codes     = initCodes.split(QRegularExpression("\\s+"));

      codes.append(unitCode);
      for (int i=0; i < codes.size(); ++i) {
          QString code = codes.at(i);

          qDebug() << "init code: <|" << code << "|>";
          if ((rv = readExec(code))) break;
          }
      if (rv > INTERP_MIN_ERROR) {
         msg = QString("Error #") + QString::number(rv) + " - failed to interpret init codes";
         break;
         }
      int lineNumber;

      while (1) {
            if ((rv = pInter->read())) break;
            lineNumber = pInter->line();
            rv = pInter->execute();

            if (!(!rv || rv == 2)) break;
            }
      if (rv > INTERP_MIN_ERROR) {
         msg = QString("Error #") + QString::number(rv)
                     + " - interpreter failed to execute line "
                     + QString::number(lineCodes.gCodes[0])
                     + " (" + QString::number(lineNumber) + ")";
         }
      pInter->close();
      return;
      }
  std::cerr << msg.toStdString().c_str() << std::endl;
  }


int LCInterface::readExec(const QString &line) {
  int result = pInter->read(line.toLatin1());

  if (result > INTERP_MIN_ERROR) {
     std::cerr << "IC Error #" << result << " - failed to read line \"" << line.toStdString().c_str() << "\"" << std::endl;

     return result;
     }
  result = pInter->execute();
  if (result > INTERP_MIN_ERROR) {
     std::cerr << "IC Error #" << result << " - failed to execute line \"" << line.toStdString().c_str() << "\"" << std::endl;

     return result;
     }
  return result;
  }


void LCInterface::setupToolTable() {
  for (const ToolEntry* te : toolTable) {
      tooldata_put(te->toCanon(), te->lineNum());
      }
  }


#ifndef USE_INTERNAL_INTERPRETER
void LCInterface::parseExt(const QString &fileName) {
  const char* lcHome = getenv("EMC2_HOME");

  if (!lcHome) {
     qDebug() << "OUPS - EMC2_HOME not found in environment!";

     return;
     }
  QDir      baseDir(lcHome);

  if (!baseDir.exists()) {
     qDebug() << "OUPS - EMC2_HOME invalid!";

     return;
     }
  QFile       cmd(QString(baseDir.path() + "/bin/rs274"));

  if (!cmd.exists()) {
     qDebug() << "OUPS - interpreter executable (rs274) NOT found!";

     return;
     }
  child = new QProcess();
  QString      initCodes = lcProperties.value("RS274NGC", "RS274NGC_STARTUP_CODE").toString();
  QString      unit      = lcProperties.value("TRAJ", "LINEAR_UNITS").toString();
  QThread*     thread    = new QThread;
  GCodeWriter* writer    = new GCodeWriter(fileName, initCodes, unit, child);

  writer->moveToThread(thread);

  connect(writer, SIGNAL(error(const QString&)), this,   SLOT(errorString(const QString&)));
  connect(thread, SIGNAL(started()),             writer, SLOT(process()));
  connect(writer, SIGNAL(finished()),            thread, SLOT(quit()));
  connect(writer, SIGNAL(finished()),            writer, SLOT(deleteLater()));
  connect(thread, SIGNAL(finished()),            thread, SLOT(deleteLater()));

  QFileInfo   iniFN(lcProperties.fileName());
  QString     varFN = iniFN.absoluteDir().path() + "/" + lcProperties.value("RS274NGC", "PARAMETER_FILE").toString();
  QStringList args;

  args.append("-g");
  args.append("-v");
  args.append(varFN);
  args.append("-i");
  args.append(iniFN.absoluteFilePath());
  args.append("-t");
  args.append(toolTable.fileName());
  args.append("-n");
  args.append("0");

  qDebug() << "exec: " << cmd.fileName() << " with args: " << args;

  child->setReadChannel(QProcess::ProcessChannel::StandardOutput);
  child->start(cmd.fileName(), args, QProcess::Unbuffered | QProcess::ReadWrite);
  thread->start();
  QString line;

  while (child->waitForReadyRead()) {
        while (child->canReadLine()) {
              line = child->readLine().trimmed();              
              if (line.startsWith("READ")) continue;
#ifdef WANT_RAW
              qDebug() << "raw line: " << line;
#else
              QStringList parts    = line.split(QRegularExpression("\\s+"));
              long        sequence = parts.takeAt(0).toInt();
              long        lineNum  = parts.takeAt(0).mid(1).toInt();

              line = parts.join(" ");

              if (line.startsWith("COMMENT(")) continue;
              if (line.startsWith("PROGRAM_END")) {
                 qDebug() << "this is the end!";

                 return;
                 }
              processLine(sequence, lineNum, line);
#endif
              }
        }
  }


void LCInterface::errorString(const QString& msg) {
  std::cerr << "error from thread: " << msg.toStdString().c_str() << std::endl;
  }


void LCInterface::processLine(long sequence, long lineNum, const QString& line) {
  QStringList   parts = line.split(QRegularExpression("(,\\s+)|\\("));
  QList<double> args;
  bool          ok;

  if (line.startsWith("STRAIGHT_TRAVERSE")) {
     // G0
     // STRAIGHT_TRAVERSE(78.1207, 11.8044, 3.0000, 0.0000, 0.0000, 0.0000)
     qDebug() << "G0 - seq #" << sequence << " line #" << lineNum << " : " << line;
     double v;

     for (int i=1; i < parts.size(); ++i) {
         v = parts.at(i).toDouble(&ok);

         if (ok) args.append(v);
         else    args.append(0.0);
         }
     for (double n : args) {
         qDebug() << "G0 args: " << n;
         }
     xLast = args.at(0);
     yLast = args.at(1);
     zLast = args.at(2);
     }
  else if (line.startsWith("STRAIGHT_FEED")) {
     // G1
     // STRAIGHT_FEED(92.1016, 14.0078, -2.0000, 0.0000, 0.0000, 0.0000)
     qDebug() << "G1 - seq #" << sequence << " line #" << lineNum << " : " << line;
     double v;

     for (int i=1; i < parts.size(); ++i) {
         v = parts.at(i).toDouble(&ok);

         if (ok) args.append(v);
         else    args.append(0.0);
         }
     for (double n : args) {
         qDebug() << "G1 args: " << n;
         }
     xLast = args.at(0);
     yLast = args.at(1);
     zLast = args.at(2);
     }
  else if (line.startsWith("ARC_FEED")) {
     // G2             end             center       cw     z?
     // ARC_FEED(93.5637, 4.2311, 83.1274, 11.2647, -1, -2.0000, 0.0000, 0.0000, 0.0000)
     //
     // G3             end             center      ccw     z?
     // ARC_FEED(90.0790, 6.0293, 85.6158, 8.7523,   1, -2.0000, 0.0000, 0.0000, 0.0000)
     qDebug() << "G2/G3 - seq #" << sequence << " line #" << lineNum << " : " << line;
     double v;

     for (int i=1; i < parts.size(); ++i) {
         v = parts.at(i).toDouble(&ok);

         if (ok) args.append(v);
         else    args.append(0.0);
         }
     for (double n : args) {
         qDebug() << "ARC args: " << n;
         }
     xLast = args.at(0);
     yLast = args.at(1);
     zLast = args.at(5);
     }
  else if (line.startsWith("NURBS_FEED")) {
     qDebug() << "can't support nurbs using external interpreter!";
     }
  else {
     qDebug() << "unsupported - seq #" << sequence << " line #" << lineNum << " : " << line;
     }
  }
#endif
