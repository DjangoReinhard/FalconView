#define CANONIF_CPP
#include <canonif.h>
#include <canonifsettings.h>
#include <tooltable.h>
#include <lcproperties.h>
#include <axismask.h>
#include <stupidtoolchangerif.h>
#include <core.h>
#include <graphicfactory.h>
//#include <guikernel.h>
#include <graphicfactory.h>

#include <AIS_Shape.hxx>
#include <gce_MakeDir.hxx>

#include <QVector3D>
#include <QDebug>


CanonIF::CanonIF(LcProperties& properties, ToolTable& toolTable) {
  if (p) throw std::runtime_error("already initialized canon settings!");
  }


CanonIF::CanonIF() {
  if (!p) throw std::runtime_error("wrong call sequence - canon NOT initialized!");
  }


void CanonIF::appendShape(int lineNum, Handle(AIS_InteractiveObject) shape) {
  p->toolPath.insert(lineNum, shape);
  }


LcProperties&     CanonIF::lcProperties() const            { return p->properties; }
CANON_UNITS       CanonIF::machineUnits() const            { return p->machineUnits; }
double            CanonIF::lengthUnits() const             { return p->lengthUnits(); }
double            CanonIF::feedRate() const                { return p->canon.linearFeedRate; }
double            CanonIF::traverseRate() const            { return p->iTraverseRate; }
bool              CanonIF::isFeedOverrideEnabled() const   { return p->feedOverride; }
bool              CanonIF::isAdaptiveFeedEnabled() const   { return p->adaptiveFeed; }
bool              CanonIF::isFeedHoldActive() const        { return p->feedHold; }
bool              CanonIF::isFloodActive() const           { return p->floodActive; }
bool              CanonIF::isMistActive() const            { return p->mistActive; }
int               CanonIF::activeSpindle() const           { return p->canon.spindle_num; }
CANON_PLANE       CanonIF::activePlane() const             { return p->canon.activePlane; }
CANON_MOTION_MODE CanonIF::motionMode() const              { return p->canon.motionMode; }
GraphicFactory    CanonIF::graphicFactory() const          { return p->gf; }
double            CanonIF::motionTolerance() const         { return p->canon.motionTolerance; }
double            CanonIF::naiveTolerance() const          { return p->canon.naivecamTolerance; }
double            CanonIF::posX() const                    { return p->canon.endPoint.x; }
double            CanonIF::posY() const                    { return p->canon.endPoint.y; }
double            CanonIF::posZ() const                    { return p->canon.endPoint.z; }
double            CanonIF::posA() const                    { return p->canon.endPoint.a; }
double            CanonIF::posB() const                    { return p->canon.endPoint.b; }
double            CanonIF::posC() const                    { return p->canon.endPoint.c; }
double            CanonIF::posU() const                    { return p->canon.endPoint.u; }
double            CanonIF::posV() const                    { return p->canon.endPoint.v; }
double            CanonIF::posW() const                    { return p->canon.endPoint.w; }
int               CanonIF::lastSlot() const                { return p->changer.slot4ToolInSpindle(); }
int               CanonIF::nextSlot() const                { return p->changer.nextTool(); }
//Quantity_Color    CanonIF::traverseColor() const           { return p->colTraverse; }
//Quantity_Color    CanonIF::feedColor() const               { return p->colFeed; }
//Quantity_Color    CanonIF::limitColor() const              { return p->colLimits; }
//Quantity_Color    CanonIF::curSegColor() const             { return p->colCurSeg; }
//Quantity_Color    CanonIF::oldSegColor() const             { return p->colOldSeg; }
//Quantity_Color    CanonIF::workPieceColor() const          { return p->colWorkPiece; }
CANON_TOOL_TABLE  CanonIF::toolEntry(int ttIndex)          { return p->canonTool(ttIndex); }
CANON_POSITION    CanonIF::g5xOffset(int i) const          { return p->g5xOffset(i); }
CANON_POSITION    CanonIF::g92Offset() const               { return p->canon.g92Offset; }
double            CanonIF::xyRotation() const              { return p->canon.xy_rotation; }
int               CanonIF::selectedOffset() const          { return p->selectedOffset; }
bool              CanonIF::isSpeedOverrideEnabled(int spindle) const  { return p->isSpeedOverrideEnabled(spindle); }
double            CanonIF::spindleSpeed(int spindle) const { return p->spindleSpeed(spindle); }
CANON_DIRECTION   CanonIF::spindleDir(int spindle) const   { return p->spindleDir(spindle); }
CANON_POSITION    CanonIF::toolOffset() const              { return p->canon.toolOffset; }
CANON_POSITION    CanonIF::endPoint() const                { return p->canon.endPoint; }
QString           CanonIF::parameterFilename() const       { return p->properties.parameterFileName(); }
QMap<long, Handle(AIS_InteractiveObject)>& CanonIF::toolPath() { return p->toolPath; }
void CanonIF::changeTool(int ttIndex)       { p->changeTool(ttIndex); }
void CanonIF::selectTool(int tool)          { p->changer.selectNextTool(tool); }
void CanonIF::setLengthUnits(CANON_UNITS u) { p->setJobUnits(u); }
void CanonIF::selectPlane(CANON_PLANE pl)   { p->selectPlane(pl); }
void CanonIF::setMotionMode(CANON_MOTION_MODE mode, double tol) { p->setMotionMode(mode, tol); }
void CanonIF::setEndPoint(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
  p->setEndPoint(CANON_POSITION(x, y, z, a, b, c, u, v, w));
  }
void CanonIF::setEndPoint(const CANON_POSITION& ep) { p->setEndPoint(ep); }
void CanonIF::setG5xOffset(int i, double x, double y, double z, double a, double b, double c, double u, double v, double w) {
  p->setG5xOffset(i, CANON_POSITION(x, y, z, a, b, c, u, v, w));
  }
void CanonIF::setG92Offset(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
  p->setG92Offset(CANON_POSITION(x, y, z, a, b, c, u, v, w));
  }
void CanonIF::setXYRotation(double r)                  { p->setXYRotation(r); }
void CanonIF::setSpindleMode(int spindle, double mode) { p->setSpindleMode(spindle, mode); }
//void CanonIF::setTraverseColor(const QColor& c)        { p->setTraverseColor(c); }
//void CanonIF::setFeedColor(const QColor& c)            { p->setFeedColor(c); }
//void CanonIF::setLimitsColor(const QColor& c)          { p->setLimitsColor(c); }
//void CanonIF::setCurSegColor(const QColor& c)          { p->setCurSegColor(c); }
//void CanonIF::setOldSegColor(const QColor& c)          { p->setOldSegColor(c); }
//void CanonIF::setWorkPieceColor(const QColor& c)       { p->setWorkPieceColor(c); }
void CanonIF::setToolOffset(EmcPose offset)            { p->setToolOffset(offset); }
CanonIFSettings* CanonIF::p = nullptr;
///////////////////////////////////////////////////////////////////////////////
/// Interpreter helper functions (don't use preprocessor macros!)
///////////////////////////////////////////////////////////////////////////////
inline double FROM_PROG_LEN(double l) { return l * CanonIF().lengthUnits(); }
inline double FROM_PROG_ANG(double a) { return a; }
inline double FROM_EXT_LEN(double l)  { return l / GET_EXTERNAL_LENGTH_UNITS(); }
inline double FROM_EXT_ANG(double a)  { return a / GET_EXTERNAL_ANGLE_UNITS(); }
inline double TO_EXT_LEN(double l)    { return l * GET_EXTERNAL_LENGTH_UNITS(); }
inline double TO_EXT_ANG(double a)    { return a * GET_EXTERNAL_ANGLE_UNITS(); }
inline double TO_PROG_LEN(double l)   { return l / CanonIF().lengthUnits(); }
inline double TO_PROG_ANG(double a)   { return a; }

/**
 * Simple circular shift function for PM_CARTESIAN type.
 * Cycle around axes without changing the individual values. A circshift of -1
 * makes the X value become the new Y, Y become the Z, and Z become the new X.
 */
static PM_CARTESIAN circshift(PM_CARTESIAN& vec, int steps) {
  int X = 0
    , Y = 1
    , Z = 2;
  int s = 3;

  // Use mod to cycle indices around by steps
  X = (X + steps + s) % s;
  Y = (Y + steps + s) % s;
  Z = (Z + steps + s) % s;

  return PM_CARTESIAN(vec[X], vec[Y], vec[Z]);
  }

static void rotate(double& x, double& y, double angle) {
  double xx, yy;
  double t = angle * M_PI / 180.0;

  xx = x;
  yy = y;
  x = xx * cos(t) - yy * sin(t);
  y = xx * sin(t) + yy * cos(t);
  }

static void rotate_and_offset_pos(double& x, double& y, double&, double&, double&, double&, double&, double&, double&) {
  CanonIF ci;

  rotate(x, y, ci.xyRotation());
  }

static void from_prog(CANON_POSITION& pos) {
  pos.x = FROM_PROG_LEN(pos.x);
  pos.y = FROM_PROG_LEN(pos.y);
  pos.z = FROM_PROG_LEN(pos.z);
  pos.a = FROM_PROG_ANG(pos.a);
  pos.b = FROM_PROG_ANG(pos.b);
  pos.c = FROM_PROG_ANG(pos.c);
  pos.u = FROM_PROG_LEN(pos.u);
  pos.v = FROM_PROG_LEN(pos.v);
  pos.w = FROM_PROG_LEN(pos.w);
  }

static void from_prog(double& x, double& y, double& z, double& a, double& b, double& c, double& u, double& v, double& w) {
  x = FROM_PROG_LEN(x);
  y = FROM_PROG_LEN(y);
  z = FROM_PROG_LEN(z);
  a = FROM_PROG_ANG(a);
  b = FROM_PROG_ANG(b);
  c = FROM_PROG_ANG(c);
  u = FROM_PROG_LEN(u);
  v = FROM_PROG_LEN(v);
  w = FROM_PROG_LEN(w);
  }

static void from_prog_len(PM_CARTESIAN& vec) {
  vec.x = FROM_PROG_LEN(vec.x);
  vec.y = FROM_PROG_LEN(vec.y);
  vec.z = FROM_PROG_LEN(vec.z);
  }

static void to_rotated(PM_CARTESIAN &vec) {
  rotate(vec.x, vec.y, CanonIF().xyRotation());
  }

static void rotate_and_offset(CANON_POSITION & pos) {
  CanonIF ci;

  rotate(pos.x, pos.y, ci.xyRotation());
  }

static void rotate_and_offset_xyz(PM_CARTESIAN & xyz) {
  CanonIF ci;

  rotate(xyz.x, xyz.y, ci.xyRotation());
  }

static double chord_deviation(double sx, double sy, double ex, double ey, double cx, double cy, int rotation, double& mx, double& my) {
  double th1 = atan2(sy - cy, sx - cx),
         th2 = atan2(ey - cy, ex - cx),
         r   = hypot(sy - cy, sx - cx),
         dth = th2 - th1;

  if (rotation < 0) {
     if (dth >= -1e-5) th2 -= 2 * M_PI;
     // in the edge case where atan2 gives you -pi and pi, a second iteration is needed
     // to get these in the right order
     dth = th2 - th1;
     if (dth >= -1e-5) th2 -= 2 * M_PI;
     }
  else {
     if (dth <= 1e-5)  th2 += 2 * M_PI;
     dth = th2 - th1;
     if (dth <= 1e-5)  th2 += 2 * M_PI;
     }
  double included = fabs(th2 - th1);
  double mid      = (th2 + th1) / 2;

  mx = cx + r * cos(mid);
  my = cy + r * sin(mid);
  double dev = r * (1 - cos(included / 2));

  return dev;
  }

static gp_Pnt to_ext_len(const gp_Pnt& p) {
  gp_Pnt ret(TO_EXT_LEN(p.X())
           , TO_EXT_LEN(p.Y())
           , TO_EXT_LEN(p.Z()));

  return ret;
  }

static void to_prog(CANON_POSITION& e) {
  e.x = TO_PROG_LEN(e.x);
  e.y = TO_PROG_LEN(e.y);
  e.z = TO_PROG_LEN(e.z);
  e.a = TO_PROG_ANG(e.a);
  e.b = TO_PROG_ANG(e.b);
  e.c = TO_PROG_ANG(e.c);
  e.u = TO_PROG_LEN(e.u);
  e.v = TO_PROG_LEN(e.v);
  e.w = TO_PROG_LEN(e.w);
  }


// capitalized old style c-functions, the interpreter callbacks :(


void INIT_CANON() {
//  qDebug() << "NCanon: init Canon() ...";
  }

CANON_UNITS GET_EXTERNAL_LENGTH_UNIT_TYPE() {
//  qDebug() << "NCanon: machine units (" << CanonIF().machineUnits() << ") ...";
  return CanonIF().machineUnits();
  }

double GET_EXTERNAL_LENGTH_UNITS() {
  return CanonIF().lengthUnits();
  }

double GET_EXTERNAL_ANGLE_UNITS() {
  return 1.0;
  }

void SET_G5X_OFFSET(int fixture, double x, double y, double z, double a, double b, double c, double u, double v, double w) {
//  qDebug() << "NCanon: set G5x offset #" << fixture
//           << " -> " << x << "/" << y << "/" << z
//           << "\t" << a << "/" << b << "/" << c
//           << "\t" << u << "/" << v << "/" << w;
  CanonIF().setG5xOffset(fixture, x, y, z, a, b, c, u, v, w);
  }

void SET_G92_OFFSET(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
//  qDebug() << "NCanon: set G92 offset "
//           << " -> " << x << "/" << y << "/" << z
//           << "\t" << a << "/" << b << "/" << c
//           << "\t" << u << "/" << v << "/" << w;
  CanonIF().setG92Offset(x, y, z, a, b, c, u, v, w);
  }

void SET_XY_ROTATION(double t) {
//  qDebug() << "NCanon: set XY-Rotation to " << t;
  CanonIF().setXYRotation(t);
  }

int GET_EXTERNAL_AXIS_MASK() {
//  qDebug() << "WHOOHOO ---> get external AXIS mask <--- (00)";
  return Core().axisMask();
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
  int slot = CanonIF().lastSlot();

//  qDebug() << "NCanon: get external Tool-Slot for tool in spindle (" << slot << ")";

  return slot;
  }

int GET_EXTERNAL_SELECTED_TOOL_SLOT() {
  int slotOrWhatever = CanonIF().nextSlot();

//  qDebug() << "NCanon: get external Tool-Slot for next tool to use (" << slotOrWhatever << ")";

  return slotOrWhatever;
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
//  if (ttIndex < 10) {
//     qDebug() << "NCanon: get external tool table entry #" << ttIndex << " (msg limited to 10)";
//     }
  CANON_TOOL_TABLE tool = CanonIF().toolEntry(ttIndex);

  if (tool.offset.tran.z > 0) tool.offset.tran.z *= -1;
  return tool;
  }

// return the value of iocontrol's toolchanger-fault pin
// bullshit-bingo part II - another function that get called
// thousand times without any sense :(
int GET_EXTERNAL_TC_FAULT() {
  return 0;
  }

// return the value of iocontrol's toolchanger-reason pin
// bullshit-bingo part II - another function that get called
// thousand times without any sense :(
int GET_EXTERNAL_TC_REASON() {
  return 0;
  }

void ON_RESET(void) {
  }

void UPDATE_TAG(StateTag) {
//  qDebug() << "NCanon: NO update tag  ...";
  }

double GET_EXTERNAL_TOOL_LENGTH_XOFFSET() {
//  qDebug() << "NCanon: get external tool length X-offset: " << CanonIF().toolOffset().x;

  return CanonIF().toolOffset().x;
  }

double GET_EXTERNAL_TOOL_LENGTH_YOFFSET() {
//  qDebug() << "NCanon: get external tool length Y-offset: " << CanonIF().toolOffset().y;

  return CanonIF().toolOffset().y;
  }

double GET_EXTERNAL_TOOL_LENGTH_ZOFFSET() {
//  qDebug() << "NCanon: get external tool length Z-offset: " << CanonIF().toolOffset().z;

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
//  qDebug() << "NCanon: use tool length offset = " << offset.tran.z;
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
//  qDebug() << "NCanon: use length units (" << u << ") ...";
  CanonIF().setLengthUnits(u);
  }

void SELECT_TOOL(int toolNum) {
//  qDebug() << "NCanon: select tool #" << toolNum;
  CanonIF().selectTool(toolNum);
  }

void CHANGE_TOOL(int slot) {
//  qDebug() << "NCanon: change tool to slot" << slot;
  CanonIF().changeTool(slot);
  }

void CHANGE_TOOL_NUMBER(int) {
//  qDebug() << "NCanon: change tool number to #" << number << " ...";
  }

// WTF?
void START_CHANGE(void) {
//  qDebug() << "NCanon: start change ...";
  }

void SELECT_PLANE(CANON_PLANE pl) {
//  qDebug() << "NCanon:: select plane #" << pl;

  CanonIF().selectPlane(pl);
  }


void STRAIGHT_TRAVERSE(int lineno, double x, double y, double z
                                 , double a, double b, double c
                                 , double u, double v, double w) {
  from_prog(x,y,z,a,b,c,u,v,w);
  rotate_and_offset_pos(x,y,z,a,b,c,u,v,w);

  CanonIF        ci;
  CANON_POSITION sp = ci.endPoint();
  CANON_POSITION ep(x, y, z, a, b, c, u, v, w);

  if (lineno > 0)   {
     Handle(AIS_Shape) shape = ci.graphicFactory().createLine(gp_Pnt(sp.x, sp.y, sp.z)
                                                            , gp_Pnt(ep.x, ep.y, ep.z));
//     shape->SetColor(ci.traverseColor());
     ci.appendShape(lineno, shape);
     }
  ci.setEndPoint(ep);
  }


void ARC_FEED(int lineno, double first_end, double second_end, double first_axis
                , double second_axis, int rotation, double axis_end_point
                , double a, double b, double c, double u, double v, double w) {
  CanonIF        ci;
  CANON_POSITION lp = ci.endPoint();

  if (ci.activePlane() == CANON_PLANE_XY && ci.motionMode() == CANON_CONTINUOUS) {
     double mx, my;
     double unused = 0;
     double fe = FROM_PROG_LEN(first_end)
          , se = FROM_PROG_LEN(second_end)
          , ae = FROM_PROG_LEN(axis_end_point);
     double fa = FROM_PROG_LEN(first_axis)
          , sa = FROM_PROG_LEN(second_axis);

     rotate_and_offset_pos(fe, se, ae, unused, unused, unused, unused, unused, unused);
     rotate_and_offset_pos(fa, sa, unused, unused, unused, unused, unused, unused, unused);

     if (chord_deviation(lp.x, lp.y, fe, se, fa, sa, rotation, mx, my)
       < ci.naiveTolerance()) {
        a = FROM_PROG_ANG(a);
        b = FROM_PROG_ANG(b);
        c = FROM_PROG_ANG(c);
        u = FROM_PROG_LEN(u);
        v = FROM_PROG_LEN(v);
        w = FROM_PROG_LEN(w);

        rotate_and_offset_pos(unused, unused, unused, a, b, c, u, v, w);

        gp_Pnt sp     = gp_Pnt(lp.x, lp.y, lp.z);
        gp_Pnt ep     = gp_Pnt(fe, se, ae);
        gp_Pnt center = gp_Pnt(fa, sa, fmin(sp.Z(), ae));
        Handle(AIS_Shape) shape;
        gp_Dir axis(0, 0, ep.Z() > sp.Z() ? 1 : -1);

        if (rotation > 0) shape = ci.graphicFactory().createHelix(sp, ep, center, axis, true);
        else              shape = ci.graphicFactory().createHelix(sp, ep, center, axis, false);
//        shape->SetColor(ci.feedColor());
        ci.appendShape(lineno, shape);
        ci.setEndPoint(ep.X(), ep.Y(), ep.Z(), a, b, c, u, v, w);

        return;
        }
     }
  PM_CARTESIAN endPoint(lp.x, lp.y, lp.z);
  // Start by defining 3D points for the motion end and center.
  PM_CARTESIAN end_cart(first_end, second_end, axis_end_point);
  PM_CARTESIAN center_cart(first_axis, second_axis, axis_end_point);
  PM_CARTESIAN normal_cart(0.0,0.0,1.0);
  PM_CARTESIAN plane_x(1.0,0.0,0.0);
  PM_CARTESIAN plane_y(0.0,1.0,0.0);
  // Rearrange the X Y Z coordinates in the correct order based on the active plane (XY, YZ, or XZ)
  // KLUDGE CANON_PLANE is 1-indexed, hence the subtraction here to make a 0-index value
  int shift_ind = 0;

  switch (ci.activePlane()) {
    case CANON_PLANE_XY:
         shift_ind = 0;
         break;
    case CANON_PLANE_XZ:
         shift_ind = -2;
         break;
    case CANON_PLANE_YZ:
         shift_ind = -1;
         break;
    case CANON_PLANE_UV:
    case CANON_PLANE_VW:
    case CANON_PLANE_UW:
         CANON_ERROR("Can't set plane in UVW axes, assuming XY");
         break;
    }
  end_cart    = circshift(end_cart,    shift_ind);
  center_cart = circshift(center_cart, shift_ind);
  normal_cart = circshift(normal_cart, shift_ind);
  plane_x     = circshift(plane_x, shift_ind);
  plane_y     = circshift(plane_y, shift_ind);
  // Define end point in PROGRAM units and convert to CANON
  CANON_POSITION endpt(0,0,0,a,b,c,u,v,w);

  from_prog(endpt);
  // Store permuted XYZ end position
  from_prog_len(end_cart);
  endpt.set_xyz(end_cart);
  // Convert to CANON units
  from_prog_len(center_cart);

  // Rotate and offset the new end point to be in the same coordinate system as the current end point
  rotate_and_offset(endpt);
  rotate_and_offset_xyz(center_cart);
  rotate_and_offset_xyz(end_cart);

  // Also rotate the basis vectors
  to_rotated(plane_x);
  to_rotated(plane_y);
  to_rotated(normal_cart);

  // Note that the "start" point is already rotated and offset
  Handle(AIS_Shape) shape;

  if (rotation == 0) {
     shape = ci.graphicFactory().createLine(gp_Pnt(lp.x, lp.y, lp.z)
                                          , gp_Pnt(endpt.x, endpt.y, endpt.z));
     }
  else {
     int fullTurn = 0;
     gp_Pnt sp(lp.x, lp.y, lp.z);
     gp_Pnt ep     = to_ext_len(gp_Pnt(endpt.x, endpt.y, endpt.z));
     // Convert internal center and normal to external units
     gp_Pnt center = to_ext_len(gp_Pnt(center_cart.x, center_cart.y, fmin(lp.z, endpt.z)));
     gp_Pnt normal = to_ext_len(gp_Pnt(normal_cart.x, normal_cart.y, normal_cart.z));
     gp_Dir axis(normal.X(), normal.Y(), normal.Z());
     if (sp.X() == ep.X() && sp.Y() == ep.Y() && sp.Z() == ep.Z()) fullTurn = 1;
     shape = ci.graphicFactory().createHelix(sp, ep, center, axis, rotation > 0,  fullTurn);
     }
  if (shape) {
//     shape->SetColor(ci.feedColor());
     ci.appendShape(lineno, shape);
     }
  ci.setEndPoint(endpt);
  }


void STRAIGHT_FEED(int lineno, double x, double y, double z
                             , double a, double b, double c
                             , double u, double v, double w) {
  from_prog(x,y,z,a,b,c,u,v,w);
  rotate_and_offset_pos(x,y,z,a,b,c,u,v,w);

  CanonIF        ci;
  CANON_POSITION sp = ci.endPoint();
  CANON_POSITION ep(x, y, z, a, b, c, u, v, w);

  Handle(AIS_Shape) shape = ci.graphicFactory().createLine(gp_Pnt(sp.x, sp.y, sp.z)
                                                         , gp_Pnt(ep.x, ep.y, ep.z));
//  shape->SetColor(ci.feedColor());
  ci.appendShape(lineno, shape);
  ci.setEndPoint(ep);
  }


void CANON_UPDATE_END_POINT(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
  CanonIF().setEndPoint(x, y, z, a, b, c, u, v, w);
  }

void SET_TRAVERSE_RATE(double ) {
  }

void SET_FEED_RATE(double ) {
  }

void SET_FEED_REFERENCE(CANON_FEED_REFERENCE ) {
  }

void SET_FEED_MODE(int , int ) {
  }

void SET_MOTION_CONTROL_MODE(CANON_MOTION_MODE , double ) {
  }

void SET_NAIVECAM_TOLERANCE(double ) {
  }

void SET_CUTTER_RADIUS_COMPENSATION(double ) {
//  qDebug() << "NCanon: set cutter radius compensation of R" << radius;
  }

void START_CUTTER_RADIUS_COMPENSATION(int ) {
//  qDebug() << "NCanon: start cutter radius compensation with direction " << direction;
  }

void STOP_CUTTER_RADIUS_COMPENSATION() {
//  qDebug() << "NCanon: stop cutter radius compensation";
  }

void START_SPEED_FEED_SYNCH(int , double , bool ) {
//  qDebug() << " NCanon: start speed feed synch ...";
  }

void STOP_SPEED_FEED_SYNCH() {
//  qDebug() << "NCanon: stop speed feed synch ...";
  }

/// nurbs stuff taken from linuxcnc (task/emccanon.cc)
static int biarc(int lineno, double p0x, double p0y
                           , double tsx, double tsy
                           , double p4x, double p4y
                           , double tex, double tey, double r=1.0);


static void unit(double* x, double* y) {
  double h = hypot(*x, *y);

  if(h != 0) { *x /= h; *y /= h; }
  }


static void arc(int lineno, double x0, double y0
                          , double x1, double y1
                          , double dx, double dy) {
  double small = 0.000001;
  double x     = x1 - x0, y = y1 - y0;
  double den   = 2 * (y*dx - x*dy);
  CANON_POSITION p = CanonIF().endPoint();

  to_prog(p);
  if (fabs(den) > small) {
     double r  = -(x * x + y * y) / den;
     double i  = dy * r, j  = -dx * r;
     double cx = x0 + i, cy = y0 + j;

     ARC_FEED(lineno, x1, y1, cx, cy, r<0 ? 1 : -1,
                      p.z, p.a, p.b, p.c, p.u, p.v, p.w);
     }
  else {
     STRAIGHT_FEED(lineno, x1, y1, p.z, p.a, p.b, p.c, p.u, p.v, p.w);
     }
  }


static int biarc(int lineno, double p0x, double p0y
                           , double tsx, double tsy
                           , double p4x, double p4y
                           , double tex, double tey, double r) {
  unit(&tsx, &tsy);
  unit(&tex, &tey);

  double vx = p0x - p4x, vy = p0y - p4y;
  double c  = vx * vx + vy * vy;
  double b  = 2 * (vx * (r * tsx + tex) + vy * (r * tsy + tey));
  double a  = 2 * r * (tsx * tex + tsy * tey - 1);
  double discr = b * b - 4 * a * c;

  if (discr < 0) return 0;

  double disq  = sqrt(discr);
  double beta1 = (-b - disq) / 2 / a;
  double beta2 = (-b + disq) / 2 / a;

  if (beta1 > 0 && beta2 > 0) return 0;

  double beta  = fmax(beta1, beta2);
  double alpha = beta * r;
  double ab  = alpha + beta;
  double p1x = p0x + alpha * tsx, p1y = p0y + alpha * tsy,
         p3x = p4x - beta * tex,  p3y = p4y - beta * tey,
         p2x = (p1x * beta + p3x * alpha) / ab,
         p2y = (p1y * beta + p3y * alpha) / ab;
  double tmx = p3x - p2x, tmy = p3y - p2y;

  unit(&tmx, &tmy);

  arc(lineno, p0x, p0y, p2x, p2y, tsx, tsy);
  arc(lineno, p2x, p2y, p4x, p4y, tmx, tmy);

  return 1;
  }


void NURBS_FEED(int lineno, std::vector<CONTROL_POINT> nurbs_control_points, unsigned int k) {
  unsigned int n    = nurbs_control_points.size() - 1;
  double       umax = n - k + 2;
  unsigned int div  = nurbs_control_points.size()*4;
  std::vector<unsigned int> knot_vector = knot_vector_creator(n, k);
  PLANE_POINT P0, P0T, P1, P1T;

  P0  = nurbs_point(0,k,nurbs_control_points,knot_vector);
  P0T = nurbs_tangent(0, k, nurbs_control_points, knot_vector);

  for (unsigned int i=1; i<=div; i++) {
      double u = umax * i / div;
      P1  = nurbs_point(u,k,nurbs_control_points,knot_vector);
      P1T = nurbs_tangent(u,k,nurbs_control_points,knot_vector);

      biarc(lineno, P0.X,P0.Y, P0T.X,P0T.Y, P1.X,P1.Y, P1T.X,P1T.Y);

      P0  = P1;
      P0T = P1T;
      }
  knot_vector.clear();
  }


void RIGID_TAP(int , double x, double y, double z, double ) {
  CANON_POSITION ep = CanonIF().endPoint();

  qDebug() << "NCanon: rigid tap - TODO!!! ...";
  ep.x = x;
  ep.y = y;
  ep.z = z;

  CanonIF().setEndPoint(ep.x, ep.y, ep.z, ep.a, ep.b, ep.c, ep.u, ep.v, ep.z);
  }

void STRAIGHT_PROBE(int, double, double, double, double, double, double, double, double, double, unsigned char) {
//  qDebug() << "NCanon: straight probe ...";
  }

void STOP() {
//  qDebug() << "NCanon: stop ...";
  }

void DWELL(double seconds) {
//  qDebug() << "NCanon: dwell ..." << seconds << "seconds";
  }

void SPINDLE_RETRACT_TRAVERSE() {
//  qDebug() << "NCanon: spindle retract traverse ...";
  }

void SPINDLE_RETRACT() {
//  qDebug() << "NCanon: spindle retract ...";
  }

void ORIENT_SPINDLE(int, double, int) {
//  qDebug() << "NCanon: orient spindle ...";
  }

void WAIT_SPINDLE_ORIENT_COMPLETE(int, double) {
//  qDebug() << "NCanon: wait spindle orient complete ...";
  }

void LOCK_SPINDLE_Z() {
//  qDebug() << "NCanon: lock spindle Z ...";
  }

void USE_SPINDLE_FORCE() {
//  qDebug() << "NCanon: use spindle force ...";
  }

void USE_NO_SPINDLE_FORCE() {
//  qDebug() << "NCanon: use no spindle force ...";
  }

void SET_TOOL_TABLE_ENTRY(int , int , EmcPose , double ,
                          double , double , int ) {
//  qDebug() << "NCanon: CHANGE tooltable entry ??? : " << toolno << " p" << pocket;
  }

void RELOAD_TOOLDATA(void) {
  }

void CLAMP_AXIS(CANON_AXIS) {
//  qDebug() << "NCanon: clamp axis ...";
  }

void DISABLE_ADAPTIVE_FEED() {
//  qDebug() << "NCanon: disable adaptive feed ...";
  }

void ENABLE_ADAPTIVE_FEED() {
//  qDebug() << "NCanon: enable adaptive feed ...";
  }

void DISABLE_FEED_OVERRIDE() {
//  qDebug() << "NCanon: disable feed override ...";
  }

void ENABLE_FEED_OVERRIDE() {
//  qDebug() << "NCanon: enable feed override ...";
  }

void DISABLE_SPEED_OVERRIDE(int) {
//  qDebug() << "NCanon: disable speed override ...";
  }

void ENABLE_SPEED_OVERRIDE(int) {
//  qDebug() << "NCanon: enable speed override ...";
  }

void DISABLE_FEED_HOLD() {
//  qDebug() << "NCanon: disable feed hold ...";
  }
void ENABLE_FEED_HOLD() {
//  qDebug() << "NCanon: enable feed hold ...";
  }

void MESSAGE(char*) {
//  qDebug() << "NCanon: send message to client: " << s;
  }

void LOG(char*) {
//  qDebug() << "NCanon: log: >" << s << "< ...";
  }

void LOGOPEN(char*) {
//  qDebug() << "NCanon: log open (" << s << ") ...";
  }

void LOGAPPEND(char*) {
//  qDebug() << "NCanon: log append [" << s << "] ...";
  }

void LOGCLOSE() {
//  qDebug() << "NCanon: log close ...";
  }

void PALLET_SHUTTLE() {
//  qDebug() << "NCanon: pallet shuttle ...";
  }

void TURN_PROBE_OFF() {
//  qDebug() << "NCanon: turn probe off ...";
  }
void TURN_PROBE_ON() {
//  qDebug() << "NCanon: turn probe on ...";
  }

void UNCLAMP_AXIS(CANON_AXIS) {
//  qDebug() << "NCanon: unclamp axis ...";
  }

void NURB_KNOT_VECTOR() {
//  qDebug() << "NCanon: nurbs knot vector ...";
  }

void NURB_CONTROL_POINT(int , double , double , double ,
                   double) {
//  qDebug() << "NCanon: nurbs control point #" << i << " (" << x << "/" << y << "/" << z << ") -> w: " << w << " ...";
  }

void NURB_FEED(double, double) {
//  qDebug() << "NCanon: nurb feed ?!? ...";
  }

void SET_BLOCK_DELETE(bool ) {
//  qDebug() << "NCanon: set block delete (" << (enabled ? "true" : "false") << ") ...";
  }

bool GET_BLOCK_DELETE(void) {
//  qDebug() << "NCanon: get block delete ...";
  return false;
  }

void OPTIONAL_PROGRAM_STOP() {
//  qDebug() << "NCanon: optional program stop ...";
  }

void SET_OPTIONAL_PROGRAM_STOP(bool) {
//  qDebug() << "NCanon: set optional program stop ...";
  }

bool GET_OPTIONAL_PROGRAM_STOP() {
//  qDebug() << "NCanon: get optional program stop ...";
  return true;
  }

void PROGRAM_END() {
//  qDebug() << "NCanon: program end!";
  }

void PROGRAM_STOP() {
//  qDebug() << "NCanon: program stop!";
  }

void SET_MOTION_OUTPUT_BIT(int) {
//  qDebug() << "NCanon: set motion output bit ...";
  }

void CLEAR_MOTION_OUTPUT_BIT(int) {
//  qDebug() << "NCanon: clear motion output bit ...";
  }

void SET_AUX_OUTPUT_BIT(int) {
//  qDebug() << "NCanon: set aux output bit ...";
  }

void CLEAR_AUX_OUTPUT_BIT(int) {
//  qDebug() << "NCanon: clear aux output bit ...";
  }

void SET_MOTION_OUTPUT_VALUE(int, double) {
//  qDebug() << "NCanon: set motion output value ...";
  }

void SET_AUX_OUTPUT_VALUE(int, double) {
//  qDebug() << "NCanon: set aux output value ...";
  }

int WAIT(int
       , int
       , int
       , double) {
//  qDebug() << "NCanon: wait ...";
  return 0;
  }

int UNLOCK_ROTARY(int, int) {
//  qDebug() << "NCanon: unlock rotary ...";
  return 0;
  }

int LOCK_ROTARY(int, int) {
//  qDebug() << "NCanon: lock rotary ...";
  return 0;
  }

void GET_EXTERNAL_PARAMETER_FILE_NAME(char *filename, int max_size) {
//  qDebug() << "NCanon: get external parameter file name ... (max size: " << max_size << ")";
  strncpy(filename, CanonIF().parameterFilename().toStdString().c_str(), max_size);
  }

void SET_PARAMETER_FILE_NAME(const char*) {
//  qDebug() << "NCanon: set parameter file name to <" << name << "> ...";
  }

double GET_EXTERNAL_PROBE_POSITION_A() {
//  qDebug() << "NCanon: get external probe position A ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_B() {
//  qDebug() << "NCanon: get external probe position B ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_C() {
//  qDebug() << "NCanon: get external probe position C ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_X() {
//  qDebug() << "NCanon: get external probe position X ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_Y() {
//  qDebug() << "NCanon: get external probe position Y ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_Z() {
//  qDebug() << "NCanon: get external probe position Z ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_U() {
//  qDebug() << "NCanon: get external probe position U ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_V() {
//  qDebug() << "NCanon: get external probe position V ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_POSITION_W() {
//  qDebug() << "NCanon: get external probe position W ...";
  return 0;
  }

double GET_EXTERNAL_PROBE_VALUE() {
//  qDebug() << "NCanon: get external probe value ...";
  return 0;
  }

int GET_EXTERNAL_PROBE_TRIPPED_VALUE() {
//  qDebug() << "NCanon: get external probe tripped value ...";
  return 0;
  }

int GET_EXTERNAL_QUEUE_EMPTY() {
  return 1;
  }

int GET_EXTERNAL_DIGITAL_INPUT(int, int) {
//  qDebug() << "NCanon: get external digital input ...";
  return 0;
  }

double GET_EXTERNAL_ANALOG_INPUT(int, double) {
//  qDebug() << "NCanon: get external analog input ...";
  return 0;
  }

USER_DEFINED_FUNCTION_TYPE USER_DEFINED_FUNCTION[USER_DEFINED_FUNCTION_NUM];

void FINISH(void) {
//  qDebug() << "NCanon: finish ...";
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
//  qDebug() << "NCanon: get external offset applied ...";
  return 0;
  };

EmcPose GET_EXTERNAL_OFFSETS(){
//  qDebug() << "NCanon: get external offsets ...";
  return EmcPose();
  }
