#ifndef CANONIF_H
#define CANONIF_H
#include <QObject>
#include <QColor>
#include <graphicfactory.h>
#include <axismask.h>
#include <stupidtoolchangerif.h>
#include <canon.hh>
class LcProperties;
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

  CANON_UNITS       machineUnits() const            { return instance->defaultUnits(); }
  double            lengthUnits() const             { return instance->lengthUnits(); }
  int               axisMask() const                { return instance->axisMask(); }
  double            feedRate() const                { return instance->feedRate(); }
  double            traverseRate() const            { return instance->traverseRate(); }
  bool              isFeedOverrideEnabled() const   { return instance->isFeedOverrideEnabled(); }
  bool              isAdaptiveFeedEnabled() const   { return instance->isAdaptiveFeedEnabled(); }
  bool              isFeedHoldActive() const        { return instance->isFeedHoldActive(); }
  bool              isFloodActive() const           { return instance->isFloodActive(); }
  bool              isMistActive() const            { return instance->isMistActive(); }
  int               activeSpindle() const           { return instance->activeSpindle(); }
  CANON_PLANE       activePlane() const             { return instance->activePlane(); }
  CANON_MOTION_MODE motionMode() const              { return instance->motionMode(); }
  GraphicFactory    graphicFactory() const          { return instance->gf; }
  double            motionTolerance() const         { return instance->motionTolerance(); }
  double            naiveTolerance() const          { return instance->naiveTolerance(); }
  double            posX() const                    { return instance->posX(); }
  double            posY() const                    { return instance->posY(); }
  double            posZ() const                    { return instance->posZ(); }
  double            posA() const                    { return instance->posA(); }
  double            posB() const                    { return instance->posB(); }
  double            posC() const                    { return instance->posC(); }
  double            posU() const                    { return instance->posU(); }
  double            posV() const                    { return instance->posV(); }
  double            posW() const                    { return instance->posW(); }
  int               lastSlot() const                { return instance->lastSlot(); }
  int               nextSlot() const                { return instance->nextSlot(); }
  Quantity_Color    traverseColor() const           { return instance->traverseColor(); }
  Quantity_Color    feedColor() const               { return instance->feedColor(); }
  Quantity_Color    limitColor() const              { return instance->limitColor(); }
  CANON_TOOL_TABLE  toolEntry(int ttIndex)          { return instance->toolEntry(ttIndex); }
  CANON_POSITION    g5xOffset() const               { return instance->g5xOffset(); }
  CANON_POSITION    g92Offset() const               { return instance->g92Offset(); }
  double            xyRotation() const              { return instance->xyRotation(); }
  bool              isSpeedOverrideEnabled(int spindle) const  { return instance->isSpeedOverrideEnabled(spindle); }
  double            spindleSpeed(int spindle) const { return instance->spindleSpeed(spindle); }
  CANON_DIRECTION   spindleDir(int spindle) const   { return instance->spindleDir(spindle); }
  CANON_POSITION    toolOffset() const              { return instance->toolOffset(); }
  CANON_POSITION    endPoint() const                { return instance->endPoint(); }
  double            convert(double v);
  QList<Handle(AIS_InteractiveObject)>& toolPath()  { return instance->toolPath; }
  void changeTool(int ttIndex)       { instance->changeTool(ttIndex); }
  void selectTool(int tool)          { instance->selectTool(tool); }
  void setLengthUnits(CANON_UNITS u) { instance->setJobUnits(u); }
  void selectPlane(CANON_PLANE pl)   { instance->selectPlane(pl); }
  void setMotionMode(CANON_MOTION_MODE mode, double tol) { instance->setMotionMode(mode, tol); }
  void setEndPoint(double x, double y, double z, double a, double b, double c, double u, double v, double w) {
    instance->setEndPoint(CANON_POSITION(x, y, z, a, b, c, u, v, w));
    }
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
  void setToolOffset(EmcPose offset)            { instance->setToolOffset(offset); }

private:
  class IFSettings
  {
    friend class CanonIF;

  private:
    IFSettings(LcProperties& lcProperties, ToolTable& toolTable);

    int               axisMask() const;
    double            lengthUnits() const;
    CANON_UNITS       defaultUnits() const            { return machineUnits; }
    double            feedRate() const                { return canon.linearFeedRate; }
    double            traverseRate() const            { return iTraverseRate; }
    bool              isFeedOverrideEnabled() const   { return feedOverride; }
    bool              isAdaptiveFeedEnabled() const   { return adaptiveFeed; }
    bool              isFeedHoldActive() const        { return feedHold; }
    bool              isFloodActive() const           { return floodActive; }
    bool              isMistActive() const            { return mistActive; }
    int               activeSpindle() const           { return canon.spindle_num; }
    CANON_PLANE       activePlane() const             { return canon.activePlane; }
    CANON_MOTION_MODE motionMode() const              { return canon.motionMode; }
    CANON_POSITION    endPoint() const                { return canon.endPoint; }
    double            motionTolerance() const         { return canon.motionTolerance; }
    double            naiveTolerance() const          { return canon.naivecamTolerance; }
    double            posX() const                    { return canon.endPoint.x; }
    double            posY() const                    { return canon.endPoint.y; }
    double            posZ() const                    { return canon.endPoint.z; }
    double            posA() const                    { return canon.endPoint.a; }
    double            posB() const                    { return canon.endPoint.b; }
    double            posC() const                    { return canon.endPoint.c; }
    double            posU() const                    { return canon.endPoint.u; }
    double            posV() const                    { return canon.endPoint.v; }
    double            posW() const                    { return canon.endPoint.w; }
    int               lastSlot() const                { return changer.slot4ToolInSpindle(); }
    int               nextSlot() const                { return changer.nextTool(); }
    Quantity_Color    traverseColor() const           { return colTraverse; }
    Quantity_Color    feedColor() const               { return colFeed; }
    Quantity_Color    limitColor() const              { return colLimits; }
    bool              isSpeedOverrideEnabled(int) const  {
      //TODO !
      return speedOverride;
      }
    double            spindleSpeed(int spindle) const;
    CANON_DIRECTION   spindleDir(int spindle) const;
    CANON_TOOL_TABLE  toolEntry(int ttIndex) const;
    CANON_POSITION    g5xOffset() const               { return canon.g5xOffset; }
    CANON_POSITION    g92Offset() const               { return canon.g92Offset; }
    double            xyRotation() const              { return canon.xy_rotation; }
    void changeTool(int ttIndex);
    void selectTool(int toolNum)                      { changer.selectNextTool(toolNum); }
    CANON_POSITION    toolOffset() const              { return canon.toolOffset; }
    void setJobUnits(CANON_UNITS u)                   { canon.lengthUnits = u; }
    void setSpindleMode(int spindle, double css_max) {
      canon.spindle[spindle].css_maximum = fabs(css_max);
      }
    void setTraverseColor(const QColor& c);
    void setFeedColor(const QColor& c);
    void setLimitsColor(const QColor& c);
    void setEndPoint(const CANON_POSITION& p);
    void setG5xOffset(int i, const CANON_POSITION& p);
    void setMotionMode(CANON_MOTION_MODE mode, double tolerance);
    void setG92Offset(const CANON_POSITION& p)        { canon.g92Offset   = p; }
    void setXYRotation(double r)                      { canon.xy_rotation = r; }
    void selectPlane(CANON_PLANE p)                   { canon.activePlane = p; }
    void setToolOffset(EmcPose offset)                { canon.toolOffset  = offset; }

  private:
    LcProperties&                        properties;
    ToolTable&                           toolTable;
    CanonConfig_t                        canon;
    CANON_POSITION                       g5xOffsets[9];
    CANON_UNITS                          machineUnits;
    AxisMask                             axisPresent;
    StupidToolChangerIF                  changer;
    GraphicFactory                       gf;
    QList<Handle(AIS_InteractiveObject)> toolPath;
    double                               iTraverseRate;
    bool                                 floodActive;
    bool                                 mistActive;
    bool                                 feedOverride;
    bool                                 speedOverride;
    bool                                 adaptiveFeed;
    bool                                 feedHold;
    Quantity_Color                       colFeed;
    Quantity_Color                       colTraverse;
    Quantity_Color                       colLimits;
    };
  static IFSettings* instance;
  };
#endif // CANONIF_H
