#include <guikernel.h>
#include <dbhelper.h>
#include <dbconnection.h>
#include <configacc.h>
#include <pagestack.h>
#include <centerpage.h>
#include <helpdockable.h>
#include <pluginpagefactory.h>
#include <canonif.h>
#include <tooltable.h>
#include <axismask.h>
#include <pos9.h>
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


GuiKernel::GuiKernel(int maxGCodes, int maxMCodes, QApplication& app, const QString& appName, const QString& groupID)
 : Kernel(app, appName, groupID)
 , maxGCodes(maxGCodes)
 , maxMCodes(maxMCodes)
 , lcProps(nullptr)
 , tt(nullptr)
 , lcIF(nullptr)
 , mAxis(nullptr)
 , v3D(nullptr)
 , centerView(nullptr)
 , wMain(nullptr)
 , ally3D(new Ally3D())
 , statusReader(nullptr)
 , commandWriter(nullptr)
 , sysEvents(nullptr) {
  }


int GuiKernel::axisMask() const {
  return mAxis->mask();
  }


int GuiKernel::activeGCodes() const {
  return maxGCodes;
  }


int GuiKernel::activeMCodes() const {
  return maxMCodes;
  }


void GuiKernel::beAbortTask() {
  emit abortTask();
  }


void GuiKernel::beEnableBlockDelete(bool enable) {
    emit enableBlockDelete(enable);
    }


void GuiKernel::beEnableFlood(bool enable) {
    emit enableFlood(enable);
    }


void GuiKernel::beEnableMist(bool enable) {
    emit enableMist(enable);
    }


void GuiKernel::beEnableOptionalStop(bool enable) {
    emit enableOptionalStop(enable);
    }


void GuiKernel::beSetSpindleOverride(double rate) {
    emit setSpindleOverride(rate);
    }


void GuiKernel::beJogStep(int axis, double stepSize, double speed) {
    emit jogStep(axis, stepSize, speed);
    }


void GuiKernel::beJogStart(int axis, double speed) {
    emit jogStart(axis, speed);
    }


void GuiKernel::beJogStop(int axis) {
    emit jogStop(axis);
    }


void GuiKernel::beHomeAxis(int jointNum) {
    emit homeAxis(jointNum);
    }


void GuiKernel::beLoadTaskPlan(const QString& gcodeFile) {
    emit loadTaskPlan(gcodeFile);
    }


void GuiKernel::beLoadToolTable(const QString& toolTableFile) {
    emit loadToolTable(toolTableFile);
    }


void GuiKernel::beSendMDICommand(const QString& command) {
    emit sendMDICommand(command);
    }


void GuiKernel::beSetAuto(int autoMode, int line) {
    emit setAuto(autoMode, line);
    }


void GuiKernel::beSetFeedOverride(double rate) {
    emit setFeedOverride(rate);
    }


void GuiKernel::beSetRapidOverride(double rate) {
    emit setRapidOverride(rate);
    }


void GuiKernel::beSetSpindle(bool enable, int speed, int direction) {
    emit setSpindle(enable, speed, direction);
    }


void GuiKernel::beSetTaskMode(int mode) {
    emit setTaskMode(mode);
    }


void GuiKernel::beSetTaskState(int state) {
    emit setTaskState(state);
    }


void GuiKernel::beTaskPlanSynch() {
    emit taskPlanSynch();
    }


//ConfigManager* GuiKernel::config() const {
//  return cfg;
//  }


//ConfigManager* GuiKernel::config() {
//  return cfg;
//  }


DBConnection* GuiKernel::createDatabase(DBHelper& dbAssist) {
  DBConnection* conn = dbAssist.createDatabase(dbAssist.dbConnection()->dbName());

  dbAssist.createSampleData(*conn);

  return conn;
  }


//DBConnection* GuiKernel::databaseConnection() {
//  return conn;
//  }


bool GuiKernel::isSimulator() const {
  return false;
  }


//QLocale GuiKernel::locale() const {
//  return *curLocale;
//  }

void    GuiKernel::activatePage(const QString& pageName) {
  }


QString GuiKernel::activePage() const {
  return "";
  }


QString GuiKernel::curPage() const {
  return "";
  }


void GuiKernel::help4Keyword(const QString& keyWord) {
  if (help) help->help4Keyword(keyWord);
  }


QMainWindow* GuiKernel::mainWindow() {
  return wMain;
  }


QList<QString> GuiKernel::pluggableMainPages() const {
  return mainPages.keys();
  }


QList<QString> GuiKernel::pluggableNotebookPages() const {
  return nbPages.keys();
  }


void GuiKernel::setAppMode4PageID(const QString& pageID) {
  }


PageStack* GuiKernel::viewStack() {

  }


bool                            GuiKernel::checkBE() {

  }


LcProperties&                   GuiKernel::lcProperties() {

  }


const LcProperties&             GuiKernel::lcProperties() const {

  }


std::pair<QVector3D, QVector3D> GuiKernel::machineLimits() const {

  }


Pos9                            GuiKernel::toolOffset() const {

  }


ToolTable&                      GuiKernel::toolTable() {

  }


ToolTable*                      GuiKernel::toolTableModel() {

  }


OcctQtViewer*                   GuiKernel::view3D() {

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
  else if (fileID == "nc_files") {
     qDebug() << "GK::fileName4(" << fileID << ") => " << nc_files;
     return nc_files;
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
  sysEvents = new SysEventModel(*conn, (Kernel*)this);
  sysEvents->setTable("SysEvents");
  nc_files = lcProperties().getPath("DISPLAY", "PROGRAM_PREFIX");

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
  v3D = new OcctQtViewer();
  ally3D->setOcctViewer(v3D);

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
            statInfos[name] = iPlugin;
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
  Kernel::connect(ValueManager().getModel("fileName", " "), &ValueModel::valueChanged
        , this, &GuiKernel::processGCodeFile);
  Kernel::connect(ValueManager().getModel("conePos", QVector3D()), &ValueModel::valueChanged
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


double GuiKernel::defaultVelocity(int jointNum) const {
//  QString groupID = QString("JOINT_%1").arg(jointNum);

//  return lcProperties().value(groupID, "HOME_SEARCH_VEL").toDouble() + 60;
  return lcProperties().value("TRAJ", "DEFAULT_LINEAR_VELOCITY").toDouble() + 60;
  }


double GuiKernel::maxVelocity(int jointNum) const {
//  QString groupID = QString("JOINT_%1").arg(jointNum);

//  return lcProperties().value(groupID, "MAX_VELOCITY").toDouble() + 60;
  return lcProperties().value("TRAJ", "MAX_LINEAR_VELOCITY").toDouble() + 60;
  }


void GuiKernel::nop() const {
  }


PluginPageInterface* GuiKernel::pluggableMainPage(const QString& pageID) const {
  if (mainPages.contains(pageID))
     return mainPages[pageID];
  return nullptr;
  }


//QList<QString> GuiKernel::pluggableNotebookPages() const {
//  return nbPages.keys();
//  }


PluginPageInterface* GuiKernel::pluggableNotebookPage(const QString& pageID) const {
  if (nbPages.contains(pageID))
     return nbPages[pageID];
  return nullptr;
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


void GuiKernel::setMainWindow(QMainWindow *w) {
  PluginPageFactory     ppf;
  AbstractCenterWidget* cw  = ppf.createCenterPage("HelpView");
  HelpView*             hv  = reinterpret_cast<HelpView*>(cw);

  wMain = w;
  help  = new HelpDockable(hv, w);
  }


void GuiKernel::setViewStack(PageStack *v) {
  centerView = v;
  }


void GuiKernel::setupBackend() {
  if (statusReader && statusReader->isActive()) {
     qDebug() << "Well, we have an active status reader ... ;)";
     timer.start(40, (Kernel*)this);
     }
  if (commandWriter && commandWriter->isActive()) {
     qDebug() << "OK, ok, ok - backend seems to be available!";
     commandWriter->moveToThread(&backendCommThread);
     Kernel::connect(&backendCommThread, &QThread::finished, &backendCommThread, &QObject::deleteLater);

     Kernel::connect(this, &GuiKernel::abortTask, commandWriter, &CommandWriter::abortTask);
     Kernel::connect(this, &GuiKernel::enableBlockDelete, commandWriter, &CommandWriter::enableBlockDelete);
     Kernel::connect(this, &GuiKernel::enableFlood, commandWriter, &CommandWriter::enableFlood);
     Kernel::connect(this, &GuiKernel::enableMist, commandWriter, &CommandWriter::enableMist);
     Kernel::connect(this, &GuiKernel::enableOptionalStop, commandWriter, &CommandWriter::enableOptionalStop);
     Kernel::connect(this, &GuiKernel::setSpindleOverride, commandWriter, &CommandWriter::setSpindleOverride);
     Kernel::connect(this, &GuiKernel::jogStep, commandWriter, &CommandWriter::jogStep);
     Kernel::connect(this, &GuiKernel::jogStart, commandWriter, &CommandWriter::jogStart);
     Kernel::connect(this, &GuiKernel::jogStop, commandWriter, &CommandWriter::jogStop);
     Kernel::connect(this, &GuiKernel::homeAxis, commandWriter, &CommandWriter::homeAxis);
     Kernel::connect(this, &GuiKernel::loadTaskPlan, commandWriter, &CommandWriter::loadTaskPlan);
     Kernel::connect(this, &GuiKernel::loadToolTable, commandWriter, &CommandWriter::loadToolTable);
     Kernel::connect(this, &GuiKernel::sendMDICommand, commandWriter, &CommandWriter::sendMDICommand);
     Kernel::connect(this, &GuiKernel::setAuto, commandWriter, &CommandWriter::setAuto);
     Kernel::connect(this, &GuiKernel::setFeedOverride, commandWriter, &CommandWriter::setFeedOverride);
     Kernel::connect(this, &GuiKernel::setRapidOverride, commandWriter, &CommandWriter::setRapidOverride);
     Kernel::connect(this, &GuiKernel::setSpindle, commandWriter, &CommandWriter::setSpindle);
     Kernel::connect(this, &GuiKernel::setTaskMode, commandWriter, &CommandWriter::setTaskMode);
     Kernel::connect(this, &GuiKernel::setTaskState, commandWriter, &CommandWriter::setTaskState);
     Kernel::connect(this, &GuiKernel::taskPlanSynch, commandWriter, &CommandWriter::taskPlanSynch);

     Kernel::connect(commandWriter, SIGNAL(systemEvent(const SysEvent&)), (Kernel*)this, SLOT(riseError(const SysEvent&)));
     backendCommThread.start();
     }
  else {
     qDebug() << "Bad luck this time. Sorry but no backend!";
     Kernel::connect(this, &GuiKernel::abortTask, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::enableBlockDelete, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::enableFlood, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::enableMist, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::enableOptionalStop, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::setSpindleOverride, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::jogStep, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::jogStart, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::jogStop, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::homeAxis, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::loadTaskPlan, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::loadToolTable, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::sendMDICommand, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::setAuto, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::setFeedOverride, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::setRapidOverride, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::setSpindle, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::setTaskMode, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::setTaskState, this, &GuiKernel::nop);
     Kernel::connect(this, &GuiKernel::taskPlanSynch, this, &GuiKernel::nop);
     }
  }


void GuiKernel::setWindowTitle(const QString &title) {
  if (wMain) {
     wMain->setWindowTitle(wMain->objectName()
                         + " - "
                         + title);
     }
  }

void GuiKernel::showHelp() const {
  if (help) help->showHelp();
  }


QWidget* GuiKernel::stackedPage(const QString &pageName) {
  return centerView->page(QString("%1Frame").arg(pageName));
  }

QList<QString> GuiKernel::statusInfos() const {
  return statInfos.keys();
  }


PluginPageInterface* GuiKernel::statusInfo(const QString& infoID) const {
  if (statInfos.contains(infoID))
     return statInfos[infoID];
  return nullptr;
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
  else Kernel::timerEvent(e);
  }


void GuiKernel::updateView(const QVariant &v) {
  QVector3D p = v.value<QVector3D>();

  ally3D->moveCone(p.x(), p.y(), p.z());
  }


void GuiKernel::usage() {
  std::cerr << std::endl << "FalconView V"  << Kernel::version().toStdString().c_str() << std::endl
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
  cfg->setValue("geometry",    mainWindow()->saveGeometry());
  cfg->setValue("windowState", mainWindow()->saveState());
  cfg->settings.endGroup();
  centerView->windowClosing(e);
  }
