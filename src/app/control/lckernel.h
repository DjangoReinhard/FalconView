/* 
 * **************************************************************************
 * 
 *  file:       lckernel.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
#ifndef LCKERNEL_H
#define LCKERNEL_H
#ifdef REDNOSE
#include <guikernel.h>
#include <AIS_InteractiveObject.hxx>
class DBConnection;
class LCProperties;
class OcctQtViewer;
class PageStack;
class PluginPageInterface;
class Pos9;
class ToolTable;

class QList<QString>;
class QLocale;
class QMainWindow;
class QString;
class QStringList;
class QVector3D;
class QWidget;


class LCKernel : public GuiKernel
{
  Q_OBJECT
public:
  LCKernel();

  /** #######################   Init   ############################ */
  DBConnection*     createDatabase(DBHelper& dbAssist);
  virtual void      initialize(DBHelper& dbAssist) override;
  virtual void      processAppArgs(const QStringList& args);
  virtual QLocale*  setupTranslators();
  void              setupToolTable();

  /** #######################   LinuxCNC   ######################## */
  CANON_PLANE       activePlane() const;
  int               activeSpindle() const;
  void              appendShape(int lineNum, Handle(AIS_InteractiveObject) shape);
  void              beAbortTask();
  void              beEnableBlockDelete(bool enable);
  void              beEnableFlood(bool enable);
  void              beEnableMist(bool enable);
  void              beEnableOptionalStop(bool enable);
  void              beHomeAxis(int jointNum);
  void              beJogStart(int axis, double speed);
  void              beJogStep(int axis, double stepSize, double speed);
  void              beJogStop(int axis);
  void              beLoadTaskPlan(const QString& gcodeFile);
  void              beLoadToolTable(const QString& toolTableFile);
  void              beSendMDICommand(const QString& command);
  void              beSetAuto(int autoMode, int line);
  void              beSetFeedOverride(double rate);
  void              beSetRapidOverride(double rate);
  void              beSetSpindle(bool enable, int speed, int direction);
  void              beSetSpindleOverride(double rate);
  void              beSetTaskMode(int mode);
  void              beSetTaskState(int state);
  void              beTaskPlanSynch();
  void              changeTool(int ttIndex);
  double            convert(double v);
  CANON_POSITION    endPoint() const;
  double            feedRate() const;
  CANON_POSITION    g5xOffset(int i=0) const;
  CANON_POSITION    g92Offset() const;
  GraphicFactory    graphicFactory() const;
  bool              isAdaptiveFeedEnabled() const;
  bool              isFeedHoldActive() const;
  bool              isFeedOverrideEnabled() const;
  bool              isFloodActive() const;
  bool              isMistActive() const;
  bool              isSpeedOverrideEnabled(int spindle) const;
  int               lastSlot() const;
  LcProperties&     lcProperties() const;
  double            lengthUnits() const;
  CANON_UNITS       machineUnits() const;
  CANON_MOTION_MODE motionMode() const;
  double            motionTolerance() const;
  double            naiveTolerance() const;
  int               nextSlot() const;
  QString           parameterFilename() const;
  double            posA() const;
  double            posB() const;
  double            posC() const;
  double            posU() const;
  double            posV() const;
  double            posW() const;
  double            posX() const;
  double            posY() const;
  double            posZ() const;
  int               selectedOffset() const;
  void              selectPlane(CANON_PLANE pl);
  void              selectTool(int tool);
  void              setEndPoint(const CANON_POSITION& p);
  void              setEndPoint(double x, double y, double z, double a, double b, double c, double u, double v, double w);
  void              setG5xOffset(int i, double x, double y, double z, double a, double b, double c, double u, double v, double w);
  void              setG92Offset(double x, double y, double z, double a, double b, double c, double u, double v, double w);
  void              setLengthUnits(CANON_UNITS u);
  void              setMotionMode(CANON_MOTION_MODE mode, double tol);
  void              setSpindleMode(int spindle, double mode);
  void              setToolOffset(EmcPose offset);
  void              setTraverseColor(const QColor& c);
  void              setXYRotation(double r);
  CANON_DIRECTION   spindleDir(int spindle) const;
  double            spindleSpeed(int spindle) const;
  CANON_TOOL_TABLE  toolEntry(int ttIndex);
  CANON_POSITION    toolOffset() const;
  QMap<long, Handle(AIS_InteractiveObject)>& toolPath();
  double            traverseRate() const;
  double            xyRotation() const;

signals:
  void              abortTask();                                        // command
  void              enableBlockDelete(bool enable);                     // command
  void              enableFlood(bool enable);                           // command
  void              enableMist(bool enable);                            // command
  void              enableOptionalStop(bool enable);                    // command
  void              homeAxis(int jointNum);                             // command
  void              jogStart(int axis, double speed);                   // command
  void              jogStep(int axis, double stepSize, double speed);   // command
  void              jogStop(int axis);                                  // command
  void              loadTaskPlan(const QString& gcodeFile);             // command
  void              loadToolTable(const QString& toolTableFile);        // command
  void              sendMDICommand(const QString& command);             // command
  void              setAuto(int autoMode, int line);                    // command
  void              setFeedOverride(double rate);                       // command
  void              setRapidOverride(double rate);                      // command
  void              setSpindle(bool enable, int speed, int direction);  // command
  void              setSpindleOverride(double rate);                    // command
  void              setTaskMode(int mode);                              // command
  void              setTaskState(int state);                            // command
  void              taskPlanSynch();                                    // command

  /** #######################   GUI   ############################# */
  void                 activatePage(const QString& pageName);
  bool                 checkBE();
  QString              curPage() const;
  void                 help4Keyword(const QString& keyWord);
  QString              helpFilename() const;
  bool                 isLatheMode() const;
  bool                 isSimulator() const;
  LcProperties&        lcProperties();
  QMainWindow*         mainWindow();
  void                 parseInline(const QString& fileName);
  PluginPageInterface* pluggableMainPage(const QString pageID);
  QList<QString>       pluggableMainPages();
  PluginPageInterface* pluggableNotebookPage(const QString pageID);
  QList<QString>       pluggableNotebookPages();
  void                 processGCodeFile(const QString& fileName);
  std::pair<QVector3D, QVector3D> machineLimits() const;
  std::pair<QVector3D, QVector3D> machineLimits() const;
  void                 setAppMode4PageID(const QString& pageID);
  void                 setMainWindow(QMainWindow* w);
  void                 setViewStack(PageStack* v);
  void                 setWindowTitle(const QString& title);
  void                 showHelp() const;
  QWidget*             stackedPage(const QString& pageName);
  PluginPageInterface* statusInfo(const QString infoID);
  QList<QString>       statusInfos();
  Pos9                 toolOffset() const;
  ToolTable&           toolTable();
  ToolTable*           toolTableModel();
  OcctQtViewer*        view3D();
  PageStack*           viewStack();
  void                 windowClosing(QCloseEvent* e);

  /** #######################   Base   ############################ */
  int           axisMask() const override;
  DBConnection* databaseConnection();
  QString       fileName4(const QString& fileID) const override;
  bool          isSimulator() const;
  bool          isLatheMode() const;
  QString       languagePrefix() const;
  void          logSysEvent(const QString& msg) override;
  void          logSysEvent(const SysEvent& se) override;
  bool          move2Backup(const QString& fileName);
  void          processGCodeFile(const QVariant& fileName);
  void          riseError(const QString& msg) override;
  void          setAppMode(ApplicationMode m);
  void          setupBackend();
  void          showAllButCenter(bool visible);
  bool          showHelpAtPageChange() const;
  void          updateView(const QVariant& pos);
  QString       version() const;
  void          windowClosing(QCloseEvent* e);

protected slots:
  void                 nop() const;
  virtual void         timerEvent(QTimerEvent* e) override;
  virtual void         usage();
  };
#endif
#endif // LCKERNEL_H
