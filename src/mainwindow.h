#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QBasicTimer>
#include <valuemodel.h>
#include <labeladapter.h>
#include <gcodehighlighter.h>
#include <gcodeinfo.h>
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
  GCodeHighlighter*   gh;
  SettingsWidget*     sw;
  Overlay*            overlay;
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
  QToolBar*           autoTB;
  QToolBar*           modeTB;
  QBasicTimer         timer;
  GCodeInfo           gcodeInfo;
  PositionCalculator  positionCalculator;
  StatusReader        statusReader;
  };
#endif // MAINWINDOW_H
