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
class QWidget;
class AxisMask;


class Core
{
public:
  Core(const QString& iniFileName, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  Core() {}

  void            parseGCFile(const QString& fileName);
  void            activatePage(const QString& pageName);
  DBConnection*   databaseConnection();
  void            showAllButCenter(bool visible = true);
  QWidget*        stackedPage(const QString& pageName);
  const AxisMask& axisMask() const;
  bool            isBackendActive() const;

  void          setViewStack(MainView* v);
  void          setMainWindow(MainWindow* mw);
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
