#ifndef GUICORE_H
#define GUICORE_H
#include <core.h>
#include <canon.hh>

class PluginPageInterface;
class AbstractCenterWidget;
class GuiKernel;
class OcctQtViewer;
class DBConnection;
class DBHelper;
class QMainWindow;
class ToolTable;
class LcProperties;
class CenterView;
class QCloseEvent;
class QTranslator;
class QLocale;
class QWidget;


class GuiCore : public Core
{
public:
  explicit GuiCore();
  explicit GuiCore(const QString& iniFileName, const QString& appName, const QLocale& locale, DBHelper& dbAssist, const QString& group = "SRD");
  virtual ~GuiCore() = default;

  virtual void         riseError(const QString& msg);

  void                 activatePage(const QString& pageName);
  bool                 checkBE();
  QString              curPage() const;
  QString              helpFilename() const;
  bool                 isLatheMode() const;
  bool                 isSimulator() const;
  LcProperties&        lcProperties();
  QMainWindow*         mainWindow();
  void                 parseGCFile(const QString& fileName);
  PluginPageInterface* pluggablePage(const QString pageID);
  QList<QString>       pluggablePages();
  void                 setMainWindow(QMainWindow* w);
  void                 setViewStack(CenterView* v);
  void                 setWindowTitle(const QString& title);
  QWidget*             stackedPage(const QString& pageName);
  PluginPageInterface* statusInfo(const QString infoID);
  QList<QString>       statusInfos();
  CANON_POSITION       toolOffset() const;
  ToolTable&           toolTable();
  ToolTable*           toolTableModel();
  OcctQtViewer*        view3D();
  CenterView*          viewStack();
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
  explicit         GuiCore(void* p);
  GuiKernel*       guiCore();
  const GuiKernel* guiCore() const;
  friend class CanonIF;
  friend class AbstractCenterWidget;
  };
#endif
