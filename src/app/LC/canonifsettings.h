#ifndef CANONIFSETTINGS_H
#define CANONIFSETTINGS_H
//#include <graphicfactory.h>
#include <lcproperties.h>
#include <axismask.h>
#include <stupidtoolchangerif.h>

#include <QObject>
#include <QColor>

#include <AIS_InteractiveObject.hxx>

#include <canon.hh>

class  ToolTable;
class  ToolEntry;
struct CanonConfig_t;
class  CANON_POSITION;
#ifndef CANONIF_CPP
#error This file is not intended for public usage!
#endif


class CanonIFSettings
{
private:
  CanonIFSettings(LcProperties& lcProperties, ToolTable& toolTable);

  void             changeTool(int ttIndex);
  bool             isSpeedOverrideEnabled(int) const  {
                     //TODO !
                     return speedOverride;
                     }
  CANON_POSITION   g5xOffset(int i) const;
  double           lengthUnits() const;
  CANON_TOOL_TABLE canonTool(int ttIndex) const;
  double           spindleSpeed(int spindle) const;
  CANON_DIRECTION  spindleDir(int spindle) const;
  void             selectPlane(CANON_PLANE p);
  void             setCurSegColor(const QColor& c);
  void             setEndPoint(const CANON_POSITION& p);
  void             setFeedColor(const QColor& c);
  void             setG5xOffset(int i, const CANON_POSITION& p);
  void             setG92Offset(const CANON_POSITION& p);
  void             setJobUnits(int u);
  void             setLimitsColor(const QColor& c);
  void             setMotionMode(CANON_MOTION_MODE mm, double tolerance);
  void             setOldSegColor(const QColor& c);
  void             setSpindleMode(int spindle, double css_max);
  void             setToolOffset(const CANON_POSITION& offset);
  void             setTraverseColor(const QColor& c);
  void             setWorkPieceColor(const QColor& c);
  void             setXYRotation(double r);

private:
  LcProperties&       properties;
  ToolTable&          toolTable;
  CanonConfig_t       canon;
  CANON_POSITION      g5xOffsets[9];
  CANON_UNITS         machineUnits;
  StupidToolChangerIF changer;
//  GraphicFactory      gf;
  double              iTraverseRate;
  bool                floodActive;
  bool                mistActive;
  bool                feedOverride;
  bool                speedOverride;
  bool                adaptiveFeed;
  bool                feedHold;
  int                 selectedOffset;
//  Quantity_Color      colFeed;
//  Quantity_Color      colTraverse;
//  Quantity_Color      colLimits;
//  Quantity_Color      colCurSeg;
//  Quantity_Color      colOldSeg;
//  Quantity_Color      colWorkPiece;
  QMultiMap<long, Handle(AIS_InteractiveObject)> toolPath;
  friend class CanonIF;
//  friend class GuiKernel;
//  friend class GuiCore;
  };
#endif // CANONIFSETTINGS_H
