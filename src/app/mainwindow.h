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
class CurCodesDockable;
class DocumentCommon;
class DBConnection;
class GCodeViewer;
class MainView;
class OcctQtViewer;
class QSplitter;
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

protected:
  void createActions();
  void createToolBars();
  void createDockables(DBConnection& conn);
  void createMainWidgets(DBConnection& conn);
  void createConnections();
  void createValueModels();
  void timerEvent(QTimerEvent* event) override;
  void closeEvent(QCloseEvent *event) override;

protected slots:
  void selectPage(const QString& name);

private:
  Ui::MainWindow*     ui;
  PositionDockable*   pos;
  GCodeHighlighter*   gh;
  QLabel*             bg01;
  QLabel*             bg02;
  QLabel*             bg03;
  QAction*            startAction;
  QAction*            pauseAction;
  QAction*            stopAction;
  QAction*            singleStep;
  QAction*            homeAll;
  QAction*            posAbsolute;
  QAction*            autoMode;
  QAction*            mdiMode;
  QAction*            editMode;
  QAction*            testEditMode;
  QAction*            wheelMode;
  QAction*            jogMode;
  QAction*            cfgMode;
  QAction*            touchMode;
  QAction*            power;
  QAction*            mist;
  QAction*            flood;
  QAction*            spindleLeft;
  QAction*            spindleRight;
  QAction*            spindleOff;
  QAction*            tools;
  QAction*            offsets;
//  QAction*            nop1;
//  QAction*            nop2;
  QToolBar*           autoTB;
  QToolBar*           modeTB;
  QToolBar*           cfgTB;
  QToolBar*           nopTB;
  QToolBar*           powerTB;
  QToolBar*           switchTB;
  int                 line;
  QBasicTimer         timer;
  GCodeInfo           gcodeInfo;
  PositionCalculator  positionCalculator;
  StatusReader        statusReader;
  };
#endif // MAINWINDOW_H
