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
class EditorDockable;
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

protected:
  void createDockings();
#ifndef USE_EVENTLOOP_TIMER
  void timerEvent(QTimerEvent* event) override;
#endif

private:
  Ui::MainWindow*     ui;
  PositionDockable*   pos;
  ToolInfoDockable*   ti;
  SpeedInfoDockable*  si;
  EditorDockable*     ed;
  ValueModel          counter;
  PositionModel       pm;
  GCodeHighlighter*   gh;
#ifndef USE_EVENTLOOP_TIMER
  QBasicTimer         timer;
#endif
  };
#endif // MAINWINDOW_H
