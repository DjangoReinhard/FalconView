#include <guikernel.h>
#include <dbhelper.h>
#include <dbconnection.h>
#include <configacc.h>
#include <ally3d.h>
#include <canonif.h>
#include <occtviewer.h>
#include <centerview.h>
#include <mainwindow.h>
#include <statusreader.h>
#include <commandwriter.h>
#include <syseventmodel.h>
#include <QApplication>
#include <QMessageBox>
#include <QFileInfo>
#include <QVector3D>


GuiKernel::GuiKernel(const QString& fileName, const QString& appName, const QString& groupID)
 : Kernel(fileName, appName, groupID)
 , lcProps(fileName)
 , tt(lcProps, lcProps.toolTableFileName())
 , lcIF(lcProps, tt)
 , mAxis(lcProps.value("KINS", "KINEMATICS").toString())
 , view3D(nullptr)
 , centerView(nullptr)
 , mainWindow(nullptr)
 , ally3D(nullptr)
 , statusReader(nullptr)
 , commandWriter(nullptr)
 , sysEvents(nullptr) {
  if (!mAxis.activeAxis()) mAxis.setup(lcProps.value("TRAJ", "COORDINATES").toString());
  lcIF.setupToolTable();
  tt.setLatheMode(isLatheMode());
  const QString& hf = lcProps.value("HAL", "HALFILE").toString();

  if (hf.contains("sim")) simulator = true;
  }


int GuiKernel::axisMask() const {
  return mAxis.mask();
  }


DBConnection* GuiKernel::createDatabase(DBHelper& dbAssist) {
  DBConnection* conn = dbAssist.createDatabase(dbAssist.dbConnection()->dbName());

  dbAssist.createSampleData(*conn);

  return conn;
  }


QString GuiKernel::fileName4(const QString &fileID) {
  if (fileID == "database") {
     return conn->dbName();
     }
  else if (fileID == "toolTable") {
     return lcProps.toolTableFileName();
     }
  return Kernel::fileName4(fileID);
  }


void GuiKernel::initialize(DBHelper &dbAssist) {
  CanonIF ci(lcProps, tt);
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
  sysEvents = new SysEventModel(*conn, this);
  sysEvents->setTable("SysEvents");
  ci.setTraverseColor(cfg.getForeground(Config::GuiElem::RapidMove));
  ci.setFeedColor(cfg.getForeground(Config::GuiElem::WorkMove));
  ci.setLimitsColor(cfg.getForeground(Config::GuiElem::WorkLimit));
  ci.setWorkPieceColor(cfg.getForeground(Config::GuiElem::WorkPiece));
  ci.setCurSegColor(cfg.getForeground(Config::GuiElem::CurSeg));
  ci.setOldSegColor(cfg.getForeground(Config::GuiElem::OldSeg));
  view3D = new OcctQtViewer();
  ally3D->setOcctViewer(view3D);
  mainWindow = new MainWindow(cfg.value("statusInPreview", false).toBool()
                            , cfg.value("previewIsCenter", false).toBool());

  connect(ValueManager().getModel("conePos", QVector3D()), &ValueModel::valueChanged
        , this, &GuiKernel::updateView);
  setupBackend();
  }


bool GuiKernel::isLatheMode() const {
  return lcProps.value("DISPLAY", "LATHE").isValid()
      && lcProps.value("DISPLAY", "LATHE").toBool();
  }


void GuiKernel::nop() const {
  }


void GuiKernel::parseGCode(QFile &file) {
  QTime start = QTime::currentTime();

  lcIF.parseInline(file.fileName());

  QTime end  = QTime::currentTime();
  long delta = end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay();

  qDebug() << "parsing of " << file.fileName() << " took: " << delta << "ms";
  }


void GuiKernel::setupBackend() {
  if (statusReader->isActive()) {
     qDebug() << "Well, we have an active status reader ... ;)";
     timer.start(40, this);
     }
  if (commandWriter->isActive()) {
     qDebug() << "OK, ok, ok - backend seems to be available!";
     commandWriter->moveToThread(&backendCommThread);
     connect(&backendCommThread, &QThread::finished, &backendCommThread, &QObject::deleteLater);

     connect(this, &GuiKernel::abortTask, commandWriter, &CommandWriter::abortTask);
     connect(this, &GuiKernel::enableBlockDelete, commandWriter, &CommandWriter::enableBlockDelete);
     connect(this, &GuiKernel::enableFlood, commandWriter, &CommandWriter::enableFlood);
     connect(this, &GuiKernel::enableMist, commandWriter, &CommandWriter::enableMist);
     connect(this, &GuiKernel::enableOptionalStop, commandWriter, &CommandWriter::enableOptionalStop);
     connect(this, &GuiKernel::setSpindleOverride, commandWriter, &CommandWriter::setSpindleOverride);
     connect(this, &GuiKernel::jogStep, commandWriter, &CommandWriter::jogStep);
     connect(this, &GuiKernel::jogStart, commandWriter, &CommandWriter::jogStart);
     connect(this, &GuiKernel::jogStop, commandWriter, &CommandWriter::jogStop);
     connect(this, &GuiKernel::homeAxis, commandWriter, &CommandWriter::homeAxis);
     connect(this, &GuiKernel::loadTaskPlan, commandWriter, &CommandWriter::loadTaskPlan);
     connect(this, &GuiKernel::loadToolTable, commandWriter, &CommandWriter::loadToolTable);
     connect(this, &GuiKernel::sendMDICommand, commandWriter, &CommandWriter::sendMDICommand);
     connect(this, &GuiKernel::setAuto, commandWriter, &CommandWriter::setAuto);
     connect(this, &GuiKernel::setFeedOverride, commandWriter, &CommandWriter::setFeedOverride);
     connect(this, &GuiKernel::setRapidOverride, commandWriter, &CommandWriter::setRapidOverride);
     connect(this, &GuiKernel::setSpindle, commandWriter, &CommandWriter::setSpindle);
     connect(this, &GuiKernel::setTaskMode, commandWriter, &CommandWriter::setTaskMode);
     connect(this, &GuiKernel::setTaskState, commandWriter, &CommandWriter::setTaskState);
     connect(this, &GuiKernel::taskPlanSynch, commandWriter, &CommandWriter::taskPlanSynch);

     connect(commandWriter, SIGNAL(systemEvent(const SysEvent&)), this, SLOT(riseError(const SysEvent&)));
     backendCommThread.start();
     }
  else {
     qDebug() << "Bad luck this time. Sorry but no backend!";
     connect(this, &GuiKernel::abortTask, this, &GuiKernel::nop);
     connect(this, &GuiKernel::enableBlockDelete, this, &GuiKernel::nop);
     connect(this, &GuiKernel::enableFlood, this, &GuiKernel::nop);
     connect(this, &GuiKernel::enableMist, this, &GuiKernel::nop);
     connect(this, &GuiKernel::enableOptionalStop, this, &GuiKernel::nop);
     connect(this, &GuiKernel::setSpindleOverride, this, &GuiKernel::nop);
     connect(this, &GuiKernel::jogStep, this, &GuiKernel::nop);
     connect(this, &GuiKernel::jogStart, this, &GuiKernel::nop);
     connect(this, &GuiKernel::jogStop, this, &GuiKernel::nop);
     connect(this, &GuiKernel::homeAxis, this, &GuiKernel::nop);
     connect(this, &GuiKernel::loadTaskPlan, this, &GuiKernel::nop);
     connect(this, &GuiKernel::loadToolTable, this, &GuiKernel::nop);
     connect(this, &GuiKernel::sendMDICommand, this, &GuiKernel::nop);
     connect(this, &GuiKernel::setAuto, this, &GuiKernel::nop);
     connect(this, &GuiKernel::setFeedOverride, this, &GuiKernel::nop);
     connect(this, &GuiKernel::setRapidOverride, this, &GuiKernel::nop);
     connect(this, &GuiKernel::setSpindle, this, &GuiKernel::nop);
     connect(this, &GuiKernel::setTaskMode, this, &GuiKernel::nop);
     connect(this, &GuiKernel::setTaskState, this, &GuiKernel::nop);
     connect(this, &GuiKernel::taskPlanSynch, this, &GuiKernel::nop);
     }
  }


void GuiKernel::timerEvent(QTimerEvent *e) {
  if (e->timerId() == timer.timerId()) {
     try {
         statusReader->update();
         }
     catch (SysEvent* e) {
         ValueManager().setValue("errorActive", true);
         sysEvents->append(e);
         QMessageBox::critical(nullptr
                             , SysEvent::toString(e->type())
                             , e->what());
         }
     }
  else QObject::timerEvent(e);
  }


void GuiKernel::updateView(const QVariant &v) {
  QVector3D p = v.value<QVector3D>();

  ally3D->moveCone(p.x(), p.y(), p.z());
  }


void GuiKernel::windowClosing(QCloseEvent *e) {
  // application is going to shut down ...
  cfg.settings.beginGroup("MainWindow");
  cfg.setValue("geometry",    mainWindow->saveGeometry());
  cfg.setValue("windowState", mainWindow->saveState());
  cfg.settings.endGroup();
  centerView->windowClosing(e);
  }
