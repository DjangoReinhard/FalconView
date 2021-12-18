#include <mainwindow.h>
#include <ui_mainwindow.h>
#include <helpdialog.h>
#include <occtviewer.h>
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
#include <centerview.h>
#include <dyndockable.h>
#include <dynframe.h>
#include <jogview.h>
#include <mdieditor.h>
#include <core.h>
#include <syseventview.h>
#include <lctooltable.h>
#include <positionstatus.h>
#include <toolstatus.h>
#include <speedstatus.h>
#include <curcodesstatus.h>
#include <multistateaction.h>
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
#include <Standard_Version.hxx>
#include <config.h>


MainWindow::MainWindow(bool statusInPreview, QWidget *parent)
 : QMainWindow(parent)
 , statusInPreview(statusInPreview)
 , ui(new Ui::MainWindow)
 , dlgHelp(nullptr)
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
//  timer.start(1000, this);
  qDebug() << "MainWindow - statusInPreview:" << (statusInPreview ? "TRUE" : "FALSE");
  }


MainWindow::~MainWindow() {
  }


void MainWindow::addDockable(Qt::DockWidgetArea area, DynDockable* d) {
  d->initialize();
  dockables.append(d);
  QMainWindow::addDockWidget(area, d);
  QAction* a = d->toggleViewAction();

  a->setEnabled(true);
  ui->menuView->addAction(a);
  }


void MainWindow::createActions() {
  ValueManager vm;

  ui->actionAbsPos->setIcon(MIcon(":/res/SK_PosRelative.png"
                                , ":/res/SK_PosAbsolute.png"));
//  qDebug() << "\tMW::createActions() ... START";
  startAction = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                             , QIcon(":/res/SK_AutoStart.png")
                             , QIcon(":/res/SK_AutoStart_active.png")
                             , tr("Start")
                             , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                                , new EqualCondition(vm.getModel("allHomed"), true)))
                                   ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                             , new OrCondition(new GreaterCondition(vm.getModel("dtg"), 0)
                                             , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_READING))
                             , this);
  pauseAction = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                             , QIcon(":/res/SK_AutoPause.png")
                             , QIcon(":/res/SK_AutoPause_active.png")
                             , tr("Pause")
                             , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                               , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_WAITING)))
                                  ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                             , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_PAUSED)
                             , this);
  stopAction = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                            , QIcon(":/res/SK_AutoStop.png")
                            , QIcon(":/res/SK_AutoStop_active.png")
                            , tr("Stop")
                            , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                              , new EqualCondition(vm.getModel("interpState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_WAITING)))
                                 ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                            , new EqualCondition(vm.getModel("execState"), EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_IDLE)
                            , this);
  singleStep = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                            , QIcon(":/res/SK_SingleStep.png")
                            , QIcon(":/res/SK_SingleStep_active.png")
                            , tr("Single-Step")
                            , new AndCondition(new EqualCondition(vm.getModel("taskMode"), EMC_TASK_MODE_ENUM::EMC_TASK_MODE_AUTO)
                                             , new EqualCondition(vm.getModel("errorActive"), false))
                            , new EqualCondition(vm.getModel("singleStep"), true)
                            , this);
  singleStep->setCheckable(true);

  autoMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                          , QIcon(":/res/SK_Auto.png")
                          , QIcon(":/res/SK_Auto_active.png")
                          , tr("Auto-mode")
                          , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                            , new EqualCondition(vm.getModel("allHomed"), true)))
                               ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                           , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Auto)
                           , this);
  mdiMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                         , QIcon(":/res/SK_MDI.png")
                         , QIcon(":/res/SK_MDI_active.png")
                         , tr("MDI-mode")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new EqualCondition(vm.getModel("allHomed"), true)))
                              ->addCondition(new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::MDI)
                         , this);
  editMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                          , QIcon(":/res/SK_Edit.png")
                          , QIcon(":/res/SK_Edit_active.png")
                          , tr("Edit-mode")
                          , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                            , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                               ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                          , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Edit)
                          , this);
  testEditMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                              , QIcon(":/res/SK_TestEdit.png")
                              , QIcon(":/res/SK_TestEdit_active.png")
                              , tr("TestEdit-mode")
                              , new TrueCondition()
                              , new EqualCondition(vm.getModel("appMode"), ApplicationMode::XEdit)
                              , this);
  cfgMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                         , QIcon(":/res/SK_Settings.png")
                         , QIcon(":/res/SK_Settings_active.png")
                         , tr("Settings-mode")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Settings)
                         , this);
  jogMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                         , QIcon(":/res/SK_Manual.png")
                         , QIcon(":/res/SK_Manual_active.png")
                         , tr("Manual-mode")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Manual)
                         , this);
  wheelMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                           , QIcon(":/res/SK_Wheel.png")
                           , QIcon(":/res/SK_Wheel_active.png")
                           , tr("Wheel-mode")
                           , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                             , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                                ->addCondition(new FalseCondition())
                                ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                           , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Wheel)
                           , this);
  wheelMode->setEnabled(false);
  touchMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                           , QIcon(":/res/SK_Touch.png")
                           , QIcon(":/res/SK_Touch_active.png")
                           , tr("Touch-mode")
                           , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                             , new SmallerCondition(vm.getModel("execState"), EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION)))
                                ->addCondition(new FalseCondition())
                                ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                           , new EqualCondition(vm.getModel("appMode"), ApplicationMode::Touch)
                           , this);
  msgMode = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                         , QIcon(":/res/SK_Messages.png")
                         , QIcon(":/res/SK_Messages_active.png")
                         , tr("SysEvents")
                         , new TrueCondition()
                         , new EqualCondition(vm.getModel("appMode"), ApplicationMode::ErrMessages)
                         , this);
  mist = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                      , QIcon(":/res/SK_Cool_Mist.png")
                      , QIcon(":/res/SK_Cool_Mist_active.png")
                      , tr("cool-Mist")
                      , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                       , new EqualCondition(vm.getModel("errorActive"), false))
                      , new EqualCondition(vm.getModel("coolMist"), true)
                      , this);
  flood = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                       , QIcon(":/res/SK_Cool_Flood.png")
                       , QIcon(":/res/SK_Cool_Flood_active.png")
                       , tr("cool-Flood")
                       , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                        , new EqualCondition(vm.getModel("errorActive"), false))
                       , new EqualCondition(vm.getModel("coolFlood"), true)
                       , this);
  QActionGroup* sg = new QActionGroup(this);

  spindleLeft = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                             , QIcon(":/res/SK_Spindle_CCW.png")
                             , QIcon(":/res/SK_Spindle_CCW_active.png")
                             , tr("spindle-CCW")
                             , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                              , new EqualCondition(vm.getModel("errorActive"), false))
                             , new EqualCondition(vm.getModel("spindle0Dir"), -1)
                             , this);
  sg->addAction(spindleLeft);
  spindleOff = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                            , QIcon(":/res/SK_Spindle_Stop.png")
                            , QIcon(":/res/SK_Spindle_Stop_active.png")
                            , tr("spindle-Off")
                            , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                             , new EqualCondition(vm.getModel("errorActive"), false))
                            , new EqualCondition(vm.getModel("spindle0Dir"), 0)
                            , this);
  sg->addAction(spindleOff);
  spindleRight = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                              , QIcon(":/res/SK_Spindle_CW.png")
                              , QIcon(":/res/SK_Spindle_CW_active.png")
                              , tr("spindle-CW")
                              , new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                               , new EqualCondition(vm.getModel("errorActive"), false))
                              , new EqualCondition(vm.getModel("spindle0Dir"), 1)
                              , this);
  sg->addAction(spindleRight);
  homeAll = new DynaAction(QIcon(":/res/SK_DisabledIcon.png")
                         , QIcon(":/res/SK_HomeAll.png")
                         , QIcon(":/res/SK_HomeAll_active.png")
                         , tr("Home-all")
                         , (new AndCondition(new EqualCondition(vm.getModel("taskState"), EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON)
                                           , new EqualCondition(vm.getModel("allHomed"), false)))
                              ->addCondition(new EqualCondition(vm.getModel("errorActive"), false))
                         , new EqualCondition(vm.getModel("allHomed"), true)
                         , this);

  power = new MultiStateAction(vm.getModel("taskState")
                             , QIcon(":/res/SK_PowerOff.png")
                             , QIcon(":/res/SK_PowerOff_1.png")
                             , QIcon(":/res/SK_PowerOn.png"));
  power->setShortcut(QKeySequence("CTRL+ALT+P"));
//  qDebug() << "\tMW::createActions() ... END";
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
  ui->actionHelp->setShortcut(QKeySequence::HelpContents);
  }


void MainWindow::createValueModels() {
  ValueManager vm;

  ui->actionAbsPos->setChecked(false);
  vm.setValue("showAbsolute", false);
  }


void MainWindow::toggleAbsolute(const QVariant& absolute) {
  qDebug() << "Mainwindow::toggleAbsolute(" << (absolute.toBool() ? "TRUE" : "FALSE") << ")";
  ValueManager().setValue("showAbsolute", absolute.toBool());
  }


void MainWindow::createConnections() {
  ValueManager vm;

  connect(vm.getModel("appMode"), &ValueModel::valueChanged, this,  &MainWindow::appModeChanged);
  connect(vm.getModel("showAllButCenter"), &ValueModel::valueChanged, this, &MainWindow::toggleAllButCenter);
  connect(ui->actionAbsPos,    &QAction::triggered, this, &MainWindow::toggleAbsolute);
  connect(ui->actionDockables, &QAction::triggered, this, [=](){ ValueManager().setValue("showAllButCenter", ui->actionDockables->isChecked()); });
  connect(ui->actionExit,      &QAction::triggered, this, &QWidget::close);
  connect(ui->actionAbout,     &QAction::triggered, this, &MainWindow::about);

  connect(ui->action3D_View,   &QAction::triggered, Core().view3D(), &OcctQtViewer::isoView);
  connect(ui->actionFrontView, &QAction::triggered, Core().view3D(), &OcctQtViewer::frontView);
  connect(ui->actionBackView,  &QAction::triggered, Core().view3D(), &OcctQtViewer::backView);
  connect(ui->actionleftView,  &QAction::triggered, Core().view3D(), &OcctQtViewer::leftView);
  connect(ui->actionrightView, &QAction::triggered, Core().view3D(), &OcctQtViewer::rightView);
  connect(ui->actionTopView,   &QAction::triggered, Core().view3D(), &OcctQtViewer::topView);
  connect(ui->actionHelp,      &QAction::triggered, dlgHelp,         &HelpDialog::showHelp);

  connect(ui->actionJog_Simulator, &QAction::triggered, pw, &PreViewEditor::toggleSub);

  // be actions ...
  connect(startAction,  &QAction::triggered, this, &MainWindow::autoStart);
  connect(pauseAction,  &QAction::triggered, this, &MainWindow::autoPause);
  connect(stopAction,   &QAction::triggered, this, &MainWindow::autoStop);
  connect(singleStep,   &QAction::triggered, this, &MainWindow::setSingleStep);
  connect(homeAll,      &QAction::triggered, this, &MainWindow::homeAxis);

  connect(autoMode,     &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::Auto); });
  connect(mdiMode,      &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::MDI); });
  connect(editMode,     &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::Edit); });
  connect(testEditMode, &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::XEdit); });
  connect(wheelMode,    &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::Wheel); });
  connect(jogMode,      &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::Manual); });
  connect(cfgMode,      &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::Settings); });
  connect(msgMode,      &QAction::triggered, this, &MainWindow::toggleErrMessages);
  connect(touchMode,    &QAction::triggered, this, [=](){ setAppMode(ApplicationMode::Touch); });

  connect(power,        &QAction::triggered, this, &MainWindow::hitPowerBtn);
  connect(mist,         &QAction::triggered, this, &MainWindow::mistToggle);
  connect(flood,        &QAction::triggered, this, &MainWindow::floodToggle);
  connect(spindleLeft,  &QAction::triggered, this, &MainWindow::startSpindleCCW);
  connect(spindleRight, &QAction::triggered, this, &MainWindow::startSpindleCW);
  connect(spindleOff,   &QAction::triggered, this, &MainWindow::stopSpindle);
  }


void MainWindow::toggleErrMessages() {
  static QString oldPage;

  qDebug() << "MW::toggleErrMessages() ...";
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
    case MDI:         Core().activatePage(MDIEditor::className); break;
    case Manual:      Core().activatePage(JogView::className); break;
    case Edit:        Core().activatePage(PathEditor::className); break;
    case Wheel:       Core().activatePage(tr("Wheely")); break;
    case XEdit:       Core().activatePage(TestEdit::className); break;
    case Settings:    Core().activatePage(SettingsNotebook::className); break;
    case Touch:       Core().activatePage(tr("TouchView")); break;
    case ErrMessages: Core().activatePage(SysEventView::className); break;
    default: break;
    }
  }


void MainWindow::about() {
  QString glInfo = Core().view3D()->getGlInfo();

  if (glInfo.isEmpty()) glInfo = tr("You need to switch to 3D-preview "
                                    "at least once to get this information.");
  else                  glInfo.replace("\n", "</li><li>");
  QMessageBox::about(this
                   , tr("About FalconView")
                   , tr("<h3>FalconView</h3><p>is an application to manage "
                        "machines controlled by linuxCNC.</p>"
                        "<p>FalconView uses external components:<ul>"
                        "<li><a href=\"%1\">linuxCNC v.%2</a></li>"
                        "<li><a href=\"%3\">Open CASCADE Technology v.%4</a></li>"
                        "<li><a href=\"%5\">Qt Toolkit v.%6</a></li></ul></p>"
                        "<hl/><p>GL capabilities: <ul><li>%7</li></ul></p>")
                       .arg("https://github.com/LinuxCNC/linuxcnc", PACKAGE_VERSION)
                       .arg("https://dev.opencascade.org/release", OCC_VERSION_STRING_EXT)
                      .arg("https://www.qt.io/download", QLatin1String(QT_VERSION_STR))
                       .arg(glInfo)
                       .toStdString().c_str());
  }


void MainWindow::toggleAllButCenter() {
  ValueModel* m = ValueManager().getModel("showAllButCenter");  
  bool visible = m->getValue().toBool();

  if (!statusInPreview) {
     for (int i=0; i < dockables.size(); ++i)
         dockables.at(i)->setVisible(visible);
     }
  autoTB->setVisible(visible);
  modeTB->setVisible(visible);
  topTB->setVisible(visible);
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

  topTB = new QToolBar(tr("TOP"), this);
  topTB->setObjectName("TopTB");
  topTB->setIconSize(s);
  topTB->addAction(homeAll);
  topTB->addAction(ui->actionAbsPos);
  topTB->addAction(msgMode);
  addToolBar(Qt::RightToolBarArea, topTB);

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
  vm.getModel("singleStep")->dump();
  }


void MainWindow::createDockables(DBConnection&) {
  qDebug() << "MainWindow::createDockables() - statusInPreview:"
           << (statusInPreview ? "TRUE" : "FALSE");

  if (!statusInPreview) {
     addDockable(Qt::LeftDockWidgetArea
               , new DynDockable(new PositionStatus(":/src/UI/Position.ui"
                                                  , Core().axisMask())
                               , this));
     addDockable(Qt::LeftDockWidgetArea
               , new DynDockable(new ToolStatus(":/src/UI/ToolInfo.ui")
                               , this));
     addDockable(Qt::BottomDockWidgetArea
               , new DynDockable(new SpeedStatus(":/src/UI/HSpeedInfo.ui")
                               , this));
     addDockable(Qt::LeftDockWidgetArea
               , new DynDockable(new CurCodesStatus(":/src/UI/HCurCodes.ui")
                               , this));
     }
  dlgHelp = new HelpDialog(this);
  addDockWidget(Qt::BottomDockWidgetArea, dlgHelp);
  }


void MainWindow::createMainWidgets(DBConnection& conn) {
  CenterView* center = new CenterView(this);
  DynFrame*   page   = new DynFrame(pw = new PreViewEditor(":/src/UI/GCodeEditor.ui"
                                                         , Core().view3D()
                                                         , statusInPreview)
                                  , true
                                  , center);

  Core().setViewStack(center);
  center->addPage(page);
  page = new DynFrame(new FileManager(QDir(QDir::homePath() + "/linuxcnc/nc_files"))
                    , true
                    , center);
  center->addPage(page);
  page = new DynFrame(new TestEdit(":/src/UI/GCodeEditor.ui")
                    , true
                    , center);
  center->addPage(page);
  page = new DynFrame(new MDIEditor(":/src/UI/MDIEditor.ui")
                    , true
                    , center);
  center->addPage(page);
  page = new DynFrame(new SysEventView(conn)
                    , true
                    , center);
  center->addPage(page);
  page = new DynFrame(new PathEditor(":/src/UI/GCodeEditor.ui")
                    , true
                    , center);
  center->addPage(page);
  SettingsNotebook* nb = new SettingsNotebook(this);

  center->addPage(new DynFrame(nb, false, center));
  if (Config().value("activateToolMgr").toBool()) nb->addPage(new ToolManager(conn, nb));
  nb->addPage(new FixtureManager(Core().axisMask(), nb));
  nb->addPage(new PreferencesEditor(":/src/UI/Settings.ui", nb));
  nb->addPage(new LCToolTable());
  page = new DynFrame(new JogView()
                    , true
                    , center);
  center->addPage(page);
  page   = new DynFrame(pw = new PreViewEditor(":/src/UI/GCodeEditor.ui"
                                             , Core().view3D()
                                             , statusInPreview)
                      , true
                      , center);
  center->addPage(page);
  this->setCentralWidget(center);
//  center->dump(); //TODO!
  }


void MainWindow::hitPowerBtn() {
  int ns;

  switch (ValueManager().getValue("taskState").toInt()) {
    case EMC_TASK_STATE_ENUM::EMC_TASK_STATE_OFF:
         qDebug() << "switch taskstate from OFF to ON";
         ns = EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON;
         break;
    case EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON:
         qDebug() << "switch taskstate from ON to ESTOP";
         ns = EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ESTOP;
         break;
    case EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ESTOP_RESET:
         qDebug() << "switch taskstate from ESTOP_RESET to ON";
         ns = EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON;
         break;
    default:
         qDebug() << "new taskstate is ESTOP_RESET";
         ns = EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ESTOP_RESET;
         break;
    }
//  tellStates();
  Core().beSetTaskState(ns);
  }


void MainWindow::setSingleStep(bool singleStep) {
  ValueManager().setValue("singleStep", singleStep);
  }


void MainWindow::autoStart() {
//  ApplicationMode am = ValueManager().getValue("appMode").value<ApplicationMode>();
  int am = 0;

  if (am == ApplicationMode::MDI) {
     Core().beSetTaskMode(EMC_TASK_MODE_ENUM::EMC_TASK_MODE_MDI);
//     Core().beSetMDI();
     qDebug() << "execute MDI: " << "¿what?";
     }
  else if (am == ApplicationMode::Auto) {
     qDebug() << "start auto NC execution ...";
     Core().beSetTaskMode(EMC_TASK_MODE_ENUM::EMC_TASK_MODE_AUTO);
     if (ValueManager().getValue("singleStep").toBool()) {
        qDebug() << "singlestep is ON";
        Core().beSetAuto(3, 0);
        }
     else {
        qDebug() << "singlestep is OFF";
        Core().beSetAuto(0, 0);
        }
     }
  }


void MainWindow::autoPause() {
  int iState = ValueManager().getValue("interpState").toInt();

  if (iState == EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_PAUSED) {
     Core().beSetAuto(2, 0);
     }
  else {
     Core().beSetAuto(1, 0);
     }
  }


void MainWindow::autoStop() {
  Core().beAbortTask();
  Core().beSetTaskMode(EMC_TASK_MODE_ENUM::EMC_TASK_MODE_MANUAL);
  Core().beTaskPlanSynch();
  }


void MainWindow::homeAxis() {
  Core().beHomeAxis(-1);
  }


void MainWindow::mistToggle() {
  ValueModel* vm = ValueManager().getModel("coolMist");

  Core().beEnableMist(!vm->getValue().toBool());
  }


void MainWindow::floodToggle() {
  ValueModel* vm = ValueManager().getModel("coolFlood");

  Core().beEnableMist(!vm->getValue().toBool());
  }


void MainWindow::startSpindleCCW() {
  double speed = ValueManager().getValue("spindle0Speed").toDouble();
  int    dir   = ValueManager().getValue("spindle0Dir").toInt();

  Core().beSetSpindle(0, speed, dir);
  }


void MainWindow::startSpindleCW() {
  double speed = ValueManager().getValue("spindle0Speed").toDouble();
  int    dir   = ValueManager().getValue("spindle0Dir").toInt();

  Core().beSetSpindle(0, speed, dir);
  }


void MainWindow::stopSpindle() {
  double speed = ValueManager().getValue("spindle0Speed").toDouble();
  int    dir   = ValueManager().getValue("spindle0Dir").toInt();

  Core().beSetSpindle(0, speed, dir);
  }


void MainWindow::setAppMode(ApplicationMode am) {
  ApplicationMode oam = static_cast<ApplicationMode>(ValueManager().getValue("appMode").toInt());
  ValueManager().setValue("appMode", am);

  qDebug() << "\tsetAppMode: " << am << "\twas:" << oam;
  if (am == ApplicationMode::Auto)
     Core().beSetTaskMode(EMC_TASK_MODE_ENUM::EMC_TASK_MODE_AUTO);
  else if (am == ApplicationMode::MDI)
     Core().beSetTaskMode(EMC_TASK_MODE_ENUM::EMC_TASK_MODE_MDI);
  else
     Core().beSetTaskMode(EMC_TASK_MODE_ENUM::EMC_TASK_MODE_MANUAL);
  }


void MainWindow::timerEvent(QTimerEvent* ) {
//  if (e->timerId() == timer.timerId()) tellStates();
  }


void MainWindow::keyPressEvent(QKeyEvent* e) {
    switch (e->key()) {
    case Qt::Key_Escape:
         if (Core().curPage() == SysEventView::className) {
            msgMode->toggle();
            toggleErrMessages();
            }
         else
            qDebug() << "MW: escape pressed! But don't do anything!";
         e->accept();
         break;
    case Qt::Key_H:
         if (e->modifiers() == int(Qt::CTRL | Qt::ALT) && !ValueManager().getValue("allHomed").toBool()) {
            e->accept();
            homeAll->trigger();
            break;
            }
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
         if (modeTB->isVisible()) {
            qDebug() << "mode toolbar is visible";
            switch (e->key()) {
              case Qt::Key_F2:  ValueManager().setValue("appMode", ApplicationMode::Edit); break;
              case Qt::Key_F3:  ValueManager().setValue("appMode", ApplicationMode::Auto); break;
              case Qt::Key_F4:  ValueManager().setValue("appMode", ApplicationMode::MDI); break;
              case Qt::Key_F5:  ValueManager().setValue("appMode", ApplicationMode::XEdit); break;
              case Qt::Key_F6:  ValueManager().setValue("appMode", ApplicationMode::Wheel); break;
              case Qt::Key_F7:  ValueManager().setValue("appMode", ApplicationMode::Manual); break;
              case Qt::Key_F8:  ValueManager().setValue("appMode", ApplicationMode::Touch); break;
              case Qt::Key_F9:  ValueManager().setValue("appMode", ApplicationMode::Settings); break;
              case Qt::Key_F10: ValueManager().setValue("appMode", ApplicationMode::ErrMessages); break;
              case Qt::Key_F11: startAction->trigger(); break;
              case Qt::Key_F12: stopAction->trigger(); break;
              }
            e->accept();
            break;
            }
         else qDebug() << "mode toolbar is NOT visible";

    default:
         qDebug() << "MW: pressed key: " << e->key()
                  << "modifiers: "   << e->modifiers()
                  << "event-ts: " << e->timestamp();
         Core().viewStack()->keyPressEvent(e);
         break;
    }
  }


void MainWindow::keyReleaseEvent(QKeyEvent* e) {
  qDebug() << "MW: released key: " << e->key()
           << "modifiers: "   << e->modifiers()
           << "event-ts: " << e->timestamp();
  Core().viewStack()->keyReleaseEvent(e);
  }
