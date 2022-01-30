#ifndef GUICORE_H
#define GUICORE_H
#include <core.h>
#include <utility>
#include <QVector3D>
class ViewPluginInterface;
class AbstractCenterWidget;
class GuiKernelInterface;
class OcctQtViewer;
class DBConnection;
class DBHelper;
class KernelCreator;
class ToolTable;
class LcProperties;
class PageStack;
class Pos9;
class QApplication;
class QMainWindow;
class QCloseEvent;
class QTranslator;
class QLocale;
class QWidget;


class GuiCore : public Core
{
public:
  static const int taskStateOn;
  static const int taskWaiting4Motion;

  explicit GuiCore();
  explicit GuiCore(QApplication& app, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  virtual ~GuiCore() = default;

  void                 riseError(const QString& msg);
  void                 activatePage(const QString& pageName);
  int                  activeGCodes() const;
  int                  activeMCodes() const;
  int                  axisMask() const;
  bool                 checkBE();
  QString              curPage() const;
  double               defaultVelocity(int jointNum = 0) const;
  QString              helpFilename() const;
  bool                 isLatheMode() const;
  void                 help4Keyword(const QString& keyWord);
  LcProperties&        lcProperties();
  std::pair<QVector3D, QVector3D> machineLimits() const;
  QMainWindow*         mainWindow();
  double               maxVelocity(int jointNum = 0) const;
  ViewPluginInterface* pluggableMainPage(const QString& pageID);
  QList<QString>       pluggableMainPages();
  ViewPluginInterface* pluggableNotebookPage(const QString& pageID);
  QList<QString>       pluggableNotebookPages();
  void                 setAppMode4PageID(const QString& pageID);
  void                 setMainWindow(QMainWindow* w);
  void                 setViewStack(PageStack* v);
  void                 setWindowTitle(const QString& title);
  void                 showHelp() const;
  void                 startTimer(int delay = 40);
  QWidget*             stackedPage(const QString& pageName);
  ViewPluginInterface* statusInfo(const QString& infoID);
  QList<QString>       statusInfos();
  void                 stopTimer();
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

  static void setKernelCreator(KernelCreator* kc);

private:
  explicit GuiCore(void* p);
  friend class AbstractCenterWidget;
  };
#endif
