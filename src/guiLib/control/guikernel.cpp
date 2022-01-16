#include <guikernel.h>
#include <dbhelper.h>
#include <dbconnection.h>
#include <configacc.h>
#include <pagestack.h>
#include <canonif.h>
#include <tooltable.h>
#include <axismask.h>
#include <lcproperties.h>
#include <LCInter.h>
#include <statusreader.h>
#include <commandwriter.h>
#include <syseventmodel.h>
#include <ally3d.h>

#include <QApplication>
#include <QMainWindow>
#include <QMessageBox>
#include <QPluginLoader>
#include <QFile>
#include <QFileInfo>
#include <QVector3D>

#include <occtviewer.h>


GuiKernel::GuiKernel(QApplication& app, const QString& appName, const QString& groupID)
 : Kernel(app, appName, groupID)
 , lcProps(nullptr)
 , tt(nullptr)
 , lcIF(nullptr)
 , mAxis(nullptr)
 , view3D(nullptr)
 , centerView(nullptr)
 , mainWindow(nullptr)
 , ally3D(new Ally3D())
 , statusReader(nullptr)
 , commandWriter(nullptr)
 , sysEvents(nullptr) {
  }


int GuiKernel::axisMask() const {
  return mAxis->mask();
  }


DBConnection* GuiKernel::createDatabase(DBHelper& dbAssist) {
  DBConnection* conn = dbAssist.createDatabase(dbAssist.dbConnection()->dbName());

  dbAssist.createSampleData(*conn);

  return conn;
  }


QString GuiKernel::fileName4(const QString &fileID) const {
  if (fileID == "database") {
     qDebug() << "GK::fileName4(" << fileID << ") => " << conn->dbName();
     return conn->dbName();
     }
  else if (fileID == "ini") {
     qDebug() << "GK::fileName4(" << fileID << ") => " << iniFileName;
     return iniFileName;
     }
  else if (fileID == "i18n") {
     qDebug() << "GK::fileName4(" << fileID << ") => " << langDir;
     return langDir;
     }
  else if (fileID == "plugins") {
     qDebug() << "GK::fileName4(" << fileID << ") => " << pluginDir;
     return pluginDir;
     }
  else if (fileID == "helpFile") {
     qDebug() << "GK::fileName4(" << fileID << ") => " << helpFileName;
     return helpFileName;
     }
  else if (fileID == "toolTable") {
     qDebug() << "GK::fileName4(" << fileID << ") => " << lcProps->toolTableFileName();
     return lcProps->toolTableFileName();
     }
  return Kernel::fileName4(fileID);
  }


void GuiKernel::initialize(DBHelper &dbAssist) {
  QDir dir(QCoreApplication::applicationDirPath());

  dir.cd("plugins");
  pluginDir = dir.absolutePath();
  dir.cd("..");
  dir.cd("help");
  helpFileName = dir.absolutePath() + "/FalconView.qzh";
  dir.cd("..");
  dir.cd("i18n");
  langDir = dir.absolutePath();
  Kernel::initialize(dbAssist);
  /** ==================================================== */
  lcProps = new LcProperties(fileName4("ini"));
  tt = new ToolTable(*lcProps, lcProps->toolTableFileName());
  canonIF = new CanonIF(*lcProps, *tt);
  lcIF = new LCInterface(*canonIF, *lcProps, *tt); /* create linuxcnc interpreter */
  mAxis = new AxisMask(lcProps->value("KINS", "KINEMATICS").toString());
  if (!mAxis->activeAxis()) mAxis->setup(lcProps->value("TRAJ", "COORDINATES").toString());
  lcIF->setupToolTable();
  tt->setLatheMode(isLatheMode());
  /** ==================================================== */

  QString   dbName = cfg->value("database").toString();
  QFileInfo db(dbName);
  const QString& hf = lcProps->value("HAL", "HALFILE").toString();

  if (hf.contains("sim")) simulator = true;
  if (!db.exists() || db.size() < 1) {
     if (dbAssist.connect(db.absoluteFilePath())) {
        conn = createDatabase(dbAssist);
        cfg->setValue("database", conn->dbName());
        cfg->setValue("dbType", conn->dbType());
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

  //TODO: convert to values
//  canonIF->setTraverseColor(cfg->getForeground(Config::GuiElem::RapidMove));
//  canonIF->setFeedColor(cfg->getForeground(Config::GuiElem::WorkMove));
//  canonIF->setLimitsColor(cfg->getForeground(Config::GuiElem::WorkLimit));
//  canonIF->setWorkPieceColor(cfg->getForeground(Config::GuiElem::WorkPiece));
//  canonIF->setCurSegColor(cfg->getForeground(Config::GuiElem::CurSeg));
//  canonIF->setOldSegColor(cfg->getForeground(Config::GuiElem::OldSeg));

  ally3D->setTraverseColor(cfg->getForeground(Config::GuiElem::RapidMove));
  ally3D->setFeedColor(cfg->getForeground(Config::GuiElem::WorkMove));
  ally3D->setLimitsColor(cfg->getForeground(Config::GuiElem::WorkLimit));
  ally3D->setWorkPieceColor(cfg->getForeground(Config::GuiElem::WorkPiece));
  ally3D->setCurSegColor(cfg->getForeground(Config::GuiElem::CurSeg));
  ally3D->setOldSegColor(cfg->getForeground(Config::GuiElem::OldSeg));
  view3D = new OcctQtViewer();
  ally3D->setOcctViewer(view3D);

  /** ==================================================== */
  statusReader  = new StatusReader(positionCalculator, gcodeInfo);
  commandWriter = new CommandWriter();
  /** ==================================================== */

  QDir pluginsDir(fileName4("plugins"));
  const auto entryList = pluginsDir.entryList(QDir::Files);

  for (const QString& fileName : entryList) {
      QString path = pluginsDir.absoluteFilePath(fileName);

      if (fileName.startsWith("libsi")) {
         QPluginLoader loader(path);
         QObject*      plugin = loader.instance();
         QString       name   = fileName.mid(5, fileName.size() - 8);

         if (plugin) {
            auto iPlugin = qobject_cast<PluginPageInterface*>(plugin);

            qDebug() << name << "is status info panel";
            statusInfos[name] = iPlugin;
            }
         else qDebug() << fileName << "NOT a valid plugin: " << loader.errorString();
         }
      else if (fileName.startsWith("libpp")) {
         QPluginLoader loader(path);

         QObject*      plugin = loader.instance();
         QString       name = fileName.mid(5, fileName.size() - 8);

         if (plugin) {
            auto iPlugin = qobject_cast<PluginPageInterface*>(plugin);

            qDebug() << name << "is pluggable center page";
            mainPages[name] = iPlugin;
            }
         else qDebug() << fileName << "is NOT a valid plugin:\t" << loader.errorString();
         }
      else if (fileName.startsWith("libnb")) {
         QPluginLoader loader(path);

         QObject*      plugin = loader.instance();
         QString       name = fileName.mid(5, fileName.size() - 8);

         if (plugin) {
            auto iPlugin = qobject_cast<PluginPageInterface*>(plugin);

            qDebug() << name << "is pluggable notebook page";
            nbPages[name] = iPlugin;
            }
         else qDebug() << fileName << "is NOT a valid plugin:\t" << loader.errorString();
         }
      }
  connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged
        , this, &GuiKernel::processGCodeFile);
  connect(ValueManager().getModel("conePos", QVector3D()), &ValueModel::valueChanged
        , this, &GuiKernel::updateView);  
  setupBackend();
  }


bool GuiKernel::isLatheMode() const {
  return lcProps->value("DISPLAY", "LATHE").isValid()
      && lcProps->value("DISPLAY", "LATHE").toBool();
  }


void GuiKernel::logSysEvent(const QString& msg) {
  SysEvent se(msg);

  qDebug() << "system event" << se.type() << ":" << se.what() << " at:" << se.when();
  sysEvents->append(&se);
  }


void GuiKernel::logSysEvent(const SysEvent& se) {
  qDebug() << "system event" << se.type() << ":" << se.what() << " at:" << se.when();
  sysEvents->append(&se);
  }


void GuiKernel::nop() const {
  }


void GuiKernel::processGCodeFile(const QVariant& fileName) {
  QTime start = QTime::currentTime();
  QFile gcFile(fileName.toString());

  if (!gcFile.exists()) return;
  lcIF->parseInline(gcFile.fileName());

  QTime end  = QTime::currentTime();
  long delta = end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay();

  qDebug() << "parsing of " << gcFile.fileName() << " took: " << delta << "ms";

  ally3D->showPath(canonIF->toolPath());
  QTime fin = QTime::currentTime();

  delta = fin.msecsSinceStartOfDay() - end.msecsSinceStartOfDay();
  qDebug() << "display of " << gcFile.fileName() << " took: " << delta << "ms";
  }


void GuiKernel::processAppArgs(const QStringList &args) {
  int mx = args.size();

  if (mx < 2) usage();
  for (int i=0; i < mx; ++i) {
      if (args[i] == "-ini" && mx > (i+1)) {
         iniFileName = args[++i];
         }
      else if (args[i] == "-help" && mx > (i+1)) {
         helpFileName = args[++i];
         }
      else if (args[i] == "-i18n" && mx > (i+1)) {
         langDir = args[++i];
         }
      else if (args[i] == "-plugins" && mx > (i+1)) {
         pluginDir = args[++i];
         }
      }
  QFileInfo iniFI(iniFileName);

  if (!iniFI.exists()) usage();
  }


void GuiKernel::setupBackend() {
  if (statusReader && statusReader->isActive()) {
     qDebug() << "Well, we have an active status reader ... ;)";
     timer.start(40, this);
     }
  if (commandWriter && commandWriter->isActive()) {
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


void GuiKernel::usage() {
  std::cerr << std::endl << "FalconView V"  << version().toStdString().c_str() << std::endl
            << std::endl << "please specify the path to INI-file of your linuxCNC machine." << std::endl
            << std::endl << "supported options:"
            << std::endl << "\t-ini\t\t<mandatory>\tpath to INI-file of linuxCNC"
            << std::endl << "\t-help\t\t[optional]\tpath to FalconView helpfile"
            << std::endl << "\t-plugins\t[optional]\tpath to plugin-directory"
            << std::endl << "\t-i18n\t\t[optional]\tpath to translation files"
            << std::endl << std::endl;
  exit(-1);
  }

void GuiKernel::windowClosing(QCloseEvent *e) {
  // application is going to shut down ...
  cfg->settings.beginGroup("MainWindow");
  cfg->setValue("geometry",    mainWindow->saveGeometry());
  cfg->setValue("windowState", mainWindow->saveState());
  cfg->settings.endGroup();
  centerView->windowClosing(e);
  }
