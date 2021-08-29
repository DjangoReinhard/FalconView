#ifndef MAINWINDOW_H
#define MAINWINDOW_H
/*
 * looks like there's no difference between QTimer and QBasicTimer
 */
#define USE_EVENTLOOP_TIMER

#include <QMainWindow>
#ifndef USE_EVENTLOOP_TIMER
# include <QBasicTimer>
#endif
#include <valuemodel.h>
#include <labeladapter.h>
#include <positionmodel.h>
#include <gcodehighlighter.h>


class PositionDockable;
class ToolInfoDockable;
class SpeedInfoDockable;
class SettingsWidget;
class EditorDockable;
class Overlay;
class QLabel;
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

public slots:
  void count();
  void activateTbd();
  void activateSettings();
  void activateBg01();
  void activateBg02();
  void activateBg03();

protected:
  void createActions();
  void createToolBars();
  void createDockables();
  void createMainWidgets();
  void createConnections();
#ifndef USE_EVENTLOOP_TIMER
  void timerEvent(QTimerEvent* event) override;
#endif

private:
  Ui::MainWindow*     ui;
  PositionDockable*   pos;
  ToolInfoDockable*   ti;
  SpeedInfoDockable*  si;
  EditorDockable*     ed;
  GCodeHighlighter*   gh;
  SettingsWidget*     sw;
  Overlay*            overlay;
  QLabel*             bg01;
  QLabel*             bg02;
  QLabel*             bg03;
  QAction*            startAction;
  QAction*            pauseAction;
  QAction*            stopAction;
  QAction*            autoMode;
  QAction*            mdiMode;
  QAction*            editMode;
  QAction*            jogMode;
  QToolBar*           autoTB;
  QToolBar*           modeTB;
  ValueModel          counter;
  PositionModel       pm;
#ifndef USE_EVENTLOOP_TIMER
  QBasicTimer         timer;
#endif
  };
#endif // MAINWINDOW_H
