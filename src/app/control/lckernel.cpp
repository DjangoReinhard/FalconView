#include <lckernel.h>
#include <axismask.h>
#include <ally3d.h>
#include <configmgr.h>
#include <gcodeinfo.h>
#include <helpdockable.h>
#include <syseventmodel.h>

#include <commandwriter.h>
#include <lcproperties.h>
#include <LCInter.h>
#include <positioncalculator.h>
#include <statusreader.h>

#include <QApplication>
#include <QBasicTimer>
#include <QLocale>
#include <QMap>
#include <QString>
#include <QThread>


class LCKernelP
{
public:
  /** ###################   APP   #####################*/
  QApplication&       app;
  QString             appName;
  QThread             backendCommThread;
  ConfigManager*      cfg;
  DBConnection*       conn;
  QString             langDir;
  QLocale*            locale;

  /** ###################   GUI   #####################*/
  PageStack*          centerView;
  HelpDockable*       help;
  QString             helpFileName;
  QMap<QString, PluginPageInterface*> mainPages;
  QMainWindow*        mainWindow;
  QMap<QString, PluginPageInterface*> nbPages;
  QString             pluginDir;
  QMap<QString, PluginPageInterface*> statusInfos;
  SysEventModel*      sysEvents;
  QBasicTimer         timer;

  /** ###################   LinxCNC   #################*/
  bool                adaptiveFeed;
  Ally3D*             ally3D;
  CanonIF&            canon;
  CanonConfig_t       cfgCanon;
  StupidToolChangerIF changer;
  QProcess*           child;
  CommandWriter*      commandWriter;
  EMC_STAT*           emcStatus;
  int                 errInter;
  bool                feedHold;
  bool                feedOverride;
  bool                floodActive;
  CANON_POSITION      g5xOffsets[9];
  GCodeInfo           gcodeInfo;
  GraphicFactory      gf;
  QString             groupID;
  QMultiMap<long, Handle(AIS_InteractiveObject)> toolPath;  
  QString             iniFileName;
  double              iTraverseRate;  
  int                 lastSeqNum;
  LCInterface*        lcIF;
  LcProperties&       lcProperties;
  CANON_UNITS         machineUnits;  
  AxisMask*           mAxis;
  bool                mistActive;  
  InterpBase*         pInter;  
  PositionCalculator  positionCalculator;
  int                 selectedOffset;
  bool                simulator;
  bool                speedOverride;  
  StatusReader*       statusReader;  
  EMC_TOOL_STAT*      toolStatus;
  ToolTable&          toolTable;
  OcctQtViewer*       view3D;
  double              xLast;
  double              yLast;
  double              zLast;
  };



LCKernel::LCKernel() {
  }
