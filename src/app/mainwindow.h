#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QBasicTimer>
#include <valuemodel.h>
#include <labeladapter.h>
#include <gcodehighlighter.h>
#include <gcodeinfo.h>
#include <positioncalculator.h>

class PositionDockable;
class ToolInfoDockable;
class SpeedInfoDockable;
class CurCodesDockable;
class DocumentCommon;
class Dockable;
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

  void showAllButCenter(bool visible = true);

protected:
  void createActions();
  void createToolBars();
  void createDockables(DBConnection& conn);
  void createMainWidgets(DBConnection& conn);
  void createConnections();
  void createValueModels();
  void closeEvent(QCloseEvent *event) override;
  void keyPressEvent(QKeyEvent* event) override;
  void addDockable(Qt::DockWidgetArea area, Dockable* dockable);

protected slots:
  void selectPage(const QString& name);

private:
  Ui::MainWindow*     ui;
  PositionDockable*   pos;
  GCodeHighlighter*   gh;
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
  QToolBar*           autoTB;
  QToolBar*           modeTB;
//  QToolBar*           cfgTB;
  QToolBar*           nopTB;
  QToolBar*           powerTB;
  QToolBar*           switchTB;
  int                 line;
  QList<Dockable*>    dockables;
  };
#endif // MAINWINDOW_H
