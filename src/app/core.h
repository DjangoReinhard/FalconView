#ifndef CORE_H
#define CORE_H
#include <QString>
class Kernel;
class OcctQtViewer;
class DBConnection;
class DBHelper;
class MainWindow;
class ToolTable;
class LcProperties;
class MainView;
class QCloseEvent;
class QWidget;
class AxisMask;


enum ApplicationMode {
  Invalid,
  Auto,          // 1
  MDI,           // 2
  Manual,        // 3
  Edit,          // 4
  Wheel,         // 5
  XEdit,         // 6
  Settings,      // 7
  Touch,         // 8
  ErrMessages,   // 9
  Unknown
  };


class Core
{
public:
  Core(const QString& iniFileName, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  Core() {}

  void            parseGCFile(const QString& fileName);
  void            activatePage(const QString& pageName);
  const QString&  curPage() const;
  DBConnection*   databaseConnection();
  void            showAllButCenter(bool visible = true);
  QWidget*        stackedPage(const QString& pageName);
  const AxisMask& axisMask() const;
  bool            isBackendActive() const;

  void          setViewStack(MainView* v);
  void          setAppMode(ApplicationMode m);
  void          setMainWindow(MainWindow* mw);
  void          windowClosing(QCloseEvent* e);
  bool          checkBE();
  OcctQtViewer* view3D();
  ToolTable&    toolTable();
  ToolTable*    toolTableModel();
  LcProperties& lcProperties();

private:
  friend class   Config;
  Kernel*        core();
  const Kernel*  core() const;
  static Kernel* kernel;
  };
#endif
