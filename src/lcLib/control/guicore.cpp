#include <guikernel.h>
#include <guicore.h>
#include <kernelcreator.h>
#include <ally3d.h>
#include <sysevent.h>
#include <syseventmodel.h>
#include <lcproperties.h>
#include <dbconnection.h>
#include <dbhelper.h>
#include <centerpage.h>
#include <settingsnb.h>
#include <pluginpagefactory.h>
#include <helpdockable.h>
#include <pagestack.h>
#include <tooltable.h>
#include <configacc.h>
#include <configmgr.h>
#include <QTime>
#include <QTimerEvent>
#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QVector3D>
#include <QSqlError>
#include <QMessageBox>
#include <QMainWindow>
#include <occtviewer.h>
#include <LCInter.h>
#include <canonif.h>
#include <statusreader.h>
#include <commandwriter.h>
#include <cassert>
#include <emc.hh>
#include <canonifsettings.h>


GuiCore::GuiCore(QApplication& app, const QString& appName, DBHelper& dbAssist, const QString& groupID)
 : Core(app, appName, dbAssist, groupID) {
  }


GuiCore::GuiCore() {
  assert(kernel);
  }


GuiCore::GuiCore(void* pFromOuterAdressSpace)
 : Core(pFromOuterAdressSpace) {
  }


void GuiCore::activatePage(const QString& pageName) {
  qDebug() << "Core: activate page with name >" << pageName << "<";

  guiCore()->centerView->activatePage(QString("%1Frame").arg(pageName));
  }


bool GuiCore::checkBE() {
  if (checked < 0) {
     bool rv = guiCore()->statusReader->isActive()
            && guiCore()->commandWriter->isActive();

     checked = 1;
     if (!rv) {
        ValueManager vm;

        checked = 0;
        qDebug() << ">>> Kernel::simulateStartOfBE() <<<";

        vm.setValue("taskMode", EMC_TASK_MODE_ENUM::EMC_TASK_MODE_MANUAL);
        vm.setValue("taskState", EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON);
        vm.setValue("allHomed", true);
        vm.setValue("execState", EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_DONE);
        vm.setValue("interpState", EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_IDLE);
        vm.setValue("errorActive", false);
        }
    }
  return checked == 1;
  }


QString GuiCore::curPage() const {
  return guiCore()->centerView->activePage();
  }


GuiKernel* GuiCore::guiCore() {
  return static_cast<GuiKernel*>(kernel);
  }


const GuiKernel* GuiCore::guiCore() const {
  return static_cast<const GuiKernel*>(kernel);
  }


void GuiCore::help4Keyword(const QString &keyWord) {
//  qDebug() << "GuiCore::help4Keyword(" << keyWord << ") NEEDS to get REIMPLEMENTED !!!";
  if (guiCore()->help) {
     guiCore()->help->help4Keyword(keyWord);
     }
  }


bool GuiCore::isLatheMode() const {
  return guiCore()->lcProps->value("DISPLAY", "LATHE").isValid()
      && guiCore()->lcProps->value("DISPLAY", "LATHE").toBool();
  }


bool GuiCore::isSimulator() const {
  return guiCore()->simulator;
  }


LcProperties& GuiCore::lcProperties() {
  return *guiCore()->lcProps;
  }


void GuiCore::parseGCFile(const QString &fileName) {
  QFile gcFile(fileName);

  if (gcFile.exists()) {
     guiCore()->parseGCode(gcFile);
     guiCore()->ally3D->showPath(CanonIF().toolPath());
     }
  }


void GuiCore::setViewStack(PageStack* v) {
  guiCore()->centerView = v;
  }


QMainWindow* GuiCore::mainWindow() {
  return guiCore()->mainWindow;
  }


QList<QString> GuiCore::pluggablePages() {
  return guiCore()->pages.keys();
  }


QList<QString> GuiCore::statusInfos() {
  return guiCore()->statusInfos.keys();
  }


PluginPageInterface* GuiCore::pluggablePage(const QString pageID) {
  if (guiCore()->pages.contains(pageID))
     return guiCore()->pages[pageID];
  return nullptr;
  }


void GuiCore::showHelp() const {
  if (guiCore()->help) guiCore()->help->showHelp();
  }

PluginPageInterface* GuiCore::statusInfo(const QString infoID) {
  if (guiCore()->statusInfos.contains(infoID))
     return guiCore()->statusInfos[infoID];
  return nullptr;
  }


void GuiCore::setMainWindow(QMainWindow *w) {
  PluginPageFactory     ppf;
  AbstractCenterWidget* cw  = ppf.createCenterPage("HelpView");
  HelpView*             hv  = reinterpret_cast<HelpView*>(cw);

  guiCore()->mainWindow = w;
  guiCore()->help       = new HelpDockable(hv, w);
  }


QWidget* GuiCore::stackedPage(const QString& pageName) {
  qDebug() << "Core: query for page: >" << pageName << "<";

  return guiCore()->centerView->page(QString("%1Frame").arg(pageName));
  }


OcctQtViewer* GuiCore::view3D() {
  qDebug() << "GuiCore: kernel is:" << guiCore();
  return guiCore()->view3D;
  }


PageStack* GuiCore::viewStack() {
  return guiCore()->centerView;
  }


void GuiCore::setWindowTitle(const QString &title) {
  if (guiCore()->mainWindow) {
     guiCore()->mainWindow->setWindowTitle(guiCore()->mainWindow->objectName()
                                      + " - "
                                      + title);
     }
  }


CANON_POSITION  GuiCore::toolOffset() const {
  return guiCore()->canonIF->canon.toolOffset;
  }


ToolTable& GuiCore::toolTable() {
  return *guiCore()->tt;
  }


ToolTable* GuiCore::toolTableModel() {
  return guiCore()->tt;
  }


void GuiCore::windowClosing(QCloseEvent *e) {
  guiCore()->windowClosing(e);
  }


void GuiCore::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  kernel->logSysEvent(se);
  QMessageBox::critical(guiCore()->mainWindow
                      , SysEvent::toString(se.type())
                      , se.what());
  }


void GuiCore::beAbortTask() {
  emit guiCore()->abortTask();
  }


void GuiCore::beEnableBlockDelete(bool enable) {
    emit guiCore()->enableBlockDelete(enable);
    }


void GuiCore::beEnableFlood(bool enable) {
    emit guiCore()->enableFlood(enable);
    }


void GuiCore::beEnableMist(bool enable) {
    emit guiCore()->enableMist(enable);
    }


void GuiCore::beEnableOptionalStop(bool enable) {
    if (!checked) return;
    emit guiCore()->enableOptionalStop(enable);
    }


void GuiCore::beSetSpindleOverride(double rate) {
    emit guiCore()->setSpindleOverride(rate);
    }


void GuiCore::beJogStep(int axis, double stepSize, double speed) {
    emit guiCore()->jogStep(axis, stepSize, speed);
    }


void GuiCore::beJogStart(int axis, double speed) {
    emit guiCore()->jogStart(axis, speed);
    }


void GuiCore::beJogStop(int axis) {
    emit guiCore()->jogStop(axis);
    }


void GuiCore::beHomeAxis(int jointNum) {
    emit guiCore()->homeAxis(jointNum);
    }


void GuiCore::beLoadTaskPlan(const QString& gcodeFile) {
    emit guiCore()->loadTaskPlan(gcodeFile);
    }


void GuiCore::beLoadToolTable(const QString& toolTableFile) {
    emit guiCore()->loadToolTable(toolTableFile);
    }


void GuiCore::beSendMDICommand(const QString& command) {
    emit guiCore()->sendMDICommand(command);
    }


void GuiCore::beSetAuto(int autoMode, int line) {
    emit guiCore()->setAuto(autoMode, line);
    }


void GuiCore::beSetFeedOverride(double rate) {
    emit guiCore()->setFeedOverride(rate);
    }


void GuiCore::beSetRapidOverride(double rate) {
    emit guiCore()->setRapidOverride(rate);
    }


void GuiCore::beSetSpindle(bool enable, int speed, int direction) {
    emit guiCore()->setSpindle(enable, speed, direction);
    }


void GuiCore::beSetTaskMode(int mode) {
    emit guiCore()->setTaskMode(mode);
    }


void GuiCore::beSetTaskState(int state) {
    emit guiCore()->setTaskState(state);
    }


void GuiCore::beTaskPlanSynch() {
    emit guiCore()->taskPlanSynch();
    }

#ifdef REDNOSE
Kernel::Kernel(const QString& iniFileName, const QString& appName, const QString& group)
 : cfg(appName, group)
 , lcProps(iniFileName)
 , tt(lcProps, lcProps.toolTableFileName()) // tooltable: file used by linuxcnc NOT the database table
 , lcIF(lcProps, tt)
 , mAxis(lcProps.value("KINS", "KINEMATICS").toString())
 , view3D(nullptr)
 , centerView(nullptr)
 , mainWindow(nullptr)
 , conn(nullptr)
 , ally3D(nullptr)
 , statusReader(positionCalculator, gcodeInfo)
 , commandWriter(new CommandWriter())
 , tmSysEvents(nullptr) {
  if (!mAxis.activeAxis()) mAxis.setup(lcProps.value("TRAJ", "COORDINATES").toString());
  lcIF.setupToolTable();
  tt.setLatheMode(isLatheMode());
  const QString& hf = lcProps.value("HAL", "HALFILE").toString();

  if (hf.contains("sim")) simulator = true;
  }


void Kernel::initialize(DBHelper& dbAssist) {
  CanonIF ci(lcProps, tt);
  // check database before anyone needs it
  QString   dbName = cfg.value("database").toString();
  QFileInfo db(dbName);

  if (!db.exists() || db.size() < 1) {
     if (dbAssist.connect(db.absoluteFilePath())) {
        conn = createDatabase(dbAssist);
        cfg.setValue("database", conn->dbName());
        cfg.setValue("dbType", conn->dbType());
        }
     else throw std::system_error(-2, std::system_category(), "could not create database");
     }
  else {
     dbAssist.connect(db.absoluteFilePath());
     conn = dbAssist.dbConnection();
     if (!conn) throw std::system_error(-2, std::system_category(), "could not access database");
     }
  tmSysEvents = new SysEventModel(*conn, this);
  tmSysEvents->setTable("SysEvents");
  ci.setTraverseColor(cfg.getForeground(Config::GuiElem::RapidMove));
  ci.setFeedColor(cfg.getForeground(Config::GuiElem::WorkMove));
  ci.setLimitsColor(cfg.getForeground(Config::GuiElem::WorkLimit));
  ci.setWorkPieceColor(cfg.getForeground(Config::GuiElem::WorkPiece));
  ci.setCurSegColor(cfg.getForeground(Config::GuiElem::CurSeg));
  ci.setOldSegColor(cfg.getForeground(Config::GuiElem::OldSeg));
  view3D = new OcctQtViewer();
  ally3D.setOcctViewer(view3D);
  mainWindow = new MainWindow(cfg.value("statusInPreview", false).toBool()
                            , cfg.value("previewIsCenter", false).toBool());

  connect(ValueManager().getModel("conePos", QVector3D()), &ValueModel::valueChanged, this, &Kernel::updateView);

  setupBackend();
#ifdef NO_CHECK_OUTPUT
  //  HelpKeywords - in: "3D-Preview" out: "3D-Vorschau"
  //  HelpKeywords - in: "3D Preview" out: "3D Preview"
  //  HelpKeywords - in: "FileManager" out: "Datei-Verwalter"
  //  HelpKeywords - in: "FixtureManager" out: "Koordinaten-Systeme"
  //  HelpKeywords - in: "FixtureEditorForm" out: "FixtureEditorForm"
  //  HelpKeywords - in: "JogView" out: "Handbetrieb"
  //  HelpKeywords - in: "LCToolTable" out: "LinuxCNC Werkzeuge"
  //  HelpKeywords - in: "MDIEditor" out: "manuelle Befehle"
  //  HelpKeywords - in: "PathEditor" out: "aktive NC-Datei"
  //  HelpKeywords - in: "PathEditorForm" out: "PathEditorForm"
  //  HelpKeywords - in: "PreferencesEditor" out: "PreferencesEditor"
  //  HelpKeywords - in: "SettingsNotebook" out: "SettingsNotebook"
  //  HelpKeywords - in: "TestEdit" out: "freie NC-Datei"
  //  HelpKeywords - in: "ToolEditor" out: "Werkzeug-Eigenschaften"
  //  HelpKeywords - in: "ToolManager" out: "ToolManager"

  // checks after everything is initialized ...
  // output should be:

//  CenterView contains 8  pages
//  MainView holds page >> "3D PreviewFrame"
//  MainView holds page >> "FileManagerFrame"
//  MainView holds page >> "JogViewFrame"
//  MainView holds page >> "MDIEditorFrame"
//  MainView holds page >> "PathEditorFrame"
//  MainView holds page >> "SettingsNotebookFrame"
//  MainView holds page >> "SysEventViewFrame"
//  MainView holds page >> "TestEditFrame"
  centerView->dump();

  //  SN: page found -> "ToolManager" with title "ToolManager"
  //  SN: page found -> "FixtureManager" with title "FixtureManager"
  //  SN: page found -> "PreferencesEditor" with title "PreferencesEditor"
  //  SN: page found -> "LCToolTable" with title "LCToolTable"
  mainWindow->settingsNotebook()->dump();

  checkTools();
#endif
  }


Kernel::~Kernel() {
  }


void Kernel::checkTools() {
  int              mx = tt.entries();
  const ToolEntry* te;

  for (int i=0; i < mx; ++i) {
      qDebug() << "\t<<< check tool entry #" << i << " <<<";
      te = tt.tool4Slot(i);

      if (te) te->dump();
      else {
         qDebug() << "NO TOOL with num #" << i;
         }
      }
  }


void Kernel::setupBackend() {
  if (statusReader.isActive()) {
     qDebug() << "Well, we have an active status reader ... ;)";
     timer.start(40, this);
     }
  if (commandWriter->isActive()) {
     qDebug() << "OK, ok, ok - backend seems to be available!";
     commandWriter->moveToThread(&backendCommThread);
     connect(&backendCommThread, &QThread::finished, &backendCommThread, &QObject::deleteLater);

     connect(this, &Kernel::abortTask, commandWriter, &CommandWriter::abortTask);
     connect(this, &Kernel::enableBlockDelete, commandWriter, &CommandWriter::enableBlockDelete);
     connect(this, &Kernel::enableFlood, commandWriter, &CommandWriter::enableFlood);
     connect(this, &Kernel::enableMist, commandWriter, &CommandWriter::enableMist);
     connect(this, &Kernel::enableOptionalStop, commandWriter, &CommandWriter::enableOptionalStop);
     connect(this, &Kernel::setSpindleOverride, commandWriter, &CommandWriter::setSpindleOverride);
     connect(this, &Kernel::jogStep, commandWriter, &CommandWriter::jogStep);
     connect(this, &Kernel::jogStart, commandWriter, &CommandWriter::jogStart);
     connect(this, &Kernel::jogStop, commandWriter, &CommandWriter::jogStop);
     connect(this, &Kernel::homeAxis, commandWriter, &CommandWriter::homeAxis);
     connect(this, &Kernel::loadTaskPlan, commandWriter, &CommandWriter::loadTaskPlan);
     connect(this, &Kernel::loadToolTable, commandWriter, &CommandWriter::loadToolTable);
     connect(this, &Kernel::sendMDICommand, commandWriter, &CommandWriter::sendMDICommand);
     connect(this, &Kernel::setAuto, commandWriter, &CommandWriter::setAuto);
     connect(this, &Kernel::setFeedOverride, commandWriter, &CommandWriter::setFeedOverride);
     connect(this, &Kernel::setRapidOverride, commandWriter, &CommandWriter::setRapidOverride);
     connect(this, &Kernel::setSpindle, commandWriter, &CommandWriter::setSpindle);
     connect(this, &Kernel::setTaskMode, commandWriter, &CommandWriter::setTaskMode);
     connect(this, &Kernel::setTaskState, commandWriter, &CommandWriter::setTaskState);
     connect(this, &Kernel::taskPlanSynch, commandWriter, &CommandWriter::taskPlanSynch);

     connect(commandWriter, &CommandWriter::systemEvent, this, &Kernel::logSysEvent);
     backendCommThread.start();
     }
  else {
     qDebug() << "Bad luck this time. Sorry but no backend!";
     connect(this, &Kernel::abortTask, this, &Kernel::nop);
     connect(this, &Kernel::enableBlockDelete, this, &Kernel::nop);
     connect(this, &Kernel::enableFlood, this, &Kernel::nop);
     connect(this, &Kernel::enableMist, this, &Kernel::nop);
     connect(this, &Kernel::enableOptionalStop, this, &Kernel::nop);
     connect(this, &Kernel::setSpindleOverride, this, &Kernel::nop);
     connect(this, &Kernel::jogStep, this, &Kernel::nop);
     connect(this, &Kernel::jogStart, this, &Kernel::nop);
     connect(this, &Kernel::jogStop, this, &Kernel::nop);
     connect(this, &Kernel::homeAxis, this, &Kernel::nop);
     connect(this, &Kernel::loadTaskPlan, this, &Kernel::nop);
     connect(this, &Kernel::loadToolTable, this, &Kernel::nop);
     connect(this, &Kernel::sendMDICommand, this, &Kernel::nop);
     connect(this, &Kernel::setAuto, this, &Kernel::nop);
     connect(this, &Kernel::setFeedOverride, this, &Kernel::nop);
     connect(this, &Kernel::setRapidOverride, this, &Kernel::nop);
     connect(this, &Kernel::setSpindle, this, &Kernel::nop);
     connect(this, &Kernel::setTaskMode, this, &Kernel::nop);
     connect(this, &Kernel::setTaskState, this, &Kernel::nop);
     connect(this, &Kernel::taskPlanSynch, this, &Kernel::nop);
     }
  }


void Kernel::nop() {
  qDebug() << "backend not available!";
  }


DBConnection* Kernel::createDatabase(DBHelper &dbAssist) {
  DBConnection* conn = dbAssist.createDatabase(dbAssist.dbConnection()->dbName());

  dbAssist.createSampleData(*conn);

  return conn;
  }


void Kernel::logSysEvent(const SysEvent& se) {
  qDebug() << "system event" << se.type() << ":" << se.what() << " at:" << se.when();
  tmSysEvents->append(&se);
  }


void Kernel::updateView(const QVariant &v) {
  QVector3D p = v.value<QVector3D>();

  ally3D.moveCone(p.x(), p.y(), p.z());
  }


bool Kernel::isLatheMode() const {
  return lcProps.value("DISPLAY", "LATHE").isValid()
      && lcProps.value("DISPLAY", "LATHE").toBool();
  }


void Kernel::parseGCode(QFile &file) {
  QTime start = QTime::currentTime();

  lcIF.parseInline(file.fileName());

  QTime end  = QTime::currentTime();
  long delta = end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay();

  qDebug() << "parsing of " << file.fileName() << " took: " << delta << "ms";
  }


void Kernel::windowClosing(QCloseEvent *e) {
  // application is going to shut down ...
  cfg.settings.beginGroup("MainWindow");
  cfg.setValue("geometry",    mainWindow->saveGeometry());
  cfg.setValue("windowState", mainWindow->saveState());
  cfg.settings.endGroup();
  centerView->windowClosing(e);
  }


void Kernel::timerEvent(QTimerEvent *e) {
  if (e->timerId() == timer.timerId()) {
     try {
         statusReader.update();
         }
     catch (SysEvent* e) {
         ValueManager().setValue("errorActive", true);
         tmSysEvents->append(e);
         QMessageBox::critical(nullptr
                             , SysEvent::toString(e->type())
                             , e->what());
         }
     }
  else QObject::timerEvent(e);
  }

Kernel* Core::kernel  = nullptr;
int     Core::checked = -1;
#endif
