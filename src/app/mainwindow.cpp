#include <mainwindow.h>
#include <ui_mainwindow.h>
//#include <applicationmode.h>
#include <settingsnb.h>
#include <dbconnection.h>
#include <dynaaction.h>
#include <andcondition.h>
#include <orcondition.h>
#include <truecondition.h>
#include <falsecondition.h>
#include <equalcondition.h>
#include <greatercondition.h>
#include <smallercondition.h>
#include <mainview.h>
#include <dockable.h>
#include <core.h>
#include <syseventview.h>
#include <lctooltable.h>
#include <positiondockable.h>
#include <toolinfodockable.h>
#include <speedinfodockable.h>
#include <editordockable.h>
#include <curcodesdockable.h>
#include <maindockable.h>
#include <gcodeviewer.h>
#include <pweditor.h>
#include <patheditor.h>
#include <preferenceseditor.h>
#include <fixturemanager.h>
#include <filemanager.h>
#include <toolmanager.h>
#include <micon.h>
#include <configacc.h>
#include <emc.hh>
#include <QDebug>
#include <QPushButton>
#include <QStyle>
#include <QFileDialog>
#include <math.h>
#include <QImageReader>
#include <QMessageBox>
#include <QImage>
#include <QColorSpace>
#include <QToolBar>
#include <QToolButton>
#include <QVariant>
#include <valuemanager.h>


MainWindow::MainWindow(QWidget *parent)
 : QMainWindow(parent)
 , ui(new Ui::MainWindow)
 , startAction(nullptr)
 , pauseAction(nullptr)
 , stopAction(nullptr)
 , singleStep(nullptr)
 , autoMode(nullptr)
 , mdiMode(nullptr)
 , editMode(nullptr)
 , testEditMode(nullptr)
 , wheelMode(nullptr)
 , jogMode(nullptr)
 , cfgMode(nullptr)
 , msgMode(nullptr)
 , autoTB(nullptr)
 , modeTB(nullptr)
 , powerTB(nullptr)
 , switchTB(nullptr) {
  ui->setupUi(this);
  setObjectName("Falcon-View");
  setDockNestingEnabled(true);
  createActions();
  setupMenu();
  createToolBars();
  createMainWidgets(*Core().databaseConnection());
  createDockables(*Core().databaseConnection());
  createValueModels();
  createConnections();

  // application window
  resize(QSize(1920, 1200));
  Config cfg;

  cfg.beginGroup("MainWindow");
  restoreGeometry(cfg.value("geometry").toByteArray());
  restoreState(cfg.value("windowState").toByteArray());
  cfg.endGroup();
  }


MainWindow::~MainWindow() {
  }


void MainWindow::addDockable(Qt::DockWidgetArea area, Dockable* d) {
  dockables.append(d);
  QMainWindow::addDockWidget(area, d);
  QAction* a = d->toggleViewAction();

  a->setEnabled(true);
  ui->menuView->addAction(a);
  }


void MainWindow::createActions() {
  MIcon::setDisabledFileName(":/res/SK_DisabledIcon.png");
  ValueManager vm;

  qDebug() << "\tMW::createActions() ... START";
  startAction = new DynaAction(MIcon(":/res/SK_AutoStart.png", ":/res/SK_AutoStart_active.png")
                             , tr("Start")
                             , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                                , new EqualCondition(vm.getModel("allHomed"), true)))
                                   ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                             , new OrCondition(new GreaterCondition(vm.getModel("dtg"), 0)
                                             , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_READING))
                             , this);
  startAction->setCheckable(true);
  pauseAction = new DynaAction(MIcon(":/res/SK_AutoPause.png"
                                   , ":/res/SK_AutoPause_active.png")
                             , tr("Pause")
                             , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                               , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_IDLE)))
                                  ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                             , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_PAUSED)
                             , this);
  pauseAction->setCheckable(true);
  stopAction = new DynaAction(MIcon(":/res/SK_AutoStop.png"
                                  , ":/res/SK_AutoStop_active.png")
                            , tr("Stop")
                            , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                              , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_IDLE)))
                                 ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                            , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)
                            , this);
  stopAction->setCheckable(true);
  singleStep = new DynaAction(MIcon(":/res/SK_SingleStep.png"
                                  , ":/res/SK_SingleStep_active.png")
                            , tr("Single-Step")
                            , new AndCondition(new EqualCondition(vm.getModel("taskMode"), EMC_TASK_MODE_ENUM::EMC_TASK_MODE_AUTO)
                                             , new EqualCondition(vm.getModel("errorActive"), false))
                            , new EqualCondition(vm.getModel("singleStep"), true)
                            , this);
  singleStep->setCheckable(true);

  autoMode = new DynaAction(MIcon(":/res/SK_Auto.png"
                                , ":/res/SK_Auto_active.png")
                          , tr("Auto-mode")
                          , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                            , new EqualCondition(vm.getModel("allHomed"), true)))
                               ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                           , new AndCondition(new EqualCondition(vm.getModel("appMode"), ApplicationMode::Auto)
                                            , new EqualCondition(vm.getModel("taskMode"), EMC_TASK_MODE_ENUM::EMC_TASK_MODE_AUTO))
                           , this);
  autoMode->setCheckable(true);
  autoMode->setShortcut(Qt::Key_F3);
  mdiMode = new DynaAction(MIcon(":/res/SK_MDI.png"
                               , ":/res/SK_MDI_active.png")
                         , tr("MDI-mode")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new EqualCondition(vm.getModel("allHomed"), true)))
                              ->addCondition(new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::MDI)
                         , this);
  mdiMode->setCheckable(true);
  mdiMode->setShortcut(Qt::Key_F4);
  editMode = new DynaAction(MIcon(":/res/SK_Edit.png"
                                , ":/res/SK_Edit_active.png")
                          , tr("Edit-mode")
                          , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                            , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                               ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                          , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Edit)
                          , this);
  editMode->setCheckable(true);
  editMode->setShortcut(Qt::Key_F2);
  testEditMode = new DynaAction(MIcon(":/res/SK_TestEdit.png"
                                    , ":/res/SK_TestEdit_active.png")
                              , tr("TestEdit-mode")
                              , new TrueCondition()
                              , new EqualCondition(vm.getModel("appMode"), ApplicationMode::XEdit)
                              , this);
  testEditMode->setCheckable(true);
  testEditMode->setShortcut(Qt::Key_F5);
  cfgMode = new DynaAction(MIcon(":/res/SK_Settings.png"
                               , ":/res/SK_Settings_active.png")
                         , tr("Settings-mode")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Settings)
                         , this);
  cfgMode->setCheckable(true);
  cfgMode->setShortcut(Qt::Key_F9);
  jogMode = new DynaAction(MIcon(":/res/SK_Manual.png"
                               , ":/res/SK_Manual_active.png")
                         , tr("Manual-mode")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Manual)
                         , this);
  jogMode->setCheckable(true);
  jogMode->setShortcut(Qt::Key_F7);
  wheelMode = new DynaAction(MIcon(":/res/SK_Wheel.png"
                                 , ":/res/SK_Wheel_active.png")
                           , tr("Wheel-mode")
                           , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                             , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                                ->addCondition(new FalseCondition())
                                ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                           , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Wheel)
                           , this);
  wheelMode->setCheckable(true);
  wheelMode->setShortcut(Qt::Key_F6);
  wheelMode->setEnabled(false);
  touchMode = new DynaAction(MIcon(":/res/SK_Touch.png"
                                 , ":/res/SK_Touch_active.png")
                           , tr("Touch-mode")
                           , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                             , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                                ->addCondition(new FalseCondition())
                                ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                           , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Touch)
                           , this);
  touchMode->setCheckable(true);
  touchMode->setShortcut(Qt::Key_F8);
  msgMode = new DynaAction(MIcon(":/res/SK_Messages.png"
                               , ":/res/SK_Messages_active.png")
                         , tr("SysEvents")
                         , new TrueCondition()
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::ErrMessages)
                         , this);
  msgMode->setCheckable(true);
  msgMode->setShortcut(Qt::Key_F10);

  mist = new DynaAction(MIcon(":/res/SK_Cool_Mist.png"
                            , ":/res/SK_Cool_Mist_active.png")
                      , tr("cool-Mist")
                      , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                       , new EqualCondition(vm.getModel("errorActive"), false))
                      , new EqualCondition(vm.getModel("coolMist"), true)
                      , this);
  mist->setCheckable(true);
  flood = new DynaAction(MIcon(":/res/SK_Cool_Flood.png"
                             , ":/res/SK_Cool_Flood_active.png")
                       , tr("cool-Flood")
                       , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                        , new EqualCondition(vm.getModel("errorActive"), false))
                       , new EqualCondition(vm.getModel("coolFlood"), true)
                       , this);
  flood->setCheckable(true);
  QActionGroup* sg = new QActionGroup(this);

  spindleLeft = new DynaAction(MIcon(":/res/SK_Spindle_CCW.png"
                                   , ":/res/SK_Spindle_CCW_active.png")
                             , tr("spindle-CCW")
                             , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                              , new EqualCondition(vm.getModel("errorActive"), false))
                             , new EqualCondition(vm.getModel("spindle0Dir"), -1)
                             , this);
  spindleLeft->setCheckable(true);
  sg->addAction(spindleLeft);
  spindleOff = new DynaAction(MIcon(":/res/SK_Spindle_Stop.png"
                                  , ":/res/SK_Spindle_Stop_active.png")
                            , tr("spindle-Off")
                            , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                             , new EqualCondition(vm.getModel("errorActive"), false))
                            , new EqualCondition(vm.getModel("spindle0Dir"), 0)
                            , this);
  spindleOff->setCheckable(true);
  sg->addAction(spindleOff);
  spindleRight = new DynaAction(MIcon(":/res/SK_Spindle_CW.png"
                                    , ":/res/SK_Spindle_CW_active.png")
                              , tr("spindle-CW")
                              , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                               , new EqualCondition(vm.getModel("errorActive"), false))
                              , new EqualCondition(vm.getModel("spindle0Dir"), 1)
                              , this);
  spindleRight->setCheckable(true);
  sg->addAction(spindleRight);
  homeAll = new DynaAction(MIcon(":/res/SK_HomeAll.png"
                               , ":/res/SK_HomeAll_active.png")
                         , tr("Home-all")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new EqualCondition(vm.getModel("homeAll"), false)))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("homeAll"), true)
                         , this);
  homeAll->setCheckable(true);
  posAbsolute = new DynaAction(MIcon(":/res/SK_PosAbsolute.png"
                                   , ":/res/SK_PosRelative.png")
                             , tr("Pos-Type")
                             , new TrueCondition()
                             , new EqualCondition(vm.getModel("showAbsolute"), true)
                             , this);
  posAbsolute->setCheckable(true);

  power       = new DynaAction(MIcon(":/res/SK_PowerOff.png"
                                   , ":/res/SK_PowerOn.png")
                             , tr("Poweroff")
                             , new TrueCondition()
                             , new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                             , this);
  power->setCheckable(true);
  qDebug() << "\tMW::createActions() ... END";
  }


void MainWindow::setupMenu() {
  ui->menuMode->addAction(editMode);
  ui->menuMode->addAction(autoMode);
  ui->menuMode->addAction(mdiMode);
  ui->menuMode->addAction(testEditMode);
  ui->menuMode->addAction(wheelMode);
  ui->menuMode->addAction(jogMode);
  ui->menuMode->addAction(touchMode);
  ui->menuMode->addAction(cfgMode);
  ui->menuMode->addAction(msgMode);
  }

void MainWindow::createValueModels() {
  ValueManager vm;

  vm.setValue("showAbsolute", false);
  }


void MainWindow::createConnections() {
  ValueManager vm;

  connect(vm.getModel("appMode"), &ValueModel::valueChanged, this,  &MainWindow::appModeChanged);
  connect(vm.getModel("showAllButCenter"), &ValueModel::valueChanged, this, &MainWindow::toggleAllButCenter);
  connect(ui->actionAbsPos,    &QAction::triggered, pos,  [=](){ pos->setAbsolute(QVariant(ui->actionAbsPos->isChecked())); });
  connect(ui->actionDockables, &QAction::triggered, this, [=](){ Core().showAllButCenter(ui->actionDockables->isChecked()); });
  connect(ui->actionExit,      &QAction::triggered, this, &QWidget::close);

  // main menu actions ...
  connect(autoMode, &QAction::triggered, this, [=](){ Core().setAppMode(ApplicationMode::Auto); });
  connect(mdiMode, &QAction::triggered, this,  [=](){ Core().setAppMode(ApplicationMode::MDI); });
  connect(editMode, &QAction::triggered, this, [=](){ Core().setAppMode(ApplicationMode::Edit); });
  connect(testEditMode, &QAction::triggered, this, [=](){ Core().setAppMode(ApplicationMode::XEdit); });
  connect(cfgMode, &QAction::triggered, this, [=](){ Core().setAppMode(ApplicationMode::Settings); });
  connect(jogMode, &QAction::triggered, this, [=](){ Core().setAppMode(ApplicationMode::Manual); });
  connect(wheelMode, &QAction::triggered, this, [=](){ Core().setAppMode(ApplicationMode::Wheel); });
  connect(touchMode, &QAction::triggered, this, [=](){ Core().setAppMode(ApplicationMode::Touch); });
  connect(posAbsolute, &QAction::triggered, pos, [=](){ pos->setAbsolute(QVariant(posAbsolute->isChecked())); });
  connect(msgMode, &QAction::triggered, this, &MainWindow::toggleErrMessages);
  connect(singleStep, &QAction::triggered, this, &MainWindow::setSingleStep);
  }


void MainWindow::setSingleStep(bool singleStep) {
  ValueManager().setValue("singleStep", singleStep);
  }


void MainWindow::toggleErrMessages() {
  static QString oldPage;

  if (msgMode->isChecked()) {
     ValueManager().setValue("errorActive", true);
     if (oldPage.isEmpty()) oldPage = Core().curPage();
     Core().activatePage(SysEventView::className);
     ValueManager().setValue("showAllButCenter", false);
     }
  else {
     ValueManager().setValue("errorActive", false);
     if (!oldPage.isEmpty()) {
        Core().activatePage(oldPage);
        oldPage.clear();
        }
     ValueManager().setValue("showAllButCenter", true);
     }
  }


void MainWindow::appModeChanged(const QVariant& appMode) {
  ApplicationMode m = static_cast<ApplicationMode>(appMode.toInt());

  switch (m) {
    case Auto:        Core().activatePage(PreViewEditor::className); break;
    case MDI:         Core().activatePage(tr("mdiView")); break;
    case Manual:      Core().activatePage(tr("manualJogView")); break;
    case Edit:        Core().activatePage(PathEditor::className); break;
    case Wheel:       Core().activatePage(tr("Wheely")); break;
    case XEdit:       Core().activatePage(TestEdit::className); break;
    case Settings:    Core().activatePage(SettingsNotebook::className); break;
    case Touch:       Core().activatePage(tr("TouchView")); break;
    case ErrMessages: Core().activatePage(SysEventView::className); break;
    default: break;
    }
  }


void MainWindow::toggleAllButCenter() {
  ValueModel* m = ValueManager().getModel("showAllButCenter");
  bool visible = m->getValue().toBool();

  for (int i=0; i < dockables.size(); ++i)
      dockables.at(i)->setVisible(visible);      
  autoTB->setVisible(visible);
  modeTB->setVisible(visible);
  nopTB->setVisible(visible);
  powerTB->setVisible(visible);
  switchTB->setVisible(visible);
  }


void MainWindow::closeEvent(QCloseEvent* e) {
  QMessageBox::StandardButton reply;

  reply = QMessageBox::question(this
                              , tr("close application?")
                              , tr("<p>closing the application means shutting down "
                                   "the backend and stopping all services IF ui "
                                   "has been started by linuxcnc start-helper</p>")
                              , QMessageBox::Yes | QMessageBox::Cancel);
  if (reply == QMessageBox::Yes) {
     Core().windowClosing(e);
     QMainWindow::closeEvent(e);
     }
  else e->ignore();
  }


void MainWindow::createToolBars() {
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
  modeTB->addAction(editMode);
  modeTB->addAction(autoMode);
  modeTB->addAction(mdiMode);
  modeTB->addAction(testEditMode);
  modeTB->addAction(wheelMode);
  modeTB->addAction(jogMode);
  modeTB->addAction(touchMode);
  modeTB->addAction(cfgMode);
  addToolBar(Qt::BottomToolBarArea, modeTB);

  QWidget* ab = modeTB->widgetForAction(editMode);

  if (ab && ab->autoFillBackground()) {
     qDebug() << ">>>>>> ToolbarButton.autoFill set <<<<<<<<<<<<<<<";
     }
  nopTB = new QToolBar(tr("NOP"), this);
  nopTB->setObjectName("NopTB");
  nopTB->setIconSize(s);
  nopTB->addAction(homeAll);  
  nopTB->addAction(posAbsolute);
  nopTB->addAction(msgMode);
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

  auto pushButton = new QPushButton("Tristate button");
  pushButton->setProperty("state", 0);
  pushButton->setProperty("state-step", 1); // change to next state, 1 or -1
  pushButton->setStyleSheet("QPushButton[state=\"0\"] { background: red; }"
                            "QPushButton[state=\"1\"] { background: grey; }"
                            "QPushButton[state=\"2\"] { background: blue; }");
  connect(pushButton, &QPushButton::clicked, [=](bool) {
    const int state = pushButton->property("state").toInt();
    const int step = state == 0 ? 1 :
                     state == 2 ? -1 : pushButton->property("state-step").toInt();
    pushButton->setProperty("state", state + step);
    pushButton->setProperty("state-step", step); // update in case it changed

    // Changing the property is not enough to choose a new style from the stylesheet,
    //  it is necessary to force a re-evaluation
    pushButton->style()->unpolish(pushButton);
    pushButton->style()->polish(pushButton);
    tellStates();
    });

//  powerTB->addAction(power);
  powerTB->addWidget(pushButton);
  addToolBar(Qt::BottomToolBarArea, powerTB);
  }


void MainWindow::tellStates() const {
  ValueManager vm;

  qDebug() << "MW::tellStates()";
  vm.getModel("appMode")->dump();
  vm.getModel("allHomed")->dump();
  vm.getModel("taskState")->dump();
  vm.getModel("taskMode")->dump();
  vm.getModel("interpState")->dump();
  vm.getModel("execState")->dump();
  vm.getModel("errorActive")->dump();
  vm.getModel("showAbsolute")->dump();
  vm.setValue("errorActive", false);
  }


void MainWindow::createDockables(DBConnection&) {
  addDockable(Qt::LeftDockWidgetArea,   new ToolInfoDockable(":/src/UI/ToolInfo.ui", this));
  addDockable(Qt::LeftDockWidgetArea,   new CurCodesDockable(":/src/UI/CurCodes.ui", this));
  addDockable(Qt::LeftDockWidgetArea,   pos = new PositionDockable(":/src/UI/Position.ui", Core().axisMask(), this));
  addDockable(Qt::BottomDockWidgetArea, new SpeedInfoDockable(":/src/UI/SpeedInfo.ui", this));
  }


void MainWindow::createMainWidgets(DBConnection& conn) {
  MainView*  mainView = new MainView(this);
  DynWidget* page     = new PreViewEditor(":/src/UI/GCodeEditor.ui", Core().view3D(), mainView);

  Core().setViewStack(mainView);
  mainView->addPage(page);
  ui->menuMain->addAction(page->viewAction());

  page = new FileManager(QDir(QDir::homePath() + "/linuxcnc"), mainView);
  mainView->addPage(page);
//  ui->menuMain->addAction(page->viewAction());

  page = new PathEditor(":/src/UI/GCodeEditor.ui", mainView);
  mainView->addPage(page);
  ui->menuMain->addAction(page->viewAction());

  page = new TestEdit(":/src/UI/GCodeEditor.ui", mainView);
  mainView->addPage(page);
  ui->menuMain->addAction(page->viewAction());

  page = new SysEventView(conn, mainView);
  mainView->addPage(page);
//  ui->menuMain->addAction(page->viewAction());
  SettingsNotebook* nb = new SettingsNotebook(this);

  nb->addPage(new ToolManager(conn, nb));
  nb->addPage(new FixtureManager(Core().axisMask(), nb));
  nb->addPage(new PreferencesEditor(":/src/UI/Settings.ui", nb));
  nb->addPage(new LCToolTable());
  mainView->addPage(nb);
  ui->menuMain->addAction(nb->viewAction());

  this->setCentralWidget(mainView);
  mainView->dump();
  }


void MainWindow::keyPressEvent(QKeyEvent* e) {
  switch (e->key()) {
    case Qt::Key_Escape:
         qDebug() << "MW: escape pressed! But don't do anything!";
         e->accept();
         break;
    case Qt::Key_F1:
    case Qt::Key_F2:
    case Qt::Key_F3:
    case Qt::Key_F4:
    case Qt::Key_F5:
    case Qt::Key_F6:
    case Qt::Key_F7:
    case Qt::Key_F8:
    case Qt::Key_F9:
    case Qt::Key_F10:
    case Qt::Key_F11:
    case Qt::Key_F12:
//         e->accept();
//         break;
    default:
         qDebug() << "MW: pressed key: " << e->key();
         qDebug() << "MW: modifiers: "   << e->modifiers();
         QMainWindow::keyPressEvent(e);
         break;
    }
  }
