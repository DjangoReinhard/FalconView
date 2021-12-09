#ifndef CORE_H
#define CORE_H
#include <QString>
#include <applicationmode.h>
class Kernel;
class OcctQtViewer;
class DBConnection;
class DBHelper;
class MainWindow;
class ToolTable;
class LcProperties;
class CenterView;
class QCloseEvent;
class QTranslator;
class QWidget;
class AxisMask;


class Core
{
public:
  Core(const QString& iniFileName, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  Core() {}

  const QString&  curPage() const;
  QString         helpFilename() const;
  const AxisMask& axisMask() const;
  bool            isLatheMode() const;
  bool            isSimulator() const;
  bool            showHelpAtPageChange() const;
  DBConnection*   databaseConnection();
  MainWindow*     mainWindow();
  void            activatePage(const QString& pageName);
  void            showAllButCenter(bool visible = true);
  QWidget*        stackedPage(const QString& pageName);
  void            setViewStack(CenterView* v);
  void            setAppMode(ApplicationMode m);
  void            setWindowTitle(const QString& title);
  void            windowClosing(QCloseEvent* e);
  void            parseGCFile(const QString& fileName);
  bool            checkBE();
  void            help4Keyword(const QString& keyWord);
  CenterView*     viewStack();
  OcctQtViewer*   view3D();
  ToolTable&      toolTable();
  ToolTable*      toolTableModel();
  LcProperties&   lcProperties();

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
  friend class   Config;
  Kernel*        core();
  const Kernel*  core() const;
  static Kernel* kernel;
  static int     checked;
  };
#endif
