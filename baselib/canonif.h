#ifndef CANONIF_H
#define CANONIF_H
#include <QObject>
#include <QColor>
#include <graphicfactory.h>
#include <lcproperties.h>
#include <axismask.h>
#include <stupidtoolchangerif.h>
#include <canon.hh>
class ToolTable;
struct CanonConfig_t;


/**
 * @brief The CanonIF class
 * canon interface to handle external world for rs274 interpreter.
 * linuxcnc interpreter uses capitalized c-functions to interact with external
 * world. This class is a bridge between OO-world and plain old c-functions.
 */
class CanonIF
{
public:
  CanonIF(LcProperties& lcProperties, ToolTable& toolTable);
  CanonIF();

  CANON_UNITS       machineUnits() const            { return instance->machineUnits; }
  double            lengthUnits() const             { return instance->lengthUnits(); }
  double            feedRate() const                { return instance->canon.linearFeedRate; }
  double            traverseRate() const            { return instance->iTraverseRate; }
  bool              isFeedOverrideEnabled() const   { return instance->feedOverride; }
  bool              isAdaptiveFeedEnabled() const   { return instance->adaptiveFeed; }
  bool              isFeedHoldActive() const        { return instance->feedHold; }
  bool              isFloodActive() const           { return instance->floodActive; }
  bool              isMistActive() const            { return instance->mistActive; }
  int               activeSpindle() const           { return instance->canon.spindle_num; }
  CANON_PLANE       activePlane() const             { return instance->canon.activePlane; }
  CANON_MOTION_MODE motionMode() const              { return instance->canon.motionMode; }
  GraphicFactory    graphicFactory() const          { return instance->gf; }
  double            motionTolerance() const         { return instance->canon.motionTolerance; }
  double            naiveTolerance() const          { return instance->canon.naivecamTolerance; }
  double            posX() const                    { return instance->canon.endPoint.x; }
  double            posY() const                    { return instance->canon.endPoint.y; }
  double            posZ() const                    { return instance->canon.endPoint.z; }
  double            posA() const                    { return instance->canon.endPoint.a; }
  double            posB() const                    { return instance->canon.endPoint.b; }
  double            posC() const                    { return instance->canon.endPoint.c; }
  double            posU() const                    { return instance->canon.endPoint.u; }
  double            posV() const                    { return instance->canon.endPoint.v; }
  double            posW() const                    { return instance->canon.endPoint.w; }
  int               lastSlot() const                { return instance->changer.slot4ToolInSpindle(); }
  int               nextSlot() const                { return instance->changer.nextTool(); }
  Quantity_Color    traverseColor() const           { return instance->colTraverse; }
  Quantity_Color    feedColor() const               { return instance->colFeed; }
  Quantity_Color    limitColor() const              { return instance->colLimits; }
  Quantity_Color    curSegColor() const             { return instance->colCurSeg; }
  Quantity_Color    oldSegColor() const             { return instance->colOldSeg; }
  Quantity_Color    workPieceColor() const          { return instance->colWorkPiece; }
  CANON_TOOL_TABLE  toolEntry(int ttIndex)          { return instance->toolEntry(ttIndex); }
  CANON_POSITION    g5xOffset(int i=0) const        { return instance->g5xOffset(i); }
  CANON_POSITION    g92Offset() const               { return instance->canon.g92Offset; }
  double            xyRotation() const              { return instance->canon.xy_rotation; }
  int               selectedOffset() const          { return instance->selectedOffset; }
  bool              isSpeedOverrideEnabled(int spindle) const  { return instance->isSpeedOverrideEnabled(spindle); }
  double            spindleSpeed(int spindle) const { return instance->spindleSpeed(spindle); }
  CANON_DIRECTION   spindleDir(int spindle) const   { return instance->spindleDir(spindle); }
  CANON_POSITION    toolOffset() const              { return instance->canon.toolOffset; }
  CANON_POSITION    endPoint() const                { return instance->canon.endPoint; }
  QString           parameterFilename() const       { return instance->properties.parameterFileName(); }
  double            convert(double v);
  void              appendShape(int lineNum, Handle(AIS_InteractiveObject) shape);
  QMap<long, Handle(AIS_InteractiveObject)>& toolPath() { return instance->toolPath; }
  void changeTool(int ttIndex)       { instance->changeTool(ttIndex); }
  void selectTool(int tool)          { instance->changer.selectNextTool(tool); }
  void setLengthUnits(CANON_UNITS u) { instance->setJobUnits(u); }
  void selectPlane(CANON_PLANE pl)   { instance->selectPlane(pl); }
  void setMotionMode(CANON_MOTION_MODE mode, double tol) { instance->setMotionMode(mode, tol); }
  void setEndPoint(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
    instance->setEndPoint(CANON_POSITION(x, y, z, a, b, c, u, v, w));
    }
  void setEndPoint(const CANON_POSITION& p) { instance->setEndPoint(p); }
  void setG5xOffset(int i, double x, double y, double z, double a, double b, double c, double u, double v, double w) {
    instance->setG5xOffset(i, CANON_POSITION(x, y, z, a, b, c, u, v, w));
    }
  void setG92Offset(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
    instance->setG92Offset(CANON_POSITION(x, y, z, a, b, c, u, v, w));
    }
  void setXYRotation(double r)                  { instance->setXYRotation(r); }
  void setSpindleMode(int spindle, double mode) { instance->setSpindleMode(spindle, mode); }
  void setTraverseColor(const QColor& c)        { instance->setTraverseColor(c); }
  void setFeedColor(const QColor& c)            { instance->setFeedColor(c); }
  void setLimitsColor(const QColor& c)          { instance->setLimitsColor(c); }
  void setCurSegColor(const QColor& c)          { instance->setCurSegColor(c); }
  void setOldSegColor(const QColor& c)          { instance->setOldSegColor(c); }
  void setWorkPieceColor(const QColor& c)       { instance->setWorkPieceColor(c); }
  void setToolOffset(EmcPose offset)            { instance->setToolOffset(offset); }

private:
  class IFSettings
  {
    friend class CanonIF;

  private:
    IFSettings(LcProperties& lcProperties, ToolTable& toolTable);

    double            lengthUnits() const;
    bool              isSpeedOverrideEnabled(int) const  {
      //TODO !
      return speedOverride;
      }
    double            spindleSpeed(int spindle) const;
    CANON_DIRECTION   spindleDir(int spindle) const;
    CANON_TOOL_TABLE  toolEntry(int ttIndex) const;
    CANON_POSITION    g5xOffset(int i) const;
    void changeTool(int ttIndex);
    void setSpindleMode(int spindle, double css_max) {
      canon.spindle[spindle].css_maximum = fabs(css_max);
      }
    void setTraverseColor(const QColor& c);
    void setFeedColor(const QColor& c);
    void setLimitsColor(const QColor& c);
    void setCurSegColor(const QColor& c);
    void setOldSegColor(const QColor& c);
    void setWorkPieceColor(const QColor& c);
    void setEndPoint(const CANON_POSITION& p);
    void setG5xOffset(int i, const CANON_POSITION& p);
    void setMotionMode(CANON_MOTION_MODE mode, double tolerance);
    void setG92Offset(const CANON_POSITION& p) { canon.g92Offset   = p; }
    void setXYRotation(double r)               { canon.xy_rotation = r; }
    void setJobUnits(CANON_UNITS u)            { canon.lengthUnits = u; }
    void selectPlane(CANON_PLANE p)            { canon.activePlane = p; }
    void setToolOffset(EmcPose offset)         { canon.toolOffset  = offset; }

  private:
    LcProperties&       properties;
    ToolTable&          toolTable;
    CanonConfig_t       canon;
    CANON_POSITION      g5xOffsets[9];
    CANON_UNITS         machineUnits;
    StupidToolChangerIF changer;
    GraphicFactory      gf;
    double              iTraverseRate;
    bool                floodActive;
    bool                mistActive;
    bool                feedOverride;
    bool                speedOverride;
    bool                adaptiveFeed;
    bool                feedHold;
    int                 selectedOffset;
    Quantity_Color      colFeed;
    Quantity_Color      colTraverse;
    Quantity_Color      colLimits;
    Quantity_Color      colCurSeg;
    Quantity_Color      colOldSeg;
    Quantity_Color      colWorkPiece;
    QMultiMap<long, Handle(AIS_InteractiveObject)> toolPath;
    };
  static IFSettings* instance;
  };
#endif // CANONIF_H
