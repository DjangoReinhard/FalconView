#ifdef REDNOSE
#include <Python.h> // must be first header
#include <QString>
//#include <QDebug>
#include <rs274ngc.hh>
#include <saicanon.hh>
#include <iostream>


/**
 * this is junk that you have to define in exactly this way because of how mah
 * implemented the python "remap" functionality of the interpreter
 * (and it needs Python.h for the definition of struct inttab)
 */
int  _task = 0;
char _parameter_file_name[PARAMETER_FILE_NAME_LENGTH];
//StandaloneInterpInternals _sai = StandaloneInterpInternals();

extern "C" PyObject* PyInit_emctask(void);
extern "C" PyObject* PyInit_interpreter(void);
extern "C" PyObject* PyInit_emccanon(void);
extern "C" struct _inittab builtin_modules[];
struct _inittab builtin_modules[] = {
    { "interpreter", PyInit_interpreter },
    { "emccanon", PyInit_emccanon },
    { NULL, NULL }
};

//dummy stuff to satisfy linker ?!?
void INIT_CANON() {
  std::cout << "init Canon() ..." << std::endl;
 }
void SET_G5X_OFFSET(int origin,
                           double x, double y, double z,
                           double a, double b, double c,
                           double u, double v, double w) {
  std::cout << "set G5X offset ..." << std::endl;
  }
void SET_G92_OFFSET(double x, double y, double z,
                           double a, double b, double c,
                           double u, double v, double w) {
  std::cout << "set G92 offset ..." << std::endl;
  }
void SET_XY_ROTATION(double t) {
  std::cout << "set XY rotation ..." << std::endl;
  }
void CANON_UPDATE_END_POINT(double x, double y, double z,
                   double a, double b, double c,
                   double u, double v, double w) {
  std::cout << "canon_update_end_point(" << x << "/" << y << "/" << z << ")" << std::endl;
  }
void USE_LENGTH_UNITS(CANON_UNITS u) {
  std::cout << "use length units ..." << std::endl;
  }
void SELECT_PLANE(CANON_PLANE pl) {}
void SET_TRAVERSE_RATE(double rate) {}
void STRAIGHT_TRAVERSE(int lineno,
                       double x, double y, double z,
                       double a, double b, double c,
                       double u, double v, double w) {
  std::cout << QString("FF>> -> %1/%2/%3").arg(x, 0, 'f', 3).arg(y, 0, 'f', 3).arg(z, 0, 'f', 3).toStdString().c_str() << std::endl;
  }
void SET_FEED_RATE(double rate) {
  std::cout << "set feed rate ..." << std::endl;
  }
void SET_FEED_REFERENCE(CANON_FEED_REFERENCE reference) {
  std::cout << " ..." << std::endl;
  }
void SET_FEED_MODE(int spindle, int mode) {
  std::cout << "set Feed Mode ..." << std::endl;
  }
void SET_MOTION_CONTROL_MODE(CANON_MOTION_MODE mode, double tolerance) {
  std::cout << "set motion control mode ..." << std::endl;
  }
void SET_NAIVECAM_TOLERANCE(double tolerance) {
  std::cout << " ..." << std::endl;
  }
void SET_CUTTER_RADIUS_COMPENSATION(double radius) {
  std::cout << "set cutter radius compensation of R" << radius << std::endl;
  }
void START_CUTTER_RADIUS_COMPENSATION(int direction) {
  std::cout << "start cutter radius compensation with direction " << direction << std::endl;
  }
void STOP_CUTTER_RADIUS_COMPENSATION() {
  std::cout << "stop cutter radius compensation" << std::endl;
  }
void START_SPEED_FEED_SYNCH(int spindle, double feed_per_revolution, bool velocity_mode) {
  std::cout << " start speed feed synch ..." << std::endl;
  }
void STOP_SPEED_FEED_SYNCH() {
  std::cout << "stop speed feed synch ..." << std::endl;
  }
void ARC_FEED(int lineno,
              double first_end, double second_end,
              double first_axis, double second_axis, int rotation,
              double axis_end_point,
              double a, double b, double c,
              double u, double v, double w) {
  std::cout << QString("arc -> %1/%2/%3").arg(first_end, 0, 'f', 3).arg(second_end, 0, 'f', 3).arg(axis_end_point, 0, 'f', 3).toStdString().c_str() << std::endl;
  }
void STRAIGHT_FEED(int lineno,
                          double x, double y, double z,
                          double a, double b, double c,
                          double u, double v, double w) {
  std::cout << QString("Feed -> %1/%2/%3").arg(x, 0, 'f', 3).arg(y, 0, 'f', 3).arg(z, 0, 'f', 3).toStdString().c_str() << std::endl;
  }
void NURBS_FEED(int lineno, std::vector<CONTROL_POINT> nurbs_control_points, unsigned int k) {
  double        u = 0.0;
  unsigned int  n = nurbs_control_points.size() - 1;
  double        umax = n - k + 2;
  unsigned int  div = nurbs_control_points.size()*3;
  std::vector<unsigned int> knot_vector = knot_vector_creator(n, k);
  PLANE_POINT   P1;

  while (u+umax/div < umax) {
        PLANE_POINT P1 = nurbs_point(u+umax/div,k,nurbs_control_points,knot_vector);
        STRAIGHT_FEED(lineno, P1.X, P1.Y, 0., 0.,0.,0.,  0.,0.,0.);
        u = u + umax/div;
        }
  P1.X = nurbs_control_points[n].X;
  P1.Y = nurbs_control_points[n].Y;
  STRAIGHT_FEED(lineno, P1.X, P1.Y, 0., 0.,0.,0.,  0.,0.,0.);
  knot_vector.clear();
  }
void RIGID_TAP(int lineno,
                      double x, double y, double z, double scale) {
  std::cout << "rigid tap ..." << std::endl;
  }
void STRAIGHT_PROBE(int lineno,
                           double x, double y, double z,
                           double a, double b, double c,
                           double u, double v, double w, unsigned char probe_type) {
  std::cout << "straight probe ..." << std::endl;
  }
void STOP() {
  std::cout << "stop ..." << std::endl;
  }
void DWELL(double seconds) {
  std::cout << "dwell ..." << std::endl;
  }
void SET_SPINDLE_MODE(int spindle, double r) {
  std::cout << "set spindle mode ..." << std::endl;
  }
void SPINDLE_RETRACT_TRAVERSE() {
  std::cout << "spindle retract traverse ..." << std::endl;
  }
void START_SPINDLE_CLOCKWISE(int spindle, int dir) {
  std::cout << "start spindle clockwise ..." << std::endl;
  }
void START_SPINDLE_COUNTERCLOCKWISE(int spindle, int dir) {
  std::cout << "start spindle counterclockwise ..." << std::endl;
  }
void SET_SPINDLE_SPEED(int spindle, double r) {
  std::cout << "set spindle speed ..." << std::endl;
  }
void STOP_SPINDLE_TURNING(int spindle) {
  std::cout << "stop spindle turning ..." << std::endl;
  }
void SPINDLE_RETRACT() {
  std::cout << "spindle retract ..." << std::endl;
  }
void ORIENT_SPINDLE(int spindle, double orientation, int mode) {
  std::cout << "orient spindle ..." << std::endl;
  }
void WAIT_SPINDLE_ORIENT_COMPLETE(int spindle, double timeout) {
  std::cout << "wait spindle orient complete ..." << std::endl;
  }
void LOCK_SPINDLE_Z() {
  std::cout << "lock spindle Z ..." << std::endl;
  }
void USE_SPINDLE_FORCE() {
  std::cout << "use spindle force ..." << std::endl;
  }
void USE_NO_SPINDLE_FORCE() {
  std::cout << "use no spindle force ..." << std::endl;
  }
void SET_TOOL_TABLE_ENTRY(int pocket, int toolno, EmcPose offset, double diameter,
                          double frontangle, double backangle, int orientation) {
  std::cout << "change tooltable entry: " << toolno << " p" << pocket << std::endl;
  }
void USE_TOOL_LENGTH_OFFSET(EmcPose offset) {
  std::cout << "use tool length offset ..." << offset.tran.z << std::endl;
  }
void CHANGE_TOOL(int ttIndex) {
  std::cout << "change tool to tooltable-entry #" << ttIndex << std::endl;
  }
void SELECT_TOOL(int tool) {
  std::cout << "select tool #" << tool << std::endl;
  }
void CHANGE_TOOL_NUMBER(int number) {
  std::cout << "change tool number to #" << number << " ..." << std::endl;
  }
void START_CHANGE(void) {
  std::cout << "start change ..." << std::endl;
  }
void CLAMP_AXIS(CANON_AXIS axis) {
  std::cout << "clamp axis ..." << std::endl;
  }
void COMMENT(const char *s) {
  std::cout << "comment <" << s << "> ..." << std::endl;
  }
void DISABLE_ADAPTIVE_FEED() {
  std::cout << "disable adaptive feed ..." << std::endl;
  }
void ENABLE_ADAPTIVE_FEED() {
  std::cout << "enable adaptive feed ..." << std::endl;
  }
void DISABLE_FEED_OVERRIDE() {
  std::cout << "disable feed override ..." << std::endl;
  }
void ENABLE_FEED_OVERRIDE() {
  std::cout << "enable feed override ..." << std::endl;
  }
void DISABLE_SPEED_OVERRIDE(int spindle) {
  std::cout << "disable speed override ..." << std::endl;
  }
void ENABLE_SPEED_OVERRIDE(int spindle) {
  std::cout << "enable speed override ..." << std::endl;
  }
void DISABLE_FEED_HOLD() {
  std::cout << "disable feed hold ..." << std::endl;
  }
void ENABLE_FEED_HOLD() {
  std::cout << "enable feed hold ..." << std::endl;
  }
void FLOOD_OFF() {
  std::cout << "flood off ..." << std::endl;
  }
void FLOOD_ON() {
  std::cout << "flood on ..." << std::endl;
  }
void MESSAGE(char *s) {
  std::cout << "send message to client: " << s << std::endl;
  }
void LOG(char *s) {
  std::cout << "log: >" << s << "< ..." << std::endl;
  }
void LOGOPEN(char *s) {
  std::cout << "log open (" << s << ") ..." << std::endl;
  }
void LOGAPPEND(char *s) {
  std::cout << "log append [" << s << "] ..." << std::endl;
  }
void LOGCLOSE() {
  std::cout << "log close ..." << std::endl;
  }
void MIST_OFF() {
  std::cout << "mist off ..." << std::endl;
  }
void MIST_ON() {
  std::cout << "mist off ..." << std::endl;
  }
void PALLET_SHUTTLE() {
  std::cout << "pallet shuttle ..." << std::endl;
  }
void TURN_PROBE_OFF() {
  std::cout << "turn probe off ..." << std::endl;
  }
void TURN_PROBE_ON() {
  std::cout << "turn probe on ..." << std::endl;
  }
void UNCLAMP_AXIS(CANON_AXIS axis) {
  std::cout << "unclamp axis ..." << std::endl;
  }
void NURB_KNOT_VECTOR() {
  std::cout << "nurbs knot vector ..." << std::endl;
  }
void NURB_CONTROL_POINT(int i, double x, double y, double z,
                   double w) {
  std::cout << "nurbs control point #" << i << " (" << x << "/" << y << "/" << z << ") -> w: " << w << " ..." << std::endl;
  }
void NURB_FEED(double sStart, double sEnd) {
  std::cout << "nurb feed ..." << std::endl;
  }
void SET_BLOCK_DELETE(bool enabled) {
  std::cout << "set block delete (" << (enabled ? "true" : "false") << ") ..." << std::endl;
  }
bool GET_BLOCK_DELETE(void) {
  std::cout << "get block delete ..." << std::endl;
  }
void OPTIONAL_PROGRAM_STOP() {
  std::cout << "optional program stop ..." << std::endl;
  }
void SET_OPTIONAL_PROGRAM_STOP(bool state) {
  std::cout << "set optional program stop ..." << std::endl;
  }
bool GET_OPTIONAL_PROGRAM_STOP() {
  std::cout << "get optional program stop ..." << std::endl;
  }
void PROGRAM_END() {
  std::cout << "program end!" << std::endl;
  }
void PROGRAM_STOP() {
  std::cout << "program stop!" << std::endl;
  }
void SET_MOTION_OUTPUT_BIT(int index) {
  std::cout << "set motion output bit ..." << std::endl;
  }
void CLEAR_MOTION_OUTPUT_BIT(int index) {
  std::cout << "clear motion output bit ..." << std::endl;
  }
void SET_AUX_OUTPUT_BIT(int index) {
  std::cout << "set aux output bit ..." << std::endl;
  }
void CLEAR_AUX_OUTPUT_BIT(int index) {
  std::cout << "clear aux output bit ..." << std::endl;
  }
void SET_MOTION_OUTPUT_VALUE(int index, double value) {
  std::cout << "set motion output value ..." << std::endl;
  }
void SET_AUX_OUTPUT_VALUE(int index, double value) {
  std::cout << "set aux output value ..." << std::endl;
  }
int WAIT(int index
       , int input_type
       , int wait_type
       , double timeout) {
  std::cout << "wait ..." << std::endl;
  }
int UNLOCK_ROTARY(int line_no, int axis) {
  std::cout << "unlock rotary ..." << std::endl;
  }
int LOCK_ROTARY(int line_no, int axis) {
  std::cout << "lock rotary ..." << std::endl;
  }
double GET_EXTERNAL_FEED_RATE() {
  std::cout << "get external feed rate ..." << std::endl;
  }
int GET_EXTERNAL_FLOOD() {
  std::cout << "get external flood ..." << std::endl;
  }
CANON_UNITS GET_EXTERNAL_LENGTH_UNIT_TYPE() {
  std::cout << "get external length unit type ..." << std::endl;
  }
double GET_EXTERNAL_LENGTH_UNITS() {
  std::cout << "get external length units ..." << std::endl;
  }
double GET_EXTERNAL_ANGLE_UNITS() {
  std::cout << "get external angle units ..." << std::endl;
  }
int GET_EXTERNAL_MIST() {
  std::cout << "get external mist ..." << std::endl;
  }
CANON_MOTION_MODE GET_EXTERNAL_MOTION_CONTROL_MODE() {
  std::cout << "get external motion control mode ..." << std::endl;
  }
double GET_EXTERNAL_MOTION_CONTROL_TOLERANCE() {
  std::cout << "get external motion control tolerance ..." << std::endl;
  }

extern void SET_PARAMETER_FILE_NAME(const char *name) {
  std::cout << "set parameter file name to <" << name << "> ..." << std::endl;
  }
double GET_EXTERNAL_MOTION_CONTROL_NAIVECAM_TOLERANCE() {
  std::cout << "get external motion control naive cam tolerance ..." << std::endl;
  }
void GET_EXTERNAL_PARAMETER_FILE_NAME(char *filename, int max_size) {
  snprintf(filename, max_size, "%s", "rs274ngc.var");
  }
CANON_PLANE GET_EXTERNAL_PLANE() {
  std::cout << "get external plane ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_A() {
  std::cout << "get external position A ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_B() {
  std::cout << "get external position B ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_C() {
  std::cout << "get external position C ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_X() {
  std::cout << "get external position X ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_Y() {
  std::cout << "get external position Y ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_Z() {
  std::cout << "get external position Z ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_U() {
  std::cout << "get external position U ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_V() {
  std::cout << "get external position V ..." << std::endl;
  }
double GET_EXTERNAL_POSITION_W() {
  std::cout << "get external position W ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_A() {
  std::cout << "get external probe position A ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_B() {
  std::cout << "get external probe position B ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_C() {
  std::cout << "get external probe position C ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_X() {
  std::cout << "get external probe position X ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_Y() {
  std::cout << "get external probe position Y ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_Z() {
  std::cout << "get external probe position Z ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_U() {
  std::cout << "get external probe position U ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_V() {
  std::cout << "get external probe position V ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_POSITION_W() {
  std::cout << "get external probe position W ..." << std::endl;
  }
double GET_EXTERNAL_PROBE_VALUE() {
  std::cout << "get external probe value ..." << std::endl;
  }
int GET_EXTERNAL_PROBE_TRIPPED_VALUE() {
  std::cout << "get external probe tripped value ..." << std::endl;
  }
int GET_EXTERNAL_QUEUE_EMPTY() {
  std::cout << "get external queue empty ..." << std::endl;
  }
double GET_EXTERNAL_SPEED(int spindle) {
  std::cout << "get external speed ..." << std::endl;
  }
CANON_DIRECTION GET_EXTERNAL_SPINDLE(int spindle) {
  std::cout << "get external spindle ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_XOFFSET() {
  std::cout << "get external tool length x-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_YOFFSET() {
  std::cout << "get external tool length y-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_ZOFFSET() {
  std::cout << "get external tool length z-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_AOFFSET() {
  std::cout << "get external tool length a-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_BOFFSET() {
  std::cout << "get external tool length b-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_COFFSET() {
  std::cout << "get external tool length c-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_UOFFSET() {
  std::cout << "get external tool length u-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_VOFFSET() {
  std::cout << "get external tool length v-offset ..." << std::endl;
  }
double GET_EXTERNAL_TOOL_LENGTH_WOFFSET() {
  std::cout << "get external tool length w-offset ..." << std::endl;
  }
int GET_EXTERNAL_TOOL_SLOT() {
  std::cout << "get external tool slot ..." << std::endl;
  }
int GET_EXTERNAL_SELECTED_TOOL_SLOT() {
  std::cout << "get external selected tool slot ..." << std::endl;
  }
CANON_TOOL_TABLE GET_EXTERNAL_TOOL_TABLE(int pocket) {
  std::cout << "get external tool table - pocket #" << pocket << " ..." << std::endl;
  }
int GET_EXTERNAL_TC_FAULT() {
  std::cout << "get external tc fault ..." << std::endl;
  return 0;
  }
int GET_EXTERNAL_TC_REASON() {
  std::cout << "get external tc reason ..." << std::endl;
  return 0;
  }
double GET_EXTERNAL_TRAVERSE_RATE() {
  std::cout << "get external traverse rate ..." << std::endl;
  }
int GET_EXTERNAL_FEED_OVERRIDE_ENABLE() {
  std::cout << "get external feed override enable ..." << std::endl;
  }
int GET_EXTERNAL_SPINDLE_OVERRIDE_ENABLE(int spindle) {
  std::cout << "get external spindle override enable (spindle #" << spindle << ") ..." << std::endl;
  }
int GET_EXTERNAL_ADAPTIVE_FEED_ENABLE() {
  std::cout << "get external adaptive feed enable ..." << std::endl;
  }
int GET_EXTERNAL_FEED_HOLD_ENABLE() {
  std::cout << "get external feed hold enable ..." << std::endl;
  }
int GET_EXTERNAL_DIGITAL_INPUT(int index, int def) {
  std::cout << "get external digital input ..." << std::endl;
  }
double GET_EXTERNAL_ANALOG_INPUT(int index, double def) {
  std::cout << "get external analog input ..." << std::endl;
  }
int GET_EXTERNAL_AXIS_MASK() {
  std::cout << "get external axis mask ..." << std::endl;
  return 7;
  }
void FINISH(void) {
  std::cout << "finish ..." << std::endl;
  }
void ON_RESET(void) {
  std::cout << "ON RESET  ..." << std::endl;
  }
void CANON_ERROR(const char *fmt, ...) {
  std::cout << "canon error  ..." << std::endl;
  }
void PLUGIN_CALL(int len, const char *call) {
  std::cout << "plugin call  ..." << std::endl;
  }
void IO_PLUGIN_CALL(int len, const char *call) {
  std::cout << "io plugin call ..." << std::endl;
  }
void UPDATE_TAG(StateTag tag) {
  std::cout << "update tag  ..." << std::endl;
  }

USER_DEFINED_FUNCTION_TYPE USER_DEFINED_FUNCTION[USER_DEFINED_FUNCTION_NUM];

int GET_EXTERNAL_OFFSET_APPLIED() {
  std::cout << "get external offset applied ..." << std::endl;
  };
EmcPose GET_EXTERNAL_OFFSETS(){
  std::cout << "get external offsets ..." << std::endl;
  };

void reset_internals() {
  _sai = StandaloneInterpInternals();
  }

StandaloneInterpInternals::StandaloneInterpInternals()
 : _active_plane(CANON_PLANE_XY)
 , _active_slot(1)
 , _feed_mode(0)
 , _feed_rate(0.0)
 , _flood(0)
 , _length_unit_factor(1) /* 1 for MM 25.4 for inch */
 , _length_unit_type(CANON_UNITS_MM)
 , _line_number(1)
 , _mist(0)
 , _motion_mode(CANON_CONTINUOUS)
 , _probe_position_a(0) /*AA*/
 , _probe_position_b(0) /*BB*/
 , _probe_position_c(0) /*CC*/
 , _probe_position_x(0)
 , _probe_position_y(0)
 , _probe_position_z(0)
 , _g5x_x(0)
 , _g5x_y(0.0)
 , _g5x_z(0.0)
 , _g5x_a(0.0)
 , _g5x_b(0.0)
 , _g5x_c(0.0)
 , _g92_x(0.0)
 , _g92_y(0.0)
 , _g92_z(0.0)
 , _g92_a(0.0)
 , _g92_b(0.0)
 , _g92_c(0.0)
 , _program_position_a(0) /*AA*/
 , _program_position_b(0) /*BB*/
 , _program_position_c(0) /*CC*/
 , _program_position_x(0)
 , _program_position_y(0)
 , _program_position_z(0)
 , _spindle_speed{0}
 , _spindle_turning{CANON_STOPPED}
 , _pockets_max(CANON_POCKETS_MAX)
 , _tools{}
  /* optional program stop */
 , optional_program_stop(ON) //set enabled by default (previous EMC behaviour)
  /* optional block delete */
 , block_delete(ON) //set enabled by default (previous EMC behaviour)
 , motion_tolerance(0.)
 , naivecam_tolerance(0.)
  /* Dummy status variables */
 , _traverse_rate(0.0)
 , _tool_offset({})
 , _toolchanger_fault(false)
 , _toolchanger_reason(0) {
  }
#endif
