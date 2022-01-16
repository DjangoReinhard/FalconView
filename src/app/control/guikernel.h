#ifndef GUIKERNEL_H
#define GUIKERNEL_H
#include <kernel.h>
#include <GuiKernelInterface.h>
#include <gcodeinfo.h>
#include <positioncalculator.h>
#include <QThread>

class PluginPageInterface;
class LcProperties;
class ToolTable;
class AxisMask;
class SysEventModel;
class OcctQtViewer;
class HelpDockable;
class Ally3D;
class PageStack;
class QMainWindow;
class StatusReader;
class CommandWriter;
class QVariant;
class CanonIF;
class LCInterface;
class QTimerEvent;
class QCloseEvent;


class GuiKernel : public Kernel, public GuiKernelInterface
{
  Q_OBJECT
public:
  virtual int            axisMask() const override;
//  virtual ConfigManager* config() const override;
//  virtual ConfigManager* config() override;
  virtual DBConnection*  createDatabase(DBHelper& dbAssist);
//  virtual DBConnection*  databaseConnection() override;
  virtual QString        fileName4(const QString& fileID) const override;
  virtual void           initialize(DBHelper& dbAssist) override;
//  virtual QLocale        locale() const override;
  virtual void           logSysEvent(const QString& msg) override;
  virtual void           logSysEvent(const SysEvent& se) override;
  virtual void           timerEvent(QTimerEvent* e) override;

  virtual void                 activatePage(const QString& pageName) override;
  virtual int                  activeGCodes() const override;
  virtual int                  activeMCodes() const override;
  virtual QString              activePage() const override;
  virtual QString              curPage() const override;
  virtual double               defaultVelocity(int jointNum = 0) const override;
  virtual void                 help4Keyword(const QString& keyWord) override;
  virtual QMainWindow*         mainWindow() override;
  virtual double               maxVelocity(int jointNum = 0) const override;
  virtual PluginPageInterface* pluggableMainPage(const QString& pageID) const override;
  virtual QList<QString>       pluggableMainPages() const override;
  virtual PluginPageInterface* pluggableNotebookPage(const QString& pageID) const override;
  virtual QList<QString>       pluggableNotebookPages() const override;
  virtual void                 setAppMode4PageID(const QString& pageID) override;
  virtual void                 setMainWindow(QMainWindow* w) override;
  virtual void                 setViewStack(PageStack* v) override;
  virtual void                 setWindowTitle(const QString& title) override;
  virtual void                 showHelp() const override;
  virtual QWidget*             stackedPage(const QString& pageName) override;
  virtual PluginPageInterface* statusInfo(const QString& infoID) const override;
  virtual QList<QString>       statusInfos() const override;
  virtual PageStack*           viewStack() override;

  virtual void beAbortTask();
  virtual void beEnableBlockDelete(bool enable);
  virtual void beEnableFlood(bool enable);
  virtual void beEnableMist(bool enable);
  virtual void beEnableOptionalStop(bool enable);
  virtual void beSetSpindleOverride(double rate);
  virtual void beJogStep(int axis, double stepSize, double speed);
  virtual void beJogStart(int axis, double speed);
  virtual void beJogStop(int axis);
  virtual void beHomeAxis(int jointNum);
  virtual void beLoadTaskPlan(const QString& gcodeFile);
  virtual void beLoadToolTable(const QString& toolTableFile);
  virtual void beSendMDICommand(const QString& command);
  virtual void beSetAuto(int autoMode, int line);
  virtual void beSetFeedOverride(double rate);
  virtual void beSetRapidOverride(double rate);
  virtual void beSetSpindle(bool enable, int speed, int direction);
  virtual void beSetTaskMode(int mode);
  virtual void beSetTaskState(int state);
  virtual void beTaskPlanSynch();

  virtual bool                            checkBE() override;
  virtual bool                            isLatheMode() const override;
  virtual bool                            isSimulator() const override;
  virtual LcProperties&                   lcProperties() override;
  virtual const LcProperties&             lcProperties() const override;
  virtual std::pair<QVector3D, QVector3D> machineLimits() const override;
  virtual void                            nop() const override;
  virtual void                            processGCodeFile(const QVariant& fileName) override;
  virtual void                            setupBackend() override;
//  virtual QLocale*                        setupTranslators() override;
  virtual Pos9                            toolOffset() const override;
  virtual ToolTable&                      toolTable() override;
  virtual ToolTable*                      toolTableModel() override;
  virtual void                            updateView(const QVariant& pos) override;
  virtual OcctQtViewer*                   view3D() override;
//  virtual QString                         version() const override;
  virtual void                            windowClosing(QCloseEvent* e) override;

protected:
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
  const int          maxGCodes;
  const int          maxMCodes;
  LcProperties*      lcProps;
  ToolTable*         tt;
  LCInterface*       lcIF;
  AxisMask*          mAxis;
  OcctQtViewer*      v3D;
  PageStack*         centerView;
  QMainWindow*       wMain;
  HelpDockable*      help;
  Ally3D*            ally3D;
  GCodeInfo          gcodeInfo;
  PositionCalculator positionCalculator;
  StatusReader*      statusReader;
  CommandWriter*     commandWriter;
  QThread            backendCommThread;
  SysEventModel*     sysEvents;
  CanonIF*           canonIF;
  QString            iniFileName;
  QString            helpFileName;
  QString            nc_files;
  QString            pluginDir;
  QMap<QString, PluginPageInterface*> mainPages;
  QMap<QString, PluginPageInterface*> nbPages;
  QMap<QString, PluginPageInterface*> statInfos;
  friend class GuiKernelCreator;
  friend class GuiCore;
  };
#endif // GUIKERNEL_H
