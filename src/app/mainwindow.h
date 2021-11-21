#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QBasicTimer>
#include <commandwriter.h>
#include <applicationmode.h>

class PositionDockable;
class Dockable;
class DBConnection;
class GCodeViewer;
class QAction;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
 ~MainWindow();

  void setAppMode(ApplicationMode am);

protected:
  void closeEvent(QCloseEvent *event)  override;
  void keyPressEvent(QKeyEvent* event) override;
  void timerEvent(QTimerEvent* event) override;
  void addDockable(Qt::DockWidgetArea area, Dockable* dockable);
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
  void toggleErrMessages();
  void toggleAllButCenter();
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
  Ui::MainWindow*     ui;
  PositionDockable*   pos;
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

  QList<Dockable*>    dockables;
  };
#endif // MAINWINDOW_H
