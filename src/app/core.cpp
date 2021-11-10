#include <core.h>
#include <core_p.h>
#include <QTime>
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
#include <configmgr.h>
#include <occtviewer.h>
#include <cassert>


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


bool Core::isBackendActive() const {
  return core()->statusReader.isActive();
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


void Core::showAllButCenter(bool visible) {
  core()->mainWindow->showAllButCenter(visible);
  }


QWidget* Core::stackedPage(const QString& pageName) {
  qDebug() << "Core: query for page: >" << pageName << "<";

  return core()->mainView->page(pageName);
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


ToolTable* Core::toolTableModel() {
  return &core()->tt;
  }


Kernel* Core::core() {
  assert(kernel != nullptr);
  return kernel;
  }


const Kernel* Core::core() const {
  assert(kernel != nullptr);
  return kernel;
  }


Kernel::Kernel(const QString& iniFileName, const QString& appName, const QString& group, DBHelper& dbAssist)
 : cfg(appName, group)
 , lcProps(iniFileName)
 , tt(lcProps.toolTableFileName()) // tooltable: file used by linuxcnc NOT the database table
 , lcIF(lcProps, tt)
 , mAxis(lcProps.value("KINS", "KINEMATICS").toString())
 , view3D(new OcctQtViewer())
 , conn(nullptr)
 , ally3D(view3D)
 , statusReader(positionCalculator, gcodeInfo) {
  CanonIF ci(lcProps, tt);
  ValueManager().setValue("conePos", QVector3D());

//  lcProps.dump();
  if (!mAxis.activeAxis()) mAxis.setup(lcProps.value("TRAJ", "COORDINATES").toString());

//  mAxis.dump();
  lcIF.setupToolTable();

  // check database before anyone needs it
  QFileInfo db(dbAssist.dbConnection()->dbName());

  if (!db.exists() || db.size() < 1) {
     conn = createDatabase(dbAssist);
     cfg.setValue("database", conn->dbName());
     cfg.setValue("dbType", conn->dbType());
     }
  if (!conn->connect()) throw std::system_error(-2, std::system_category(), "no database");
  ci.setTraverseColor(QColor(Qt::cyan));
  ci.setFeedColor(QColor(Qt::white));
  ci.setLimitsColor(QColor(150, 255, 150));
  connect(ValueManager().getModel("conePos"), &ValueModel::valueChanged, this, &Kernel::updateView);  

  if (statusReader.isActive()) timer.start(40, this);
  }


Kernel::~Kernel() {
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


void Kernel::timerEvent(QTimerEvent *e) {
  if (e->timerId() == timer.timerId()) statusReader.update();
  else QObject::timerEvent(e);
  }

Kernel* Core::kernel = nullptr;
