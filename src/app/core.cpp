#include <core.h>
#include <core_p.h>
#include <QTime>
#include <QTimerEvent>
#include <QString>
#include <QVector3D>
#include <QSqlError>
#include <core.h>
#include <lcproperties.h>
#include <dbconnection.h>
#include <dbhelper.h>
#include <mainwindow.h>
#include <tooltable.h>
#include <LCInter.h>
#include <canonif.h>
#include <configacc.h>
#include <configmgr.h>
#include <commandwriter.h>
#include <occtviewer.h>
#include <cassert>
#include <emc.hh>


Core::Core(const QString& iniFileName, const QString& appName, DBHelper& dbAssist, const QString& group) {
  if (!kernel)
     kernel = new Kernel(iniFileName, appName, group, dbAssist);
  }


void Core::parseGCFile(const QString &fileName) {
  QFile gcFile(fileName);

  if (gcFile.exists()) {
     core()->parseGCode(gcFile);
     core()->ally3D.showPath(CanonIF().toolPath());
     }
  }


LcProperties& Core::lcProperties() {
  return core()->lcProps;
  }


OcctQtViewer* Core::view3D() {
  return core()->view3D;
  }


DBConnection* Core::databaseConnection() {
  return core()->conn;
  }


void Core::setViewStack(MainView* v) {
  core()->mainView = v;
  }


void Core::setMainWindow(MainWindow* mw) {
  core()->mainWindow = mw;
  }


void Core::setAppMode(ApplicationMode m) {
  core()->mainWindow->setAppMode(m);
  }


void Core::showAllButCenter(bool visible) {
  ValueManager().setValue("showAllButCenter", visible);
  }


QWidget* Core::stackedPage(const QString& pageName) {
  qDebug() << "Core: query for page: >" << pageName << "<";

  return core()->mainView->page(pageName);
  }


bool Core::checkBE() {
  if (checked < 0) {
     bool rv = core()->statusReader.isActive()
            && core()->commandWriter->isActive();

     checked = 1;
     if (!rv) {
        ValueManager vm;

        checked = 0;
        qDebug() << ">>> Kernel::simulateStartOfBE() <<<";

        vm.setValue("taskMode", EMC_TASK_MODE_ENUM::EMC_TASK_MODE_MANUAL);
        vm.setValue("allHomed", true);
        vm.setValue("execState", EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_DONE);
        vm.setValue("interpState", EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_IDLE);
        }
    }
  return checked == 1;
  }


void Core::activatePage(const QString& pageName) {
  qDebug() << "Core: activate page with name >" << pageName << "<";

  auto page = core()->mainView->activatePage(pageName);
  if (page)
     core()->mainWindow->setWindowTitle(core()->mainWindow->objectName()
                                     + " - "
                                     +  page->objectName());
  }


const AxisMask& Core::axisMask() const {
  return core()->mAxis;
  }


ToolTable& Core::toolTable() {
  return core()->tt;
  }


const QString& Core::curPage() const {
  return core()->mainView->activePage();
  }


ToolTable* Core::toolTableModel() {
  return &core()->tt;
  }


void Core::windowClosing(QCloseEvent *e) {
  core()->windowClosing(e);
  }


Kernel* Core::core() {
  assert(kernel != nullptr);
  return kernel;
  }


const Kernel* Core::core() const {
  assert(kernel != nullptr);
  return kernel;
  }


void Core::beAbortTask() {
  emit core()->abortTask();
  }


void Core::beEnableBlockDelete(bool enable) {
    emit core()->enableBlockDelete(enable);
    }


void Core::beEnableFlood(bool enable) {
    emit core()->enableFlood(enable);
    }


void Core::beEnableMist(bool enable) {
    emit core()->enableMist(enable);
    }


void Core::beEnableOptionalStop(bool enable) {
    if (!checked) return;
    emit core()->enableOptionalStop(enable);
    }


void Core::beEnableSpindleOverride(double rate) {
    emit core()->enableSpindleOverride(rate);
    }


void Core::beJogStep(int axis, double stepSize, double speed) {
    emit core()->jogStep(axis, stepSize, speed);
    }


void Core::beJogStart(int axis, double speed) {
    emit core()->jogStart(axis, speed);
    }


void Core::beJogStop(int axis) {
    emit core()->jogStop(axis);
    }


void Core::beHomeAxis(int jointNum) {
    emit core()->homeAxis(jointNum);
    }


void Core::beLoadTaskPlan(const QString& gcodeFile) {
    emit core()->loadTaskPlan(gcodeFile);
    }


void Core::beLoadToolTable(const QString& toolTableFile) {
    emit core()->loadToolTable(toolTableFile);
    }


void Core::beSendMDICommand(const QString& command) {
    emit core()->sendMDICommand(command);
    }


void Core::beSetAuto(int autoMode, int line) {
    emit core()->setAuto(autoMode, line);
    }


void Core::beSetFeedOverride(double rate) {
    emit core()->setFeedOverride(rate);
    }


void Core::beSetRapidOverride(double rate) {
    emit core()->setRapidOverride(rate);
    }


void Core::beSetSpindle(bool enable, int speed, int direction) {
    emit core()->setSpindle(enable, speed, direction);
    }


void Core::beSetTaskMode(int mode) {
    emit core()->setTaskMode(mode);
    }


void Core::beSetTaskState(int state) {
    emit core()->setTaskState(state);
    }


void Core::beTaskPlanSynch() {
    emit core()->taskPlanSynch();
    }


Kernel::Kernel(const QString& iniFileName, const QString& appName, const QString& group, DBHelper& dbAssist)
 : cfg(appName, group)
 , lcProps(iniFileName)
 , tt(lcProps.toolTableFileName()) // tooltable: file used by linuxcnc NOT the database table
 , lcIF(lcProps, tt)
 , mAxis(lcProps.value("KINS", "KINEMATICS").toString())
 , view3D(new OcctQtViewer())
 , mainView(nullptr)
 , mainWindow(nullptr)
 , conn(nullptr)
 , ally3D(view3D)
 , statusReader(positionCalculator, gcodeInfo)
 , commandWriter(new CommandWriter()) {
  CanonIF ci(lcProps, tt);

  if (!mAxis.activeAxis()) mAxis.setup(lcProps.value("TRAJ", "COORDINATES").toString());
  lcIF.setupToolTable();

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
  ci.setTraverseColor(cfg.getForeground(Config::GuiElem::RapidMove));
  ci.setFeedColor(cfg.getForeground(Config::GuiElem::WorkMove));
  ci.setLimitsColor(cfg.getForeground(Config::GuiElem::WorkLimit));
  ci.setWorkPieceColor(cfg.getForeground(Config::GuiElem::WorkPiece));
  ci.setCurSegColor(cfg.getForeground(Config::GuiElem::CurSeg));
  ci.setOldSegColor(cfg.getForeground(Config::GuiElem::OldSeg));

  connect(ValueManager().getModel("conePos", QVector3D()), &ValueModel::valueChanged, this, &Kernel::updateView);

  setupBackend();
  }


Kernel::~Kernel() {
  }


void Kernel::checkTools() {
  int              mx = tt.entries();
  const ToolEntry* te;

  for (int i=0; i < mx; ++i) {
      qDebug() << "\t<<< check tool num #" << i << " <<<";
      te = tt.tool(i);

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
     connect(this, &Kernel::enableSpindleOverride, commandWriter, &CommandWriter::enableSpindleOverride);
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
     backendCommThread.start();
     }
  else {
     qDebug() << "Bad luck this time. Sorry but no backend!";
     connect(this, &Kernel::abortTask, this, &Kernel::nop);
     connect(this, &Kernel::enableBlockDelete, this, &Kernel::nop);
     connect(this, &Kernel::enableFlood, this, &Kernel::nop);
     connect(this, &Kernel::enableMist, this, &Kernel::nop);
     connect(this, &Kernel::enableOptionalStop, this, &Kernel::nop);
     connect(this, &Kernel::enableSpindleOverride, this, &Kernel::nop);
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


void Kernel::updateView(const QVariant &v) {
  QVector3D p = v.value<QVector3D>();

  ally3D.moveCone(p.x(), p.y(), p.z());
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
  cfg.setValue("geometry", mainWindow->saveGeometry());
  cfg.setValue("windowState", mainWindow->saveState());
  cfg.settings.endGroup();
  mainView->windowClosing(e);
  }


void Kernel::timerEvent(QTimerEvent *e) {
  if (e->timerId() == timer.timerId()) statusReader.update();
  else QObject::timerEvent(e);
  }

Kernel* Core::kernel  = nullptr;
int     Core::checked = -1;
