#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <axismask.h>
#include <positiondockable.h>
#include <toolinfodockable.h>
#include <speedinfodockable.h>
#include <editordockable.h>
#include <gcodehighlighter.h>
#include <settingswidget.h>
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
 , statusReader(positionCalculator, gcodeInfo) {
  ui->setupUi(this);    // moc generated

  createActions();
  createToolBars();
  createMainWidgets();
  createDockables();
  createValueModels();
  createConnections();

  timer.start(40, this);

  // application window
  setMinimumWidth(1200);
  }


MainWindow::~MainWindow() {
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
  delete autoTB;
  delete autoMode;
  delete mdiMode;
  delete editMode;
  delete jogMode;
  delete modeTB;
  }


void MainWindow::createActions() {
  // gcode execution
  startAction = new QAction(QIcon(":/res/SK_AutoStart.png"),  tr("Start"),       this);
  pauseAction = new QAction(QIcon(":/res/SK_AutoPause.png"),  tr("Pause"),       this);
  stopAction  = new QAction(QIcon(":/res/SK_AutoStop.png"),   tr("Stop"),        this);
  singleStep  = new QAction(QIcon(":/res/SK_SingleStep.png"), tr("Single-Step"), this);

  // controller mode
  autoMode    = new QAction(QIcon(":/res/SK_Auto.png"),     tr("Auto-mode"),   this);
  mdiMode     = new QAction(QIcon(":/res/SK_MDI.png"),      tr("MDI-mode"),    this);
  editMode    = new QAction(QIcon(":/res/SK_Edit.png"),     tr("Edit-mode"),   this);
  jogMode     = new QAction(QIcon(":/res/SK_Manual.png"),   tr("Manual-mode"), this);
  wheelMode   = new QAction(QIcon(":/res/SK_Wheel.png"),    tr("Wheel-mode"),  this);
  cfgMode     = new QAction(QIcon(":/res/SK_Settings.png"), tr("Config-mode"), this);
  }


void MainWindow::createValueModels() {
  ValueManager vm;

  vm.setValue("showAbsolute", false);
  }


void MainWindow::createConnections() {
  ValueManager vm;

  // toggle between absolute and relative position ...
  connect(ui->actionAbsolute_Position, &QAction::triggered, pos, [=](){ pos->setAbsolute(QVariant(ui->actionAbsolute_Position->isChecked())); });

  // main menu actions ...
  connect(ui->actionOpen,     &QAction::triggered, ed,   &EditorDockable::openFileAlt);
  connect(ui->actionDefault,  &QAction::triggered, this, &MainWindow::activateTbd);
  connect(ui->actionBack01,   &QAction::triggered, this, &MainWindow::activateBg01);
  connect(ui->actionBack02,   &QAction::triggered, this, &MainWindow::activateBg02);
  connect(ui->actionBack03,   &QAction::triggered, this, &MainWindow::activateBg03);
  connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::activateSettings);

  connect(singleStep, &QAction::triggered, ed, [=](){ ed->setLine(QVariant(++line)); });
  connect(stopAction, &QAction::triggered, this, &MainWindow::resetLine);
  }


void MainWindow::resetLine() {
  line = 0;
  ed->setLine(QVariant(0));
  }


void MainWindow::createToolBars() {
  autoTB = new QToolBar(tr("Auto"), this);
  autoTB->setIconSize(QSize(90, 90));
  autoTB->addAction(startAction);
  autoTB->addAction(pauseAction);
  autoTB->addAction(stopAction);
  autoTB->addAction(singleStep);
  addToolBar(Qt::BottomToolBarArea, autoTB);

  modeTB = new QToolBar(tr("Mode"), this);
  modeTB->setIconSize(QSize(90, 90));
  modeTB->addAction(autoMode);
  modeTB->addAction(mdiMode);
  modeTB->addAction(editMode);
  modeTB->addAction(jogMode);
  modeTB->addAction(wheelMode);
  modeTB->addAction(cfgMode);
  addToolBar(Qt::BottomToolBarArea, modeTB);
  }


void MainWindow::createDockables() {
  pos = new PositionDockable("../QtUi/src/UI/Position.ui", AxisMask(0x01FF), this);
  addDockWidget(Qt::LeftDockWidgetArea, pos);
  ti = new ToolInfoDockable("../QtUi/src/UI/ToolInfo.ui", this);
  addDockWidget(Qt::LeftDockWidgetArea, ti);
  si = new SpeedInfoDockable("../QtUi/src/UI/SpeedInfo.ui", this);
  addDockWidget(Qt::BottomDockWidgetArea, si);
  ed = new EditorDockable("../QtUi/src/UI/GCodeEditor.ui", this);
  addDockWidget(Qt::BottomDockWidgetArea, ed);
  }


void MainWindow::createMainWidgets() {
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

  overlay = new Overlay("../QtUi/src/UI/Overlay.ui", this);
  ui->gridLayout->addWidget(overlay, 0, 0);
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
  if (e->timerId() == timer.timerId())  {
     statusReader.update();
     }
  else QMainWindow::timerEvent(e);
  }
