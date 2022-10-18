/* 
 * **************************************************************************
 * 
 *  file:       guikernel.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    30.1.2022 by Django Reinhard
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
#ifndef GUIKERNEL_H
#define GUIKERNEL_H
#include <kernel.h>
#include <KernelInterface.h>
#include <gcodeinfo.h>
#include <positioncalculator.h>
#include <QBasicTimer>
#include <QThread>

class ViewPluginInterface;
class LcProperties;
class ToolTable;
class AxisMask;
class SysEventModel;
class OcctQtViewer;
class HelpDockable;
class LCStatus;
class Ally3D;
class PageStack;
class QMainWindow;
class AbstractStatusReader;
class StatusUpdater;
class CommandWriter;
class CanonIF;
class LCInterface;
class QApplication;
class QVariant;
class QTimerEvent;
class QCloseEvent;


class GuiKernel : public QObject, public KernelInterface
{
  Q_OBJECT
protected:
  virtual int            axisMask() const override;
  virtual ConfigManager* config() const override;
  virtual ConfigManager* config() override;
  virtual DBConnection*  createDatabase(DBHelperInterface& dbAssist);
  virtual DBConnection*  databaseConnection() override;
  virtual QString        fileName4(const QString& fileID) const override;
  virtual void           initialize(DBHelperInterface& dbAssist) override;
  virtual QLocale        locale() const override;
  virtual void           logSysEvent(const QString& msg) override;
  virtual void           logSysEvent(const SysEvent& se) override;
  virtual QLocale*       setupTranslators() override;
  virtual QString        version() const override;
  virtual void           loadPlugins();

  virtual void                 activatePage(const QString& pageName) override;
  virtual int                  activeGCodes() const override;
  virtual int                  activeMCodes() const override;
  virtual QString              activePage() const override;
  virtual QString              curPage() const override;
  virtual double               defaultVelocity(int jointNum = 0) const override;
  virtual void                 help4Keyword(const QString& keyWord) override;
  virtual QMainWindow*         mainWindow() override;
  virtual double               maxVelocity(int jointNum = 0) const override;
  virtual ViewPluginInterface* pluggableMainPage(const QString& pageID) const override;
  virtual QList<QString>       pluggableMainPages() const override;
  virtual ViewPluginInterface* pluggableNotebookPage(const QString& pageID) const override;
  virtual QList<QString>       pluggableNotebookPages() const override;
  virtual void                 setAppMode4PageID(const QString& pageID) override;
  virtual void                 setMainWindow(QMainWindow* w) override;
  virtual void                 setViewStack(PageStack* v) override;
  virtual void                 setWindowTitle(const QString& title) override;
  virtual void                 showHelp() const override;
  virtual QWidget*             stackedPage(const QString& pageName) override;
  virtual void                 startTimer(int delay = 400) override;
  virtual void                 stopTimer() override;
  virtual ViewPluginInterface* statusInfo(const QString& infoID) const override;
  virtual QList<QString>       statusInfos() const override;
  virtual void                 updateStatus(const LCStatus& status);
  virtual PageStack*           viewStack() override;

  virtual void timerEvent(QTimerEvent* e) override;
  virtual void beAbortTask() override;
  virtual void beEnableBlockDelete(bool enable) override;
  virtual void beEnableFlood(bool enable) override;
  virtual void beEnableMist(bool enable) override;
  virtual void beEnableOptionalStop(bool enable) override;
  virtual void beSetSpindleOverride(double rate) override;
  virtual void beJogStep(int axis, double stepSize, double speed) override;
  virtual void beJogStart(int axis, double speed) override;
  virtual void beJogStop(int axis) override;
  virtual void beHomeAxis(int jointNum) override;
  virtual void beLoadTaskPlan(const QString& gcodeFile) override;
  virtual void beLoadToolTable(const QString& toolTableFile) override;
  virtual void beSendMDICommand(const QString& command) override;
  virtual void beSetAuto(int autoMode, int line) override;
  virtual void beSetFeedOverride(double rate) override;
  virtual void beSetRapidOverride(double rate) override;
  virtual void beSetSpindle(bool enable, int speed, int direction) override;
  virtual void beSetTaskMode(int mode) override;
  virtual void beSetTaskState(int state) override;
  virtual void beTaskPlanSynch() override;

  virtual bool                            checkBE() override;
  virtual bool                            isLatheMode() const override;
  virtual bool                            isSimulator() const override;
  virtual LcProperties&                   lcProperties() override;
  virtual const LcProperties&             lcProperties() const override;
  virtual std::pair<QVector3D, QVector3D> machineLimits() const override;
  virtual void                            nop() const override;
  virtual void                            processGCodeFile(const QVariant& fileName) override;
  virtual void                            setupBackend() override;
  virtual Pos9                            toolOffset() const override;
  virtual ToolTable&                      toolTable() override;
  virtual ToolTable*                      toolTableModel() override;
  virtual void                            updateView(const QVariant& pos) override;
  virtual OcctQtViewer*                   view3D() override;
  virtual void                            windowClosing(QCloseEvent* e) override;

//protected:
  explicit GuiKernel(int maxGCodes, int maxMCodes, QApplication& app, const QString& appName, const QString& groupID);
  virtual ~GuiKernel() = default;

  virtual void usage();
  virtual void processAppArgs(const QStringList& args) override;

signals:
  void abortTask();
  void enableBlockDelete(bool enable);
  void enableFlood(bool enable);
  void enableMist(bool enable);
  void enableOptionalStop(bool enable);
  void setSpindleOverride(double rate);
  void jogStep(int axis, double stepSize, double speed);
  void jogStart(int axis, double speed);
  void jogStop(int axis);
  void homeAxis(int jointNum);
  void loadTaskPlan(const QString& gcodeFile);
  void loadToolTable(const QString& toolTableFile);
  void sendMDICommand(const QString& command);
  void setAuto(int autoMode, int line);
  void setFeedOverride(double rate);
  void setRapidOverride(double rate);
  void setSpindle(bool enable, int speed, int direction);
  void setTaskMode(int mode);
  void setTaskState(int state);
  void taskPlanSynch();

private:
  const int             maxGCodes;
  const int             maxMCodes;
  int                   checked;
  int                   portMulticast;
  bool                  simulator;
  bool                  useNML;
  QApplication&         app;
  ConfigManager*        cfg;
  QLocale*              curLocale;
  DBConnection*         conn;
  QString               appName;
  QString               groupID;
  QString               langDir;
  QBasicTimer           timer;
  LcProperties*         lcProps;
  ToolTable*            tt;
  LCInterface*          lcIF;
  AxisMask*             mAxis;
  OcctQtViewer*         v3D;
  PageStack*            centerView;
  QMainWindow*          wMain;
  HelpDockable*         help;
  Ally3D*               ally3D;
  GCodeInfo             gcodeInfo;
  PositionCalculator    positionCalculator;
  AbstractStatusReader* statusReader;
  StatusUpdater*        statusUpdater;
  CommandWriter*        commandWriter;
  QThread               backendCommThread;
  QThread               backendStatThread;
  SysEventModel*        sysEvents;
  CanonIF*              canonIF;
  QString               iniFileName;
  QString               helpFileName;
  QString               nc_files;
  QString               pluginDir;
  QList<DBHelperInterface*>      dbAssistants;
  QMap<QString, ViewPluginInterface*> mainPages;
  QMap<QString, ViewPluginInterface*> nbPages;
  QMap<QString, ViewPluginInterface*> statInfos;
  friend class GuiKernelCreator;
  friend class GuiCore;
  };
#endif // GUIKERNEL_H
