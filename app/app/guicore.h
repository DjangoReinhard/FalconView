#ifndef GUICORE_H
#define GUICORE_H
#include <core.h>

class GuiKernel;
class OcctQtViewer;
class DBConnection;
class DBHelper;
class MainWindow;
class ToolTable;
class LcProperties;
class CenterView;
class QCloseEvent;
class QTranslator;
class QLocale;
class QWidget;
class AxisMask;


class GuiCore : public Core
{
public:
  GuiCore(const QString& iniFileName, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  GuiCore() {}

  QString         curPage() const;
  QString         helpFilename() const;
  bool            isLatheMode() const;
  bool            isSimulator() const;
  bool            showHelpAtPageChange() const;
  void            riseError(const QString& msg);
  QString         languagePrefix() const;
  DBConnection*   databaseConnection();
  MainWindow*     mainWindow();
  QLocale         locale() const;
  bool            move2Backup(const QString& fileName);
  void            activatePage(const QString& pageName);
  void            showAllButCenter(bool visible = true);
  QWidget*        stackedPage(const QString& pageName);
  void            setViewStack(CenterView* v);
  void            setWindowTitle(const QString& title);
  void            windowClosing(QCloseEvent* e);
  void            parseGCFile(const QString& fileName);
  bool            checkBE();
  void            help4Keyword(const QString& keyWord);
  void            showHelp();
  void            setLocale(const QLocale& l);
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
  GuiKernel*       guiCore();
  const GuiKernel* guiCore() const;
  };
#endif
