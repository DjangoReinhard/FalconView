#ifndef GUICORE_H
#define GUICORE_H
#include <core.h>
#include <utility>
#include <QVector3D>
class PluginPageInterface;
class AbstractCenterWidget;
class GuiKernelInterface;
class OcctQtViewer;
class DBConnection;
class DBHelper;
class ToolTable;
class LcProperties;
class PageStack;
class Pos9;
class QMainWindow;
class QCloseEvent;
class QTranslator;
class QLocale;
class QWidget;


class GuiCore : public Core
{
public:
  explicit GuiCore();
  explicit GuiCore(QApplication& app, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  virtual ~GuiCore() = default;

  virtual void         riseError(const QString& msg) override;

  void                 activatePage(const QString& pageName);
  int                  activeGCodes() const;
  int                  activeMCodes() const;
  bool                 checkBE();
  QString              curPage() const;
  double               defaultVelocity(int jointNum = 0) const;
  QString              helpFilename() const;
  bool                 isLatheMode() const;
  bool                 isSimulator() const;
  void                 help4Keyword(const QString& keyWord);
  LcProperties&        lcProperties();
  std::pair<QVector3D, QVector3D> machineLimits() const;
  QMainWindow*         mainWindow();
  double               maxVelocity(int jointNum = 0) const;
  PluginPageInterface* pluggableMainPage(const QString& pageID);
  QList<QString>       pluggableMainPages();
  PluginPageInterface* pluggableNotebookPage(const QString& pageID);
  QList<QString>       pluggableNotebookPages();
  void                 setAppMode4PageID(const QString& pageID);
  void                 setMainWindow(QMainWindow* w);
  void                 setViewStack(PageStack* v);
  void                 setWindowTitle(const QString& title);
  void                 showHelp() const;
  QWidget*             stackedPage(const QString& pageName);
  PluginPageInterface* statusInfo(const QString& infoID);
  QList<QString>       statusInfos();
  Pos9                 toolOffset() const;
  ToolTable&           toolTable();
  ToolTable*           toolTableModel();
  OcctQtViewer*        view3D();
  PageStack*           viewStack();
  void                 windowClosing(QCloseEvent* e);

  void beAbortTask();
  void beEnableBlockDelete(bool enable);
  void beEnableFlood(bool enable);
  void beEnableMist(bool enable);
  void beEnableOptionalStop(bool enable);
  void beSetSpindleOverride(double rate);
  void beJogStep(int axis, double stepSize, double speed);
  void beJogStart(int axis, double speed);
  void beJogStop(int axis);
  void beHomeAxis(int jointNum);
  void beLoadTaskPlan(const QString& gcodeFile);
  void beLoadToolTable(const QString& toolTableFile);
  void beSendMDICommand(const QString& command);
  void beSetAuto(int autoMode, int line);
  void beSetFeedOverride(double rate);
  void beSetRapidOverride(double rate);
  void beSetSpindle(bool enable, int speed, int direction);
  void beSetTaskMode(int mode);
  void beSetTaskState(int state);
  void beTaskPlanSynch();

private:
  explicit GuiCore(void* p);
  GuiKernelInterface*       guiCore();
  const GuiKernelInterface* guiCore() const;
  friend class AbstractCenterWidget;
  };
#endif
