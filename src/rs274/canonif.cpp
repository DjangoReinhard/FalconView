#include <canon.hh>
#ifdef toLine
#undef toLine
#endif
#include <canonif.h>
#include <tooltable.h>
#include <lcproperties.h>
#include <AIS_Shape.hxx>
#include <gce_MakeDir.hxx>
#include <QDebug>


CanonIF::CanonIF(LcProperties& properties, ToolTable& toolTable) {
  if (instance) throw std::runtime_error("already initialized canon settings!");
  instance = new IFSettings(properties, toolTable);
  }


CanonIF::CanonIF() {
  if (!instance) throw std::runtime_error("wrong call sequence - canon NOT initialized!");
  }


CanonIF::IFSettings::IFSettings(LcProperties& lcProperties, ToolTable& toolTable)
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
  axisPresent = AxisMask(properties.value("AXIS_X", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_Y", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_Z", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_A", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_B", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_C", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_U", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_V", "MAX_VELOCITY").toBool()
                       , properties.value("AXIS_W", "MAX_VELOCITY").toBool());
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
     CANON_POSITION ep = canon.endPoint;

     qDebug() << "CIF: restore current position from last shutdown ... "
              << " -> " << ep.x << "/" << ep.y << "/" << ep.z
              << "\t" << ep.a << "/" << ep.b << "/" << ep.c
              << "\t" << ep.u << "/" << ep.v << "/" << ep.w;
     }
  }

double CanonIF::IFSettings::lengthUnits() const {
  return 1;
  }


int CanonIF::IFSettings::axisMask() const {
  return axisPresent.mask();
  }


void CanonIF::IFSettings::setG5xOffset(int i, const CANON_POSITION &p) {
  if (i < 0)      i = 0;
  else if (i > 8) i = 8;
  g5xOffsets[i] = p;
  }


CANON_DIRECTION CanonIF::IFSettings::spindleDir(int spindle) const {
  if (spindle < 0)                        spindle = 0;
  else if (spindle > EMCMOT_MAX_SPINDLES) spindle = EMCMOT_MAX_SPINDLES - 1;
  return static_cast<CANON_DIRECTION>(canon.spindle[spindle].dir);
  }


double CanonIF::IFSettings::spindleSpeed(int spindle) const {
  if (spindle < 0)                        spindle = 0;
  else if (spindle > EMCMOT_MAX_SPINDLES) spindle = EMCMOT_MAX_SPINDLES - 1;
  return canon.spindle[spindle].speed;
  }


CANON_TOOL_TABLE CanonIF::IFSettings::toolEntry(int ttIndex) const {
  return toolTable.current().toCanon();
  }


void CanonIF::IFSettings::changeTool(int slot) {
  qDebug() << "CIF: change tool to slot #" << slot;
  }


void CanonIF::IFSettings::setEndPoint(const CANON_POSITION &p) {
  canon.endPoint = p;
  }

void CanonIF::IFSettings::setTraverseColor(const QColor &c) {
  }

void CanonIF::IFSettings::setFeedColor(const QColor &c) {
  }

void CanonIF::IFSettings::setLimitsColor(const QColor &c) {
  }

void CanonIF::IFSettings::setMotionMode(CANON_MOTION_MODE mode, double tolerance) {
  canon.motionMode      = mode;
  }

CanonIF::IFSettings* CanonIF::instance = nullptr;

void INIT_CANON() {
  qDebug() << "NCanon: init Canon() ...";
  }

CANON_UNITS GET_EXTERNAL_LENGTH_UNIT_TYPE() {
  qDebug() << "NCanon: machine units (" << CanonIF().machineUnits() << ") ...";
  return CanonIF().machineUnits();
  }

double GET_EXTERNAL_LENGTH_UNITS() {
  return CanonIF().lengthUnits();
  }

double GET_EXTERNAL_ANGLE_UNITS() {
  return 1.0;
  }

void SET_G5X_OFFSET(int fixture, double x, double y, double z, double a, double b, double c, double u, double v, double w) {
  qDebug() << "NCanon: set G5x offset #" << fixture
           << " -> " << x << "/" << y << "/" << z
           << "\t" << a << "/" << b << "/" << c
           << "\t" << u << "/" << v << "/" << w;
  }

void SET_G92_OFFSET(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
  qDebug() << "NCanon: set G92 offset "
           << " -> " << x << "/" << y << "/" << z
           << "\t" << a << "/" << b << "/" << c
           << "\t" << u << "/" << v << "/" << w;
  }

void SET_XY_ROTATION(double t) {
  qDebug() << "NCanon: set XY-Rotation to " << t;
  }

int GET_EXTERNAL_AXIS_MASK() {
  return CanonIF().axisMask();
  }

double GET_EXTERNAL_POSITION_A() {
  return CanonIF().posA();
  }

double GET_EXTERNAL_POSITION_B() {
  return CanonIF().posB();
  }

double GET_EXTERNAL_POSITION_C() {
  return CanonIF().posC();
  }

double GET_EXTERNAL_POSITION_X() {
  return CanonIF().posX();
  }

double GET_EXTERNAL_POSITION_Y() {
  return CanonIF().posY();
  }

double GET_EXTERNAL_POSITION_Z() {
  return CanonIF().posZ();
  }

double GET_EXTERNAL_POSITION_U() {
  return CanonIF().posU();
  }

double GET_EXTERNAL_POSITION_V() {
  return CanonIF().posV();
  }

double GET_EXTERNAL_POSITION_W() {
  return CanonIF().posW();
  }

CANON_MOTION_MODE GET_EXTERNAL_MOTION_CONTROL_MODE() {
  return CanonIF().motionMode();
  }

double GET_EXTERNAL_MOTION_CONTROL_TOLERANCE() {
  return CanonIF().motionTolerance();
  }

double GET_EXTERNAL_MOTION_CONTROL_NAIVECAM_TOLERANCE() {
  return CanonIF().naiveTolerance();
  }

int GET_EXTERNAL_TOOL_SLOT() {
  qDebug() << "NCanon: get external Tool-Slot for tool in spindle";
  return 0;
  }

int GET_EXTERNAL_SELECTED_TOOL_SLOT() {
  return 0;
  }

double GET_EXTERNAL_FEED_RATE() {
  return CanonIF().feedRate();
  }

int GET_EXTERNAL_FLOOD() {
  return CanonIF().isFloodActive();
  }

int GET_EXTERNAL_MIST() {
  return CanonIF().isMistActive();
  }

CANON_PLANE GET_EXTERNAL_PLANE() {
  return CanonIF().activePlane();
  }

double GET_EXTERNAL_TRAVERSE_RATE() {
  return CanonIF().traverseRate();
  }

int GET_EXTERNAL_FEED_OVERRIDE_ENABLE() {
  return CanonIF().isFeedOverrideEnabled();
  }

int GET_EXTERNAL_SPINDLE_OVERRIDE_ENABLE(int spindle) {
  return CanonIF().isSpeedOverrideEnabled(spindle);
  }

int GET_EXTERNAL_ADAPTIVE_FEED_ENABLE() {
  return CanonIF().isAdaptiveFeedEnabled();
  }

int GET_EXTERNAL_FEED_HOLD_ENABLE() {
  return CanonIF().isFeedHoldActive();
  }

double GET_EXTERNAL_SPEED(int spindle) {
  return CanonIF().spindleSpeed(spindle);
  }

CANON_DIRECTION GET_EXTERNAL_SPINDLE(int spindle) {
  return CanonIF().spindleDir(spindle);
  }

CANON_TOOL_TABLE GET_EXTERNAL_TOOL_TABLE(int ttIndex) {
  qDebug() << "NCanon: get external tool table entry #" << ttIndex << " (msg limited to 10)";
  return CanonIF().toolEntry(ttIndex);
  }

int GET_EXTERNAL_TC_FAULT() {
  return 0;
  }

int GET_EXTERNAL_TC_REASON() {
  return 0;
  }

void ON_RESET(void) {
  }

void UPDATE_TAG(StateTag) {
//  qDebug() << "NCanon: NO update tag  ...";
  }

double GET_EXTERNAL_TOOL_LENGTH_XOFFSET() {
  return CanonIF().toolOffset().x;
  }

double GET_EXTERNAL_TOOL_LENGTH_YOFFSET() {
  return CanonIF().toolOffset().y;
  }

double GET_EXTERNAL_TOOL_LENGTH_ZOFFSET() {
  qDebug() << "NCanon: get external tool length Z-offset: " << CanonIF().toolOffset().z;

  return CanonIF().toolOffset().z;
  }

double GET_EXTERNAL_TOOL_LENGTH_AOFFSET() {
  return CanonIF().toolOffset().a;
  }

double GET_EXTERNAL_TOOL_LENGTH_BOFFSET() {
  return CanonIF().toolOffset().b;
  }

double GET_EXTERNAL_TOOL_LENGTH_COFFSET() {
  return CanonIF().toolOffset().c;
  }

double GET_EXTERNAL_TOOL_LENGTH_UOFFSET() {
  return CanonIF().toolOffset().u;
  }

double GET_EXTERNAL_TOOL_LENGTH_VOFFSET() {
  return CanonIF().toolOffset().v;
  }

double GET_EXTERNAL_TOOL_LENGTH_WOFFSET() {
  return CanonIF().toolOffset().w;
  }

void COMMENT(const char*) {
//  qDebug() << "NCanon: comment <" << s << "> ...";
  }

void USE_TOOL_LENGTH_OFFSET(EmcPose offset) {
  qDebug() << "NCanon: use tool length offset = " << offset.tran.z;
  CanonIF().setToolOffset(offset);
  }

void SET_SPINDLE_MODE(int spindle, double mode) {
  CanonIF().setSpindleMode(spindle, mode);
  }

void START_SPINDLE_CLOCKWISE(int, int ) {
  }

void START_SPINDLE_COUNTERCLOCKWISE(int, int) {
  }

void SET_SPINDLE_SPEED(int, double) {
  }

void STOP_SPINDLE_TURNING(int) {
  }

void MIST_OFF() {
  }

void MIST_ON() {
  }

void FLOOD_OFF() {
  }

void FLOOD_ON() {
  }

void USE_LENGTH_UNITS(CANON_UNITS u) {
  qDebug() << "NCanon: use length units (" << u << ") ...";
  CanonIF().setLengthUnits(u);
  }

void SELECT_TOOL(int toolNum) {
  qDebug() << "NCanon: select tool #" << toolNum;
  CanonIF().selectTool(toolNum);
  }

void CHANGE_TOOL(int slot) {
  qDebug() << "NCanon: change tool to slot" << slot;
  CanonIF().changeTool(slot);
  }

void CHANGE_TOOL_NUMBER(int number) {
  qDebug() << "NCanon: change tool number to #" << number << " ...";
  }

void START_CHANGE(void) {
  qDebug() << "NCanon: start change ...";
  }

void SELECT_PLANE(CANON_PLANE pl) {
  qDebug() << "NCanon:: select plane #" << pl;

  CanonIF().selectPlane(pl);
  }


void STRAIGHT_TRAVERSE(int lineno, double x, double y, double z
                                 , double a, double b, double c
                                 , double u, double v, double w) {
  qDebug() << QString("NCanon: rapid move #%1  -  (%2/%3/%4) -> (%5/%6/%7)")
                     .arg(lineno)
                     .arg(x, 0, 'f', 3)
                     .arg(y, 0, 'f', 3)
                     .arg(z, 0, 'f', 3)
                     .arg(a, 0, 'f', 3)
                     .arg(b, 0, 'f', 3)
                     .arg(c, 0, 'f', 3)
                     .toStdString().c_str();
  }


void ARC_FEED(int lineno, double first_end, double second_end, double first_axis
                        , double second_axis, int rotation, double axis_end_point
                        , double a, double b, double c, double u, double v, double w) {
    qDebug() << QString("NCanon: arc move #%1  -  (%2/%3/%4) -> (%5/%6/%7) CENTER (%8/%9/%10)")
                       .arg(lineno)
                       .arg(first_end, 0, 'f', 3)
                       .arg(second_end, 0, 'f', 3)
                       .arg(first_axis, 0, 'f', 3)
                       .arg(second_axis, 0, 'f', 3)
                       .arg(axis_end_point, 0, 'f', 3)
                       .arg(a, 0, 'f', 3)
                       .arg(b, 0, 'f', 3)
                       .arg(c, 0, 'f', 3)
                       .arg(u, 0, 'f', 3)
                       .toStdString().c_str();
  }


void STRAIGHT_FEED(int lineno, double x, double y, double z
                             , double a, double b, double c
                             , double u, double v, double w) {
  qDebug() << QString("NCanon: feed move #%1  -  (%2/%3/%4) -> (%5/%6/%7)")
                     .arg(lineno)
                     .arg(x, 0, 'f', 3)
                     .arg(y, 0, 'f', 3)
                     .arg(z, 0, 'f', 3)
                     .arg(x, 0, 'f', 3)
                     .arg(y, 0, 'f', 3)
                     .arg(z, 0, 'f', 3)
                     .toStdString().c_str();
  }


void CANON_UPDATE_END_POINT(double x, double y, double z, double a, double b, double c, double u, double v, double w) {    
  qDebug() << "Canon: update end point: " << x << "/" << y << "/" << z
                                  << "  " << a << "/" << b << "/" << c
                                  << "  " << u << "/" << v << "/" << w;
  CanonIF().setEndPoint(x, y, z, a, b, c, u, v, w);
  }

void SET_TRAVERSE_RATE(double r) {
  }

void SET_FEED_RATE(double rate) {
  }

void SET_FEED_REFERENCE(CANON_FEED_REFERENCE reference) {
  }

void SET_FEED_MODE(int spindle, int mode) {
  }

void SET_MOTION_CONTROL_MODE(CANON_MOTION_MODE mode, double tolerance) {
  }

void SET_NAIVECAM_TOLERANCE(double tolerance) {
  }

void SET_CUTTER_RADIUS_COMPENSATION(double radius) {
  qDebug() << "NCanon: set cutter radius compensation of R" << radius;
  }

void START_CUTTER_RADIUS_COMPENSATION(int direction) {
  qDebug() << "NCanon: start cutter radius compensation with direction " << direction;
  }

void STOP_CUTTER_RADIUS_COMPENSATION() {
  qDebug() << "NCanon: stop cutter radius compensation";
  }

void START_SPEED_FEED_SYNCH(int spindle, double feed_per_revolution, bool velocity_mode) {
  qDebug() << " NCanon: start speed feed synch ...";
  }

void STOP_SPEED_FEED_SYNCH() {
  qDebug() << "NCanon: stop speed feed synch ...";
  }

void NURBS_FEED(int lineno, std::vector<CONTROL_POINT> nurbs_control_points, unsigned int k) {
  qDebug() << "NCanon: nurbs feed - begin ...";
  }


void RIGID_TAP(int lineno, double x, double y, double z, double scale) {
  CANON_POSITION ep = CanonIF().endPoint();

  qDebug() << "NCanon: rigid tap - TODO!!! ...";
  ep.x = x;
  ep.y = y;
  ep.z = z;

  CanonIF().setEndPoint(ep.x, ep.y, ep.z, ep.a, ep.b, ep.c, ep.u, ep.v, ep.z);
  }

void STRAIGHT_PROBE(int lineno, double x, double y, double z, double a, double b, double c, double u, double v, double w, unsigned char probe_type) {
  qDebug() << "NCanon: straight probe ...";
  }

void STOP() {
  qDebug() << "NCanon: stop ...";
  }

void DWELL(double seconds) {
  qDebug() << "NCanon: dwell ..." << seconds << "seconds";
  }

void SPINDLE_RETRACT_TRAVERSE() {
  qDebug() << "NCanon: spindle retract traverse ...";
  }

void SPINDLE_RETRACT() {
  qDebug() << "NCanon: spindle retract ...";
  }

void ORIENT_SPINDLE(int, double, int) {
  qDebug() << "NCanon: orient spindle ...";
  }

void WAIT_SPINDLE_ORIENT_COMPLETE(int, double) {
  qDebug() << "NCanon: wait spindle orient complete ...";
  }

void LOCK_SPINDLE_Z() {
  qDebug() << "NCanon: lock spindle Z ...";
  }

void USE_SPINDLE_FORCE() {
  qDebug() << "NCanon: use spindle force ...";
  }

void USE_NO_SPINDLE_FORCE() {
  qDebug() << "NCanon: use no spindle force ...";
  }

void SET_TOOL_TABLE_ENTRY(int pocket, int toolno, EmcPose offset, double diameter,
                          double frontangle, double backangle, int orientation) {
  qDebug() << "NCanon: CHANGE tooltable entry ??? : " << toolno << " p" << pocket;
  }

void CLAMP_AXIS(CANON_AXIS) {
  qDebug() << "NCanon: clamp axis ...";
  }

void DISABLE_ADAPTIVE_FEED() {
  qDebug() << "NCanon: disable adaptive feed ...";
  }

void ENABLE_ADAPTIVE_FEED() {
  qDebug() << "NCanon: enable adaptive feed ...";
  }

void DISABLE_FEED_OVERRIDE() {
  qDebug() << "NCanon: disable feed override ...";
  }

void ENABLE_FEED_OVERRIDE() {
  qDebug() << "NCanon: enable feed override ...";
  }

void DISABLE_SPEED_OVERRIDE(int) {
  qDebug() << "NCanon: disable speed override ...";
  }

void ENABLE_SPEED_OVERRIDE(int) {
  qDebug() << "NCanon: enable speed override ...";
  }

void DISABLE_FEED_HOLD() {
  qDebug() << "NCanon: disable feed hold ...";
  }
void ENABLE_FEED_HOLD() {
  qDebug() << "NCanon: enable feed hold ...";
  }

void MESSAGE(char *s) {
  qDebug() << "NCanon: send message to client: " << s;
  }

void LOG(char *s) {
  qDebug() << "NCanon: log: >" << s << "< ...";
  }

void LOGOPEN(char *s) {
  qDebug() << "NCanon: log open (" << s << ") ...";
  }

void LOGAPPEND(char *s) {
  qDebug() << "NCanon: log append [" << s << "] ...";
  }

void LOGCLOSE() {
  qDebug() << "NCanon: log close ...";
  }

void PALLET_SHUTTLE() {
  qDebug() << "NCanon: pallet shuttle ...";
  }

void TURN_PROBE_OFF() {
  qDebug() << "NCanon: turn probe off ...";
  }
void TURN_PROBE_ON() {
  qDebug() << "NCanon: turn probe on ...";
  }

void UNCLAMP_AXIS(CANON_AXIS) {
  qDebug() << "NCanon: unclamp axis ...";
  }

void NURB_KNOT_VECTOR() {
  qDebug() << "NCanon: nurbs knot vector ...";
  }

void NURB_CONTROL_POINT(int i, double x, double y, double z,
                   double w) {
  qDebug() << "NCanon: nurbs control point #" << i << " (" << x << "/" << y << "/" << z << ") -> w: " << w << " ...";
  }

void NURB_FEED(double, double) {
  qDebug() << "NCanon: nurb feed ?!? ...";
  }

void SET_BLOCK_DELETE(bool enabled) {
  qDebug() << "NCanon: set block delete (" << (enabled ? "true" : "false") << ") ...";
  }

bool GET_BLOCK_DELETE(void) {
  qDebug() << "NCanon: get block delete ...";
  }

void OPTIONAL_PROGRAM_STOP() {
  qDebug() << "NCanon: optional program stop ...";
  }

void SET_OPTIONAL_PROGRAM_STOP(bool) {
  qDebug() << "NCanon: set optional program stop ...";
  }

bool GET_OPTIONAL_PROGRAM_STOP() {
  qDebug() << "NCanon: get optional program stop ...";
  }

void PROGRAM_END() {
  qDebug() << "NCanon: program end!";
  }

void PROGRAM_STOP() {
  qDebug() << "NCanon: program stop!";
  }

void SET_MOTION_OUTPUT_BIT(int) {
  qDebug() << "NCanon: set motion output bit ...";
  }

void CLEAR_MOTION_OUTPUT_BIT(int) {
  qDebug() << "NCanon: clear motion output bit ...";
  }

void SET_AUX_OUTPUT_BIT(int) {
  qDebug() << "NCanon: set aux output bit ...";
  }

void CLEAR_AUX_OUTPUT_BIT(int) {
  qDebug() << "NCanon: clear aux output bit ...";
  }

void SET_MOTION_OUTPUT_VALUE(int, double) {
  qDebug() << "NCanon: set motion output value ...";
  }

void SET_AUX_OUTPUT_VALUE(int, double) {
  qDebug() << "NCanon: set aux output value ...";
  }

int WAIT(int
       , int
       , int
       , double) {
  qDebug() << "NCanon: wait ...";
  }

int UNLOCK_ROTARY(int, int) {
  qDebug() << "NCanon: unlock rotary ...";
  }

int LOCK_ROTARY(int, int) {
  qDebug() << "NCanon: lock rotary ...";
  }

void GET_EXTERNAL_PARAMETER_FILE_NAME(char *filename, int max_size) {
  qDebug() << "NCanon: get external parameter file name ... (max size: " << max_size << ")";
  strncpy(filename, CanonIF().parameterFilename().toStdString().c_str(), max_size);
  }

void SET_PARAMETER_FILE_NAME(const char *name) {
  qDebug() << "NCanon: set parameter file name to <" << name << "> ...";
  }

double GET_EXTERNAL_PROBE_POSITION_A() {
  qDebug() << "NCanon: get external probe position A ...";
  }

double GET_EXTERNAL_PROBE_POSITION_B() {
  qDebug() << "NCanon: get external probe position B ...";
  }

double GET_EXTERNAL_PROBE_POSITION_C() {
  qDebug() << "NCanon: get external probe position C ...";
  }

double GET_EXTERNAL_PROBE_POSITION_X() {
  qDebug() << "NCanon: get external probe position X ...";
  }

double GET_EXTERNAL_PROBE_POSITION_Y() {
  qDebug() << "NCanon: get external probe position Y ...";
  }

double GET_EXTERNAL_PROBE_POSITION_Z() {
  qDebug() << "NCanon: get external probe position Z ...";
  }

double GET_EXTERNAL_PROBE_POSITION_U() {
  qDebug() << "NCanon: get external probe position U ...";
  }

double GET_EXTERNAL_PROBE_POSITION_V() {
  qDebug() << "NCanon: get external probe position V ...";
  }

double GET_EXTERNAL_PROBE_POSITION_W() {
  qDebug() << "NCanon: get external probe position W ...";
  }

double GET_EXTERNAL_PROBE_VALUE() {
  qDebug() << "NCanon: get external probe value ...";
  }

int GET_EXTERNAL_PROBE_TRIPPED_VALUE() {
  qDebug() << "NCanon: get external probe tripped value ...";
  }

int GET_EXTERNAL_QUEUE_EMPTY() {
  return 1;
  }

int GET_EXTERNAL_DIGITAL_INPUT(int, int) {
  qDebug() << "NCanon: get external digital input ...";
  }

double GET_EXTERNAL_ANALOG_INPUT(int, double) {
  qDebug() << "NCanon: get external analog input ...";
  }

USER_DEFINED_FUNCTION_TYPE USER_DEFINED_FUNCTION[USER_DEFINED_FUNCTION_NUM];

void FINISH(void) {
  qDebug() << "NCanon: finish ...";
  }

void CANON_ERROR(const char *, ...) {
  qDebug() << "NCanon: canon error  ...";
  }

void PLUGIN_CALL(int , const char *) {
  qDebug() << "NCanon: plugin call  ...";
  }

void IO_PLUGIN_CALL(int , const char *) {
  qDebug() << "NCanon: io plugin call ...";
  }

int GET_EXTERNAL_OFFSET_APPLIED() {
  qDebug() << "NCanon: get external offset applied ...";
  };

EmcPose GET_EXTERNAL_OFFSETS(){
  qDebug() << "NCanon: get external offsets ...";
  };
