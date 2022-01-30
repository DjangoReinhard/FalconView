#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <applicationmode.h>
#include <QMainWindow>
//#define ADD_TEST_ACTION
class SettingsNotebook;
class PositionStatus;
class PreViewEditor;
class Dockable;
class DBConnection;
class MDIEditor;
class GCodeViewer;
class HelpDockable;
class PluginPageFactory;
class QAction;
class QDialog;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
 ~MainWindow();

  void initialize();
  void setAppMode(ApplicationMode am);
  SettingsNotebook* settingsNotebook() const { return snb; }

protected:
  void closeEvent(QCloseEvent *event)  override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void about();
  void addDockable(Qt::DockWidgetArea area, Dockable* dockable);
  void createActions();
  void createToolBars();
  void createDockables();
  void createMainWidgets();
  void createConnections();
  void createValueModels();
  void setupMenu();
  void restoreAll();
  void tellStates() const;

protected slots:
  void appModeChanged(const QVariant& appMode);
  void setSingleStep(bool singleStep);
  void hitPowerBtn();
  void showErrMessages();
  void toggleAllButCenter();
  void toggleAbsolute(const QVariant& absolute);
#ifdef ADD_TEST_ACTION
  void testTools();
#endif
  void autoStart();
  void autoPause();
  void autoStop();
  void homeAxis();
  void mistToggle();
  void floodToggle();
  void startSpindleCCW();
  void startSpindleCW();
  void stopSpindle();

private:
  bool                statusInPreview;
  bool                previewIsCenter;
  Ui::MainWindow*     ui;
  PluginPageFactory*  ppFactory;
  SettingsNotebook*   snb;
  PreViewEditor*      pw;
  MDIEditor*          mdi;
  QDialog*            dlgAbout;
  QAction*            startAction;
  QAction*            pauseAction;
  QAction*            stopAction;
  QAction*            singleStep;
  QAction*            homeAll;
  QAction*            autoMode;
  QAction*            mdiMode;
  QAction*            editMode;
  QAction*            testEditMode;
  QAction*            wheelMode;
  QAction*            jogMode;
  QAction*            cfgMode;
  QAction*            msgMode;
  QAction*            touchMode;

  QAction*            power;
  QAction*            mist;
  QAction*            flood;
  QAction*            spindleLeft;
  QAction*            spindleRight;
  QAction*            spindleOff;
  QAction*            tools;
  QAction*            offsets;

  QToolBar*           autoTB;
  QToolBar*           modeTB;
  QToolBar*           topTB;
  QToolBar*           powerTB;
  QToolBar*           switchTB;
  int                 line;

  QList<Dockable*> dockables;
  };
#endif // MAINWINDOW_H
