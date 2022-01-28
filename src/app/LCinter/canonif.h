#ifndef CANONIF_H
#define CANONIF_H
#include <QObject>
#include <QColor>

#include <canon.hh>

#ifdef toLine
# undef toLine
#endif

class  ToolTable;
class  CanonIFSettings;
struct CanonConfig_t;
class  LcProperties;
class  GraphicElement;
class  GraphicFactory;
class  AIS_InteractiveObject;
class  Quantity_Color;


/**
 * @brief The data-storage counterpart of linuxcnc interpreter.
 * linuxcnc interpreter uses capitalized c-functions to interact with external
 * world.
 */
class CanonIF
{
public:
  CanonIF(LcProperties& lcProperties, ToolTable& toolTable);
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
  void              appendShape(int lineNum, GraphicElement* ge);
  Quantity_Color    feedColor() const;
  Quantity_Color    traverseColor() const;
//  Quantity_Color    curSegColor() const;
//  Quantity_Color    limitsColor() const;
//  Quantity_Color    oldSegColor() const;
//  Quantity_Color    workPieceColor() const;

  QMap<long, GraphicElement*>& toolPath();
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
  void setFeedColor(const QColor& c);
  void setTraverseColor(const QColor& c);
//  void setCurSegColor(const QColor& c);
//  void setLimitsColor(const QColor& c);
//  void setOldSegColor(const QColor& c);
//  void setWorkPieceColor(const QColor& c);
  void setSpindleMode(int spindle, double mode);
  void setToolOffset(EmcPose offset);

private:
  static CanonIFSettings* p;
  };
#endif // CANONIF_H
