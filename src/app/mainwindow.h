#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QBasicTimer>
#include <commandwriter.h>
#include <applicationmode.h>

class SettingsNotebook;
class PositionStatus;
class PreViewEditor;
class DynDockable;
class DBConnection;
class GCodeViewer;
class HelpDialog;
class QAction;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(bool statusInPreview, QWidget *parent = nullptr);
 ~MainWindow();

  void setAppMode(ApplicationMode am);
  HelpDialog* helpDialog() { return dlgHelp; }
  SettingsNotebook* settingsNotebook() const { return snb; }

protected:
  void closeEvent(QCloseEvent *event)  override;
  void keyPressEvent(QKeyEvent* event) override;
  void keyReleaseEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
  void about();
  void addDockable(Qt::DockWidgetArea area, DynDockable* dockable);
  void createActions();
  void createToolBars();
  void createDockables(DBConnection& conn);
  void createMainWidgets(DBConnection& conn);
  void createConnections();
  void createValueModels();
  void setupMenu();
  void tellStates() const;

protected slots:
  void appModeChanged(const QVariant& appMode);
  void setSingleStep(bool singleStep);
  void hitPowerBtn();
  void showErrMessages();
  void toggleAllButCenter();
  void toggleAbsolute(const QVariant& absolute);
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
  Ui::MainWindow*     ui;
  PreViewEditor*      pw;
  HelpDialog*         dlgHelp;
  SettingsNotebook*   snb;
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
  QBasicTimer         timer;

  QList<DynDockable*> dockables;
  };
#endif // MAINWINDOW_H
