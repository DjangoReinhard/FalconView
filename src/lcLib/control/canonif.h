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
class CanonIFSettings;
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
//  CanonIF(LcProperties& lcProperties, ToolTable& toolTable);
  CanonIF();

  LcProperties&     lcProperties() const;
  CANON_UNITS       machineUnits() const;
  double            lengthUnits() const;
  double            feedRate() const;
  double            traverseRate() const;
  bool              isFeedOverrideEnabled() const;
  bool              isAdaptiveFeedEnabled() const;
  bool              isFeedHoldActive() const;
  bool              isFloodActive() const;
  bool              isMistActive() const;
  int               activeSpindle() const;
  CANON_PLANE       activePlane() const;
  CANON_MOTION_MODE motionMode() const;
  GraphicFactory    graphicFactory() const;
  double            motionTolerance() const;
  double            naiveTolerance() const;
  double            posX() const;
  double            posY() const;
  double            posZ() const;
  double            posA() const;
  double            posB() const;
  double            posC() const;
  double            posU() const;
  double            posV() const;
  double            posW() const;
  int               lastSlot() const;
  int               nextSlot() const;
  Quantity_Color    traverseColor() const;
  Quantity_Color    feedColor() const;
  Quantity_Color    limitColor() const;
  Quantity_Color    curSegColor() const;
  Quantity_Color    oldSegColor() const;
  Quantity_Color    workPieceColor() const;
  CANON_TOOL_TABLE  toolEntry(int ttIndex);
  CANON_POSITION    g5xOffset(int i=0) const;
  CANON_POSITION    g92Offset() const;
  double            xyRotation() const;
  int               selectedOffset() const;
  bool              isSpeedOverrideEnabled(int spindle) const;
  double            spindleSpeed(int spindle) const;
  CANON_DIRECTION   spindleDir(int spindle) const;
  CANON_POSITION    toolOffset() const;
  CANON_POSITION    endPoint() const;
  QString           parameterFilename() const;
  double            convert(double v);
  void              appendShape(int lineNum, Handle(AIS_InteractiveObject) shape);
  QMap<long, Handle(AIS_InteractiveObject)>& toolPath();
  void changeTool(int ttIndex);
  void selectTool(int tool);
  void setLengthUnits(CANON_UNITS u);
  void selectPlane(CANON_PLANE pl);
  void setMotionMode(CANON_MOTION_MODE mode, double tol);
  void setEndPoint(double x, double y, double z, double a, double b, double c, double u, double v, double w);
  void setEndPoint(const CANON_POSITION& p);
  void setG5xOffset(int i, double x, double y, double z, double a, double b, double c, double u, double v, double w);
  void setG92Offset(double x, double y, double z, double a, double b, double c, double u, double v, double w);
  void setXYRotation(double r);
  void setSpindleMode(int spindle, double mode);
  void setTraverseColor(const QColor& c);
  void setFeedColor(const QColor& c);
  void setLimitsColor(const QColor& c);
  void setCurSegColor(const QColor& c);
  void setOldSegColor(const QColor& c);
  void setWorkPieceColor(const QColor& c);
  void setToolOffset(EmcPose offset);

private:
  CanonIFSettings*       instance();
  const CanonIFSettings* instance() const;
  };
#endif // CANONIF_H
