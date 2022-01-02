#include <tooltable.h>
#include <toolentry.h>
#include <canonifsettings.h>


CanonIFSettings::CanonIFSettings(LcProperties& lcProperties, ToolTable& toolTable)
 : properties(lcProperties)
 , toolTable(toolTable) {
  QString lu  = properties.value("TRAJ", "LINEAR_UNITS").toString();
  QString pfn = properties.value("TRAJ", "POSITION_FILE").toString();
  QFile   pf  = QFile(properties.baseDir() + "/" + pfn);

  if (!lu.compare("mm"))      machineUnits = CANON_UNITS_MM;
  else if (!lu.compare("cm")) machineUnits = CANON_UNITS_CM;
  else                        machineUnits = CANON_UNITS_INCHES;
  canon.lengthUnits = machineUnits;
  canon.activePlane = CANON_PLANE_XY;
  canon.motionMode  = CANON_EXACT_PATH;
  canon.motionTolerance   = 0.01;
  canon.naivecamTolerance = 0.01;
  canon.feed_mode         = CANON_SYNCHED;
  iTraverseRate = properties.value("AXIS_X", "MAX_VELOCITY").toDouble();
  canon.linearFeedRate = iTraverseRate / 4;

  if (pf.open(QIODevice::ReadOnly | QIODevice::Text)) {
     QTextStream in(&pf);
     QString line = in.readLine();
     double  dv;
     bool    ok;

     for (int i=0; !line.isNull(); ++i, line=in.readLine()) {
         dv = line.toDouble(&ok);

         if (ok) {
            if (dv < 0.0001) dv = 0;
            switch (i) {
              case 0: canon.endPoint.x = dv; break;
              case 1: canon.endPoint.y = dv; break;
              case 2: canon.endPoint.z = dv; break;
              case 3: canon.endPoint.a = dv; break;
              case 4: canon.endPoint.b = dv; break;
              case 5: canon.endPoint.c = dv; break;
              case 6: canon.endPoint.u = dv; break;
              case 7: canon.endPoint.v = dv; break;
              case 8: canon.endPoint.w = dv; break;
              default: break;
              }
            }
         }
     pf.close();
     }
  }


/**
 * @brief CanonIF::IFSettings::lengthUnits
 * @return factor to convert jobUnits into machineUnits
 */
double CanonIFSettings::lengthUnits() const {
   switch (machineUnits) {
     case CANON_UNITS_CM:
          switch (canon.lengthUnits) {
            case CANON_UNITS_CM: return 1;
            case CANON_UNITS_MM: return 10;
            default:             return 2.54;
            } break;
     case CANON_UNITS_MM:
          switch (canon.lengthUnits) {
            case CANON_UNITS_CM: return 0.1;
            case CANON_UNITS_MM: return 1;
            default:             return 25.4;
            } break;
     default:
          switch (canon.lengthUnits) {
            case CANON_UNITS_CM: return 1/2.54;
            case CANON_UNITS_MM: return 1/25.4;
            default:             return 1;
            } break;
     }
  }


void CanonIFSettings::setG5xOffset(int i, const CANON_POSITION &p) {
  if (i < 0)      i = 0;
  else if (i > 8) i = 8;
  selectedOffset    = i;
  g5xOffsets[i] = p;
  }


CANON_POSITION CanonIFSettings::g5xOffset(int i) const {
  if (i < 0)      i = 0;
  else if (i > 8) i = 8;
  return g5xOffsets[i];
  }


CANON_DIRECTION CanonIFSettings::spindleDir(int spindle) const {
  if (spindle < 0)                        spindle = 0;
  else if (spindle > EMCMOT_MAX_SPINDLES) spindle = EMCMOT_MAX_SPINDLES - 1;
  return static_cast<CANON_DIRECTION>(canon.spindle[spindle].dir);
  }


double CanonIFSettings::spindleSpeed(int spindle) const {
  if (spindle < 0)                        spindle = 0;
  else if (spindle > EMCMOT_MAX_SPINDLES) spindle = EMCMOT_MAX_SPINDLES - 1;
  return canon.spindle[spindle].speed;
  }


CANON_TOOL_TABLE CanonIFSettings::toolEntry(int ttIndex) const {
  if (!ttIndex) return toolTable.current().toCanon();
  const ToolEntry* te = toolTable.tool(ttIndex);

  if (!te) return ToolEntry().toCanon();
  return te->toCanon();
  }


void CanonIFSettings::changeTool(int slot) {
  toolTable.setCurrent(slot);
  changer.setCurrentTool(slot);
  ToolEntry ct = toolTable.current();

  canon.toolOffset = ct.toCanon().offset;
  }


void CanonIFSettings::setEndPoint(const CANON_POSITION &p) {
  canon.endPoint = p;
  }


static Quantity_Color convertColor(const QColor& c) {
  return Quantity_Color((double)(c.red()   / 255.0)
                      , (double)(c.green() / 255.0)
                      , (double)(c.blue()  / 255.0), Quantity_TOC_RGB);
  }


void CanonIFSettings::setTraverseColor(const QColor &c) {
  colTraverse = convertColor(c);
  }


void CanonIFSettings::setFeedColor(const QColor &c) {
  colFeed = convertColor(c);
  }


void CanonIFSettings::setLimitsColor(const QColor &c) {
  colLimits = convertColor(c);
  }


void CanonIFSettings::setCurSegColor(const QColor &c) {
  colCurSeg = convertColor(c);
  }


void CanonIFSettings::setOldSegColor(const QColor &c) {
  colOldSeg = convertColor(c);
  }


void CanonIFSettings::setWorkPieceColor(const QColor &c) {
  colWorkPiece = convertColor(c);
  }


void CanonIFSettings::setMotionMode(CANON_MOTION_MODE mode, double) {
  canon.motionMode      = mode;
  }
