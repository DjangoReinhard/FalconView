#ifndef CANONIFSETTINGS_H
#define CANONIFSETTINGS_H
#include <QObject>
#include <QColor>
#include <graphicfactory.h>
#include <lcproperties.h>
#include <axismask.h>
#include <stupidtoolchangerif.h>
#include <canon.hh>
class ToolTable;
struct CanonConfig_t;


class CanonIFSettings
{
private:
  CanonIFSettings(LcProperties& lcProperties, ToolTable& toolTable);

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
  friend class CanonIF;
  friend class GuiKernel;
  friend class GuiCore;
  };

#endif // CANONIFSETTINGS_H
