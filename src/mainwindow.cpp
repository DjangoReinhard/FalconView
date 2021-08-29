#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <axismask.h>
#include <positiondockable.h>
#include <toolinfodockable.h>
#include <speedinfodockable.h>
#include <editordockable.h>
#include <gcodehighlighter.h>
#include <settingswidget.h>
#ifdef USE_EVENTLOOP_TIMER
#include <QTimer>
#endif
#include <QDockWidget>
#include <QtUiTools/QUiLoader>
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
#include <overlay.h>


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , gh(nullptr)
 , counter(0.0) {
  // load our widgets from ui-file
  ui->setupUi(this);

  createActions();
  createToolBars();
  createMainWidgets();
  createDockables();
  createConnections();

  /*
   * for testing purpose only
   * start simple timer as base of changes
   */
#ifdef USE_EVENTLOOP_TIMER
  /*
   * drawback of this timer - timer stops with open-file-dialogs
   */
  QTimer* t = new QTimer(this);

  connect(t, &QTimer::timeout, this, &MainWindow::count);
  t->start(5);
#else
  timer.start(5, this);
#endif

  // simulate homed axis
  pos->setXHomed();
  pos->setYHomed();
  pos->setZHomed();
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
  startAction = new QAction(QIcon(":/res/SK_AutoStart.png"), tr("Start"), this);
  pauseAction = new QAction(QIcon(":/res/SK_AutoPause.png"), tr("Pause"), this);
  stopAction  = new QAction(QIcon(":/res/SK_AutoStop.png"),  tr("Stop"),  this);

  autoMode    = new QAction(QIcon(":/res/SK_Auto.png"),   tr("Auto-mode"),    this);
  mdiMode     = new QAction(QIcon(":/res/SK_MDI.png"),    tr("MDI-mode"),     this);
  editMode    = new QAction(QIcon(":/res/SK_Edit.png"),   tr("Edit-mode"),    this);
  jogMode     = new QAction(QIcon(":/res/SK_Manual.png"), tr("Manual-mode"),  this);
  }


void MainWindow::createConnections() {
  // connect model with view
  connect(&pm.getXAbs(), &ValueModel::valueChanged, pos->getXAbs(), &LabelAdapter::setValue);
  connect(&pm.getYAbs(), &ValueModel::valueChanged, pos->getYAbs(), &LabelAdapter::setValue);
  connect(&pm.getZAbs(), &ValueModel::valueChanged, pos->getZAbs(), &LabelAdapter::setValue);
  connect(&pm.getAAbs(), &ValueModel::valueChanged, pos->getAAbs(), &LabelAdapter::setValue);
  connect(&pm.getBAbs(), &ValueModel::valueChanged, pos->getBAbs(), &LabelAdapter::setValue);
  connect(&pm.getCAbs(), &ValueModel::valueChanged, pos->getCAbs(), &LabelAdapter::setValue);
  connect(&pm.getUAbs(), &ValueModel::valueChanged, pos->getUAbs(), &LabelAdapter::setValue);
  connect(&pm.getVAbs(), &ValueModel::valueChanged, pos->getVAbs(), &LabelAdapter::setValue);
  connect(&pm.getWAbs(), &ValueModel::valueChanged, pos->getWAbs(), &LabelAdapter::setValue);

  connect(&pm.getXRel(), &ValueModel::valueChanged, pos->getXRel(), &LabelAdapter::setValue);
  connect(&pm.getYRel(), &ValueModel::valueChanged, pos->getYRel(), &LabelAdapter::setValue);
  connect(&pm.getZRel(), &ValueModel::valueChanged, pos->getZRel(), &LabelAdapter::setValue);
  connect(&pm.getARel(), &ValueModel::valueChanged, pos->getARel(), &LabelAdapter::setValue);
  connect(&pm.getBRel(), &ValueModel::valueChanged, pos->getBRel(), &LabelAdapter::setValue);
  connect(&pm.getCRel(), &ValueModel::valueChanged, pos->getCRel(), &LabelAdapter::setValue);
  connect(&pm.getURel(), &ValueModel::valueChanged, pos->getURel(), &LabelAdapter::setValue);
  connect(&pm.getVRel(), &ValueModel::valueChanged, pos->getVRel(), &LabelAdapter::setValue);
  connect(&pm.getWRel(), &ValueModel::valueChanged, pos->getWRel(), &LabelAdapter::setValue);

  // main menu actions ...
  connect(ui->actionOpen, &QAction::triggered, ed, &EditorDockable::loadFileAlt);
  connect(ui->actionAbsolute_Position, &QAction::triggered, pos, [=](){ pos->setAbsolute(ui->actionAbsolute_Position->isChecked()); });
  connect(ui->actionDefault,  &QAction::triggered, this, &MainWindow::activateTbd);
  connect(ui->actionBack01,   &QAction::triggered, this, &MainWindow::activateBg01);
  connect(ui->actionBack02,   &QAction::triggered, this, &MainWindow::activateBg02);
  connect(ui->actionBack03,   &QAction::triggered, this, &MainWindow::activateBg03);
  connect(ui->actionSettings, &QAction::triggered, this, &MainWindow::activateSettings);
}


void MainWindow::createToolBars() {
  autoTB = new QToolBar(tr("Auto"), this);
  autoTB->setIconSize(QSize(90, 90));
  autoTB->addAction(startAction);
  autoTB->addAction(pauseAction);
  autoTB->addAction(stopAction);
  addToolBar(Qt::BottomToolBarArea, autoTB);

  modeTB = new QToolBar(tr("Mode"), this);
  modeTB->setIconSize(QSize(90, 90));
  modeTB->addAction(autoMode);
  modeTB->addAction(mdiMode);
  modeTB->addAction(editMode);
  modeTB->addAction(jogMode);
  addToolBar(Qt::BottomToolBarArea, modeTB);
  }


void MainWindow::createDockables() {
  QFile geFile("../QtUi/src/UI/GCodeEditor.ui");
  ed = new EditorDockable(geFile, this);
  ed->setAllowedAreas(Qt::AllDockWidgetAreas);
  addDockWidget(Qt::BottomDockWidgetArea, ed);

  QFile posFile("../QtUi/src/UI/Position.ui");
  pos = new PositionDockable(posFile, AxisMask(0x01FF), this);
  pos->setAllowedAreas(Qt::AllDockWidgetAreas);
  addDockWidget(Qt::LeftDockWidgetArea, pos);

  QFile tiFile("../QtUi/src/UI/ToolInfo.ui");
  ti = new ToolInfoDockable(tiFile, this);
  ti->setAllowedAreas(Qt::AllDockWidgetAreas);
  addDockWidget(Qt::LeftDockWidgetArea, ti);

  QFile siFile("../QtUi/src/UI/SpeedInfo.ui");
  si = new SpeedInfoDockable(siFile, this);
  si->setAllowedAreas(Qt::AllDockWidgetAreas);
  addDockWidget(Qt::LeftDockWidgetArea, si);
  }


void MainWindow::createMainWidgets() {
  QFile swFile("../QtUi/src/UI/Settings.ui");
  sw = new SettingsWidget(swFile, this);
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

  /*
  QFile ovFile("../QtUi/src/UI/Overlay.ui");
  overlay = new Overlay(ovFile, this);
  ui->gridLayout->addWidget(overlay, 0, 0);
  */
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


void MainWindow::count() {
  counter.setValue(counter.getValue().toDouble() + 0.001);
  pm.getXRel().setValue(2000 * sin(counter.getValue().toDouble()));
  pm.getYRel().setValue(2000 * cos(counter.getValue().toDouble()));
  pm.getXAbs().setValue(2000 * sin(counter.getValue().toDouble()));
  pm.getYAbs().setValue(2000 * cos(counter.getValue().toDouble()));
  }


#ifndef USE_EVENTLOOP_TIMER
void MainWindow::timerEvent(QTimerEvent *e) {
  if (e->timerId() == timer.timerId())  {
     count();
     }
  else {
     QMainWindow::timerEvent(e);
     }
  }
#endif
