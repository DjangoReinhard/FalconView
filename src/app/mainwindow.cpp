#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <dbconnection.h>
#include <mainview.h>
#include <axismask.h>
#include <dockable.h>
#include <core.h>
#include <positiondockable.h>
#include <toolinfodockable.h>
#include <speedinfodockable.h>
#include <editordockable.h>
#include <curcodesdockable.h>
#include <maindockable.h>
#include <gcodehighlighter.h>
#include <gcodeviewer.h>
#include <pweditor.h>
#include <patheditor.h>
#include <settingseditor.h>
#include <fixturemanager.h>
#include <filemanager.h>
#include <toolmanager.h>
#include <micon.h>
#include <canonif.h>
#include <configacc.h>
#include <DocumentCommon.h>
#include <occtviewer.h>
#include <QDockWidget>
#include <QtUiTools/QUiLoader>
#include <QSplitter>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QFileDialog>
#include <math.h>
#include <QImageReader>
#include <QMessageBox>
#include <QImage>
#include <QColorSpace>
#include <QToolBar>
#include <QVariant>
#include <overlay.h>
#include <valuemanager.h>


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , gh(nullptr)
 , bg01(nullptr)
 , bg02(nullptr)
 , bg03(nullptr)
 , startAction(nullptr)
 , pauseAction(nullptr)
 , stopAction(nullptr)
 , singleStep(nullptr)
 , autoMode(nullptr)
 , mdiMode(nullptr)
 , editMode(nullptr)
 , wheelMode(nullptr)
 , jogMode(nullptr)
 , cfgMode(nullptr)
 , autoTB(nullptr)
 , modeTB(nullptr)
 , powerTB(nullptr)
 , switchTB(nullptr)
 , statusReader(positionCalculator, gcodeInfo) {
  ui->setupUi(this);
  setObjectName("Falcon-View");
  setDockNestingEnabled(true);
  DBConnection conn("../ToolManager/db/toolTable");

  if (!conn.connect()) qDebug() << "failed to connect to Database!";

  createActions();
  createToolBars();
  createMainWidgets(conn);
  createDockables(conn);
  createValueModels();
  createConnections();

  timer.start(40, this);

  // application window
  resize(QSize(1920, 1200));
  Config cfg;

  restoreGeometry(cfg.value("geometry").toByteArray());
  restoreState(cfg.value("windowState").toByteArray());
  }


MainWindow::~MainWindow() {
  }


void MainWindow::createActions() {
//  qDebug() << "start of createActions(gcode) ...";
  // gcode execution
  MIcon::setDisabledFileName(":/res/SK_DisabledIcon.png");
  startAction = new QAction(MIcon(":/res/SK_AutoStart.png"
                                , ":/res/SK_AutoStart_active.png"),  tr("Start"),       this);
  startAction->setCheckable(true);
  pauseAction = new QAction(MIcon(":/res/SK_AutoPause.png"
                                , ":/res/SK_AutoPause_active.png"),  tr("Pause"),       this);
  pauseAction->setCheckable(true);
  stopAction  = new QAction(MIcon(":/res/SK_AutoStop.png"
                                , ":/res/SK_AutoStop_active.png"),   tr("Stop"),        this);
  stopAction->setCheckable(true);
  singleStep  = new QAction(MIcon(":/res/SK_SingleStep.png"
                                , ":/res/SK_SingleStep_active.png"), tr("Single-Step"), this);
  singleStep->setCheckable(true);

//  qDebug() << "start of createActions(mode) ...";
  // controller mode
  autoMode    = new QAction(MIcon(":/res/SK_Auto.png"
                                , ":/res/SK_Auto_active.png"),     tr("Auto-mode"),   this);
  autoMode->setCheckable(true);
  mdiMode     = new QAction(MIcon(":/res/SK_MDI.png"
                                , ":/res/SK_MDI_active.png"),      tr("MDI-mode"),    this);
  mdiMode->setCheckable(true);
  editMode    = new QAction(MIcon(":/res/SK_Edit.png"
                                , ":/res/SK_Edit_active.png"),     tr("Edit-mode"),   this);
  editMode->setCheckable(true);
  jogMode     = new QAction(MIcon(":/res/SK_Manual.png"
                                , ":/res/SK_Manual_active.png"),   tr("Manual-mode"), this);
  jogMode->setCheckable(true);
  wheelMode   = new QAction(MIcon(":/res/SK_Wheel.png"
                                , ":/res/SK_Wheel_active.png"),    tr("Wheel-mode"),  this);
  wheelMode->setCheckable(true);
//  wheelMode->setEnabled(false);
  cfgMode     = new QAction(MIcon(":/res/SK_Settings.png"
                                , ":/res/SK_Settings_active.png"), tr("Config-mode"), this);
  cfgMode->setCheckable(true);

//  qDebug() << "start of createActions(switches) ...";
  // switches
  mist         = new QAction(MIcon(":/res/SK_Cool_Mist.png"
                                 , ":/res/SK_Cool_Mist_active.png"),    tr("cool-Mist"),    this);
  mist->setCheckable(true);
  flood        = new QAction(MIcon(":/res/SK_Cool_Flood.png"
                                 , ":/res/SK_Cool_Flood_active.png"),   tr("cool-Flood"),  this);
  flood->setCheckable(true);
  spindleLeft  = new QAction(MIcon(":/res/SK_Spindle_CCW.png"
                                 , ":/res/SK_Spindle_CCW_active.png"),  tr("spindle-CCW"), this);
  spindleLeft->setCheckable(true);
  spindleOff   = new QAction(MIcon(":/res/SK_Spindle_Stop.png"
                                 , ":/res/SK_Spindle_Stop_active.png"), tr("spindle-Off"), this);
  spindleOff->setCheckable(true);
  spindleRight = new QAction(MIcon(":/res/SK_Spindle_CW.png"
                                 , ":/res/SK_Spindle_CW_active.png"),   tr("spindle-CW"),  this);
  spindleRight->setCheckable(true);

//  qDebug() << "start of createActions(nop) ...";
  nop0 = new QAction(QIcon(":/res/SK_NOP.png"), tr("nop"), this);
  nop1 = new QAction(QIcon(":/res/SK_NOP.png"), tr("nop"), this);
  nop2 = new QAction(QIcon(":/res/SK_NOP.png"), tr("nop"), this);
  nop3 = new QAction(QIcon(":/res/SK_NOP.png"), tr("nop"), this);
  nop4 = new QAction(QIcon(":/res/SK_NOP.png"), tr("nop"), this);
  nop0->setEnabled(false);
  nop1->setEnabled(false);
  nop2->setEnabled(false);
  nop3->setEnabled(false);
  nop4->setEnabled(false);

//  qDebug() << "start of createActions(power) ...";
  // power switch
  power       = new QAction(MIcon(":/res/SK_PowerOff.png"
                                , ":/res/SK_PowerOn.png"), tr("Poweroff"), this);
  power->setCheckable(true);
  }


void MainWindow::createValueModels() {
  ValueManager vm;

  vm.setValue("showAbsolute", false);
  }


void MainWindow::createConnections() {
  ValueManager vm;

//  qDebug() << " start of createConnections(view) ...";
  // toggle between absolute and relative position ...
  connect(ui->actionAbsPos, &QAction::triggered, pos, [=](){ pos->setAbsolute(QVariant(ui->actionAbsPos->isChecked())); });

  qDebug() << " start of createConnections(file open) ...";
  // main menu actions ...
//  connect(ui->actionOpen, &QAction::triggered, pwe,  &PreViewEditor::openFile);
  qDebug() << " start of createConnections(done) ...";
  }


void MainWindow::closeEvent(QCloseEvent *event) {
  QMessageBox::StandardButton reply;

  reply = QMessageBox::question(this
                              , tr("close application?")
                              , tr("<p>closing the application means shutting down "
                                   "the backend and stopping all services IF ui "
                                   "has been started by linuxcnc start-helper</p>")
                              , QMessageBox::Yes | QMessageBox::Cancel);
  if (reply == QMessageBox::Yes) {
     Config cfg;

     cfg.setValue("geometry", saveGeometry());
     cfg.setValue("windowState", saveState());
     QMainWindow::closeEvent(event);
     }
  else event->ignore();
  }


void MainWindow::createToolBars() {
//  qDebug() << "start of createToolBars() ...";
  QSize s(90, 90);

  autoTB = new QToolBar(tr("Auto"), this);
  autoTB->setObjectName("AutoTB");
  autoTB->setIconSize(s);
  autoTB->addAction(startAction);
  autoTB->addAction(pauseAction);
  autoTB->addAction(stopAction);
  autoTB->addAction(singleStep);
  addToolBar(Qt::BottomToolBarArea, autoTB);

  modeTB = new QToolBar(tr("Mode"), this);
  modeTB->setObjectName("ModeTB");
  modeTB->setIconSize(s);
  modeTB->addAction(autoMode);
  modeTB->addAction(mdiMode);
  modeTB->addAction(editMode);
  modeTB->addAction(jogMode);
  modeTB->addAction(wheelMode);
  modeTB->addAction(cfgMode);
  addToolBar(Qt::BottomToolBarArea, modeTB);

  nopTB = new QToolBar(tr("NOP"), this);
  nopTB->setObjectName("NopTB");
  nopTB->setIconSize(s);
  nopTB->addAction(nop0);
  nopTB->addAction(nop1);
  nopTB->addAction(nop2);
  nopTB->addAction(nop3);
  nopTB->addAction(nop4);
  addToolBar(Qt::RightToolBarArea, nopTB);

  switchTB = new QToolBar(tr("Switch"), this);
  switchTB->setObjectName("SwitchTB");
  switchTB->setIconSize(s);
  switchTB->addAction(mist);
  switchTB->addAction(flood);
  switchTB->addAction(spindleLeft);
  switchTB->addAction(spindleOff);
  switchTB->addAction(spindleRight);
  addToolBar(Qt::RightToolBarArea, switchTB);

  powerTB = new QToolBar(tr("Power"), this);
  powerTB->setObjectName("PowerTB");
  powerTB->setIconSize(s);
  powerTB->addAction(power);
  addToolBar(Qt::BottomToolBarArea, powerTB);
  }


void MainWindow::createDockables(DBConnection&) {
  Dockable* d = new ToolInfoDockable(":/src/UI/ToolInfo.ui", this);

  addDockWidget(Qt::LeftDockWidgetArea, d);
  ui->menuView->addAction(d->toggleViewAction());

  d = new CurCodesDockable(":/src/UI/CurCodes.ui", this);
  addDockWidget(Qt::LeftDockWidgetArea, d);
  ui->menuView->addAction(d->toggleViewAction());

  //TODO: read axisMask from ini-file
  pos = new PositionDockable(":/src/UI/Position.ui", AxisMask(0x01FF), this);
  d   = pos;
  addDockWidget(Qt::LeftDockWidgetArea, d);
  ui->menuView->addAction(d->toggleViewAction());

  d = new SpeedInfoDockable(":/src/UI/SpeedInfo.ui", this);
  addDockWidget(Qt::BottomDockWidgetArea, d);
  ui->menuView->addAction(d->toggleViewAction());
  }


void MainWindow::createMainWidgets(DBConnection& conn) {
  MainView*  mainView = new MainView(this);
  DynWidget* page     = new PreViewEditor(":/src/UI/GCodeEditor.ui", Core().view3D(), mainView);

  Core().setViewStack(mainView);
  mainView->addPage(page->objectName(), page);
  ui->menuMain->addAction(page->viewAction());

  page = new FileManager(QDir(QDir::homePath() + "/linuxcnc"), mainView);
  mainView->addPage(page->objectName(), page);
  ui->menuMain->addAction(page->viewAction());

  page = new ToolManager(conn);
  mainView->addPage(page->objectName(), page);
  ui->menuMain->addAction(page->viewAction());

  page = new FixtureManager(":/src/UI/Fixture.ui");
  mainView->addPage(page->objectName(), page);
  ui->menuMain->addAction(page->viewAction());

  page = new SettingsEditor(":/src/UI/Settings.ui", mainView);
  mainView->addPage(page->objectName(), page);
  ui->menuMain->addAction(page->viewAction());

  page = new PathEditor(":/src/UI/GCodeEditor.ui", mainView);
  mainView->addPage(page->objectName(), page);
  ui->menuMain->addAction(page->viewAction());

  page = new TestEdit(":/src/UI/GCodeEditor.ui", mainView);
  mainView->addPage(page->objectName(), page);
  ui->menuMain->addAction(page->viewAction());

  this->setCentralWidget(mainView);
  }


void MainWindow::selectPage(const QString& name) {
  qDebug() << "page to select: " << name;
  Core().viewStack()->activatePage(name);
  }


void MainWindow::timerEvent(QTimerEvent *e) {
//  qDebug() << "start of timerEvent ...";
  if (e->timerId() == timer.timerId())  {
     statusReader.update();
     }
  else QMainWindow::timerEvent(e);
  }
