#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QBasicTimer>
#include <valuemodel.h>
#include <labeladapter.h>
#include <gcodehighlighter.h>
#include <gcodeinfo.h>
#include <curcodesdockable.h>
#include <positioncalculator.h>
#include <statusreader.h>


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
  void activateTbd();
  void activateSettings();
  void activateBg01();
  void activateBg02();
  void activateBg03();
  void resetLine();

protected:
  void createActions();
  void createToolBars();
  void createDockables();
  void createMainWidgets();
  void createConnections();
  void createValueModels();
  void timerEvent(QTimerEvent* event) override;

private:
  Ui::MainWindow*     ui;
  PositionDockable*   pos;
  ToolInfoDockable*   ti;
  SpeedInfoDockable*  si;
  EditorDockable*     ed;
  CurCodesDockable*   cc;
  GCodeHighlighter*   gh;
  SettingsWidget*     sw;
  QLabel*             bg01;
  QLabel*             bg02;
  QLabel*             bg03;
  QAction*            startAction;
  QAction*            pauseAction;
  QAction*            stopAction;
  QAction*            singleStep;
  QAction*            autoMode;
  QAction*            mdiMode;
  QAction*            editMode;
  QAction*            wheelMode;
  QAction*            jogMode;
  QAction*            cfgMode;
  QAction*            power;
  QAction*            mist;
  QAction*            flood;
  QAction*            spindleLeft;
  QAction*            spindleRight;
  QAction*            spindleOff;
  QAction*            nop0;
  QAction*            nop1;
  QAction*            nop2;
  QAction*            nop3;
  QAction*            nop4;
  QToolBar*           autoTB;
  QToolBar*           modeTB;
  QToolBar*           powerTB;
  QToolBar*           switchTB;
  int                 line;
  QBasicTimer         timer;
  GCodeInfo           gcodeInfo;
  PositionCalculator  positionCalculator;
  StatusReader        statusReader;
  };
#endif // MAINWINDOW_H
