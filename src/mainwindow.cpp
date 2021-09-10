#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <axismask.h>
#include <positiondockable.h>
#include <toolinfodockable.h>
#include <speedinfodockable.h>
#include <editordockable.h>
#include <gcodehighlighter.h>
#include <settingswidget.h>
#include <config.h>
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
 , pos(nullptr)
 , ti(nullptr)
 , si(nullptr)
 , ed(nullptr)
 , cc(nullptr)
 , gh(nullptr)
 , sw(nullptr)
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
  ui->setupUi(this);    // moc generated
  setObjectName("MainWindow");
  setDockNestingEnabled(true);
  Config cfg;

  cfg.value("whatEver");
  createActions();
  createToolBars();
  createMainWidgets();
  createDockables();
  createValueModels();
  createConnections();

  timer.start(40, this);

  // application window
  resize(QSize(1920, 1200));

  restoreGeometry(cfg.value("geometry").toByteArray());
  restoreState(cfg.value("windowState").toByteArray());
  }


MainWindow::~MainWindow() {
    /*
  delete ui;
  delete pos;
  delete ti;
  delete si;
  delete ed;
  delete gh;
  delete sw;
  delete bg01;
  delete bg02;
  delete bg03;
  delete startAction;
  delete pauseAction;
  delete stopAction;
  delete singleStep;
  delete autoMode;
  delete mdiMode;
  delete editMode;
  delete wheelMode;
  delete jogMode;
  delete cfgMode;
  delete autoTB;
  delete modeTB;
  delete powerTB;
  delete switchTB;
   */
  }


void MainWindow::createActions() {
//  qDebug() << "start of createActions(gcode) ...";
  // gcode execution
  startAction = new QAction(QIcon(":/res/SK_AutoStart.png"),  tr("Start"),       this);
  pauseAction = new QAction(QIcon(":/res/SK_AutoPause.png"),  tr("Pause"),       this);
  stopAction  = new QAction(QIcon(":/res/SK_AutoStop.png"),   tr("Stop"),        this);
  singleStep  = new QAction(QIcon(":/res/SK_SingleStep.png"), tr("Single-Step"), this);

//  qDebug() << "start of createActions(mode) ...";
  // controller mode
  autoMode    = new QAction(QIcon(":/res/SK_Auto.png"),     tr("Auto-mode"),   this);
  mdiMode     = new QAction(QIcon(":/res/SK_MDI.png"),      tr("MDI-mode"),    this);
  editMode    = new QAction(QIcon(":/res/SK_Edit.png"),     tr("Edit-mode"),   this);
  jogMode     = new QAction(QIcon(":/res/SK_Manual.png"),   tr("Manual-mode"), this);
  wheelMode   = new QAction(QIcon(":/res/SK_Wheel.png"),    tr("Wheel-mode"),  this);
  cfgMode     = new QAction(QIcon(":/res/SK_Settings.png"), tr("Config-mode"), this);

//  qDebug() << "start of createActions(switches) ...";
  // switches
  mist         = new QAction(QIcon(":/res/SK_Cool_Mist.png"),    tr("cool-Mist"),    this);
  flood        = new QAction(QIcon(":/res/SK_Cool_Flood.png"),   tr("cool-Flood"),  this);
  spindleLeft  = new QAction(QIcon(":/res/SK_Spindle_CCW.png"),  tr("spindle-CCW"), this);
  spindleOff   = new QAction(QIcon(":/res/SK_Spindle_Stop.png"), tr("spindle-Off"), this);
  spindleRight = new QAction(QIcon(":/res/SK_Spindle_CW.png"),   tr("spindle-CW"),  this);

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
  power       = new QAction(QIcon(":/res/SK_PowerOff.png"), tr("Powerooff"), this);
  }


void MainWindow::createValueModels() {
  ValueManager vm;

  vm.setValue("showAbsolute", false);
  }


void MainWindow::createConnections() {
  ValueManager vm;

//  qDebug() << " start of createConnections(view) ...";
  // toggle between absolute and relative position ...
  connect(ui->actionAbsolute_Position, &QAction::triggered, pos, [=](){ pos->setAbsolute(QVariant(ui->actionAbsolute_Position->isChecked())); });

//  qDebug() << " start of createConnections(file open) ...";
  // main menu actions ...
  connect(ui->actionOpen,     &QAction::triggered, ed,   &EditorDockable::openFile);
//  qDebug() << " start of createConnections(extra) ...";
  connect(ui->actionDefault,  &QAction::triggered, this, &MainWindow::activateTbd);
  connect(ui->actionBack01,   &QAction::triggered, this, &MainWindow::activateBg01);
  connect(ui->actionBack02,   &QAction::triggered, this, &MainWindow::activateBg02);
  connect(ui->actionBack03,   &QAction::triggered, this, &MainWindow::activateBg03);
  connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::activateSettings);
//  qDebug() << " start of createConnections(done) ...";
/*
  connect(singleStep, &QAction::triggered, ed, [=](){ ed->setLine(QVariant(++line)); });
  connect(stopAction, &QAction::triggered, this, &MainWindow::resetLine);
 */
  }


void MainWindow::closeEvent(QCloseEvent *event) {
  Config cfg;

  cfg.setValue("geometry", saveGeometry());
  cfg.setValue("windowState", saveState());
  QMainWindow::closeEvent(event);
/*
    if (maybeSave()) {
     writeSettings();
     event->accept();
     }
  else {
     event->ignore();
     }
 */
  }


/*
void MainWindow::resetLine() {
  line = 0;
  ed->setLine(QVariant(0));
  }
*/


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


void MainWindow::createDockables() {
//  qDebug() << "start of createDockables()";
  ti = new ToolInfoDockable("../QtUi/src/UI/ToolInfo.ui", this);
  addDockWidget(Qt::LeftDockWidgetArea, ti);
  cc = new CurCodesDockable("../QtUi/src/UI/CurCodes.ui", this);
  addDockWidget(Qt::LeftDockWidgetArea, cc);
  pos = new PositionDockable("../QtUi/src/UI/Position.ui", AxisMask(0x01FF), this);
  addDockWidget(Qt::LeftDockWidgetArea, pos);
  si = new SpeedInfoDockable("../QtUi/src/UI/SpeedInfo.ui", this);
  addDockWidget(Qt::BottomDockWidgetArea, si);
  ed = new EditorDockable("../QtUi/src/UI/GCodeEditor.ui", this);
  addDockWidget(Qt::BottomDockWidgetArea, ed);
  }


void MainWindow::createMainWidgets() {
//  qDebug() << "start of createMainWidgets() ...";
  sw = new SettingsWidget("../QtUi/src/UI/Settings.ui", this);
  ui->gridLayout->addWidget(sw, 0, 0);
  sw->hide();
  bg01 = new QLabel(this);
  bg01->setPixmap(QPixmap(":/res/SampleBG01.jpg"));
  ui->gridLayout->addWidget(bg01, 0, 0);
  bg01->hide();
  bg02 = new QLabel(this);
  bg02->setPixmap(QPixmap(":/res/SampleBG02.jpg"));
  ui->gridLayout->addWidget(bg02, 0, 0);
  bg02->hide();
  bg03 = new QLabel(this);
  bg03->setPixmap(QPixmap(":/res/SampleBG03.jpg"));
  ui->gridLayout->addWidget(bg03, 0, 0);
  bg03->hide();
  }


void MainWindow::activateTbd() {
  ui->tbd->show();
  sw->hide();
  bg01->hide();
  bg02->hide();
  bg03->hide();
  }


void MainWindow::activateSettings() {
  sw->show();
  ui->tbd->hide();
  bg01->hide();
  bg02->hide();
  bg03->hide();
  ui->actionSave->setEnabled(true);
  }


void MainWindow::activateBg01() {
  bg01->show();
  sw->hide();
  ui->tbd->hide();
  bg02->hide();
  bg03->hide();
  }


void MainWindow::activateBg02() {
  bg02->show();
  sw->hide();
  ui->tbd->hide();
  bg01->hide();
  bg03->hide();
  }


void MainWindow::activateBg03() {
  bg03->show();
  sw->hide();
  ui->tbd->hide();
  bg01->hide();
  bg02->hide();
  }


void MainWindow::timerEvent(QTimerEvent *e) {
//  qDebug() << "start of timerEvent ...";
  if (e->timerId() == timer.timerId())  {
     statusReader.update();
     }
  else QMainWindow::timerEvent(e);
  }
