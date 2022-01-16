#include <guicore.h>
#include <GuiKernelInterface.h>
#include <kernelcreator.h>
#include <pos9.h>
#include <ally3d.h>
#include <sysevent.h>
#include <syseventmodel.h>
#include <dbconnection.h>
#include <dbhelper.h>
#include <centerpage.h>
#include <settingsnb.h>
//#include <pluginpagefactory.h>
#include <helpdockable.h>
#include <pagestack.h>
#include <configacc.h>
#include <configmgr.h>

//#include <canonif.h>
////#include <canonifsettings.h>
//#include <lcproperties.h>
//#include <tooltable.h>
//#include <LCInter.h>
//#include <statusreader.h>
//#include <commandwriter.h>

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

//#include <emc.hh>

#include <cassert>


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

  guiCore()->activatePage(QString("%1Frame").arg(pageName));
  }


int GuiCore::activeGCodes() const {
  return guiCore()->activeGCodes();
  }


int GuiCore::activeMCodes() const {
  return guiCore()->activeMCodes();
  }


bool GuiCore::checkBE() {
//  if (checked < 0) {
//     bool rv = guiCore()->statusReader->isActive()
//            && guiCore()->commandWriter->isActive();

//     checked = 1;
//     if (!rv) {
//        ValueManager vm;

//        checked = 0;
//        qDebug() << ">>> Kernel::simulateStartOfBE() <<<";

//        vm.setValue("taskMode", EMC_TASK_MODE_ENUM::EMC_TASK_MODE_MANUAL);
//        vm.setValue("taskState", EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON);
//        vm.setValue("allHomed", true);
//        vm.setValue("execState", EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_DONE);
//        vm.setValue("interpState", EMC_TASK_INTERP_ENUM::EMC_TASK_INTERP_IDLE);
//        vm.setValue("errorActive", false);
//        }
//    }
//  return checked == 1;
  return guiCore()->checkBE();
  }


QString GuiCore::curPage() const {
  return guiCore()->activePage();
  }


GuiKernelInterface* GuiCore::guiCore() {
  return dynamic_cast<GuiKernelInterface*>(kernel);
  }


const GuiKernelInterface* GuiCore::guiCore() const {
  return dynamic_cast<const GuiKernelInterface*>(kernel);
  }


double GuiCore::defaultVelocity(int jointNum) const {
  return guiCore()->defaultVelocity(jointNum);
  }


double GuiCore::maxVelocity(int jointNum) const {
  return guiCore()->maxVelocity(jointNum);
  }


void GuiCore::help4Keyword(const QString &keyWord) {
  guiCore()->help4Keyword(keyWord);
  }


bool GuiCore::isLatheMode() const {
  return guiCore()->isLatheMode();
  }


bool GuiCore::isSimulator() const {
  return guiCore()->isSimulator();
  }


LcProperties& GuiCore::lcProperties() {
  return guiCore()->lcProperties();
  }


std::pair<QVector3D, QVector3D> GuiCore::machineLimits() const {
  return guiCore()->machineLimits();
  }


QMainWindow* GuiCore::mainWindow() {
  return guiCore()->mainWindow();
  }


QList<QString> GuiCore::pluggableMainPages() {
  return guiCore()->pluggableMainPages();
  }


PluginPageInterface* GuiCore::pluggableMainPage(const QString& pageID) {
  return guiCore()->pluggableMainPage(pageID);
  }


QList<QString> GuiCore::pluggableNotebookPages() {
  return guiCore()->pluggableNotebookPages();
  }


PluginPageInterface* GuiCore::pluggableNotebookPage(const QString& pageID) {
  return guiCore()->pluggableNotebookPage(pageID);
  }


//void GuiCore::processGCodeFile(const QString &fileName) {
//  QFile gcFile(fileName);

//  if (gcFile.exists()) guiCore()->processGCodeFile(gcFile);
//  }


void GuiCore::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  kernel->logSysEvent(se);
  QMessageBox::critical(guiCore()->mainWindow()
                      , SysEvent::toString(se.type())
                      , se.what());
  }


void GuiCore::setViewStack(PageStack* v) {
  guiCore()->setViewStack(v);
  }


void GuiCore::showHelp() const {
  guiCore()->showHelp();
  }


QList<QString> GuiCore::statusInfos() {
  return guiCore()->statusInfos();
  }


PluginPageInterface* GuiCore::statusInfo(const QString& infoID) {
  return guiCore()->statusInfo(infoID);
  }


void GuiCore::setAppMode4PageID(const QString& pageID) {
  if (pageID == "PreView3D")             ValueManager().setValue("appMode", ApplicationMode::Auto);
  else if (pageID == "MDIEditor")        ValueManager().setValue("appMode", ApplicationMode::MDI);
  else if (pageID == "JogView")          ValueManager().setValue("appMode", ApplicationMode::Manual);
  else if (pageID == "PathEditor")       ValueManager().setValue("appMode", ApplicationMode::Edit);
  else if (pageID == "Wheely")           ValueManager().setValue("appMode", ApplicationMode::Wheel);
  else if (pageID == "TestEdit")         ValueManager().setValue("appMode", ApplicationMode::XEdit);
  else if (pageID == "SettingsNotebook") ValueManager().setValue("appMode", ApplicationMode::Settings);
  else if (pageID == "FileManager")      ValueManager().setValue("appMode", ApplicationMode::SelectFile);
  else if (pageID == "TouchView")        ValueManager().setValue("appMode", ApplicationMode::Touch);
  else if (pageID == "SysEventView")     ValueManager().setValue("appMode", ApplicationMode::ErrMessages);
  }


void GuiCore::setMainWindow(QMainWindow *w) {
  guiCore()->setMainWindow(w);
  }


QWidget* GuiCore::stackedPage(const QString& pageName) {
  return guiCore()->stackedPage(QString("%1Frame").arg(pageName));
  }


void GuiCore::setWindowTitle(const QString &title) {
  guiCore()->setWindowTitle(title);
  }


Pos9 GuiCore::toolOffset() const {
  throw std::system_error(-1, std::system_category(), "need to reimplement tool-offset!");
  return Pos9(); // guiCore()->canonIF->canon.toolOffset);
  }


ToolTable& GuiCore::toolTable() {
  return guiCore()->toolTable();
  }


ToolTable* GuiCore::toolTableModel() {
  return guiCore()->toolTableModel();
  }


OcctQtViewer* GuiCore::view3D() {
  qDebug() << "GuiCore: kernel is:" << guiCore();
  return guiCore()->view3D();
  }


PageStack* GuiCore::viewStack() {
  return guiCore()->viewStack();
  }


void GuiCore::windowClosing(QCloseEvent *e) {
  guiCore()->windowClosing(e);
  }


void GuiCore::beAbortTask() {
  guiCore()->beAbortTask();
  }


void GuiCore::beEnableBlockDelete(bool enable) {
    guiCore()->beEnableBlockDelete(enable);
    }


void GuiCore::beEnableFlood(bool enable) {
    guiCore()->beEnableFlood(enable);
    }


void GuiCore::beEnableMist(bool enable) {
    guiCore()->beEnableMist(enable);
    }


void GuiCore::beEnableOptionalStop(bool enable) {
    guiCore()->beEnableOptionalStop(enable);
    }


void GuiCore::beSetSpindleOverride(double rate) {
    guiCore()->beSetSpindleOverride(rate);
    }


void GuiCore::beJogStep(int axis, double stepSize, double speed) {
    guiCore()->beJogStep(axis, stepSize, speed);
    }


void GuiCore::beJogStart(int axis, double speed) {
    guiCore()->beJogStart(axis, speed);
    }


void GuiCore::beJogStop(int axis) {
    guiCore()->beJogStop(axis);
    }


void GuiCore::beHomeAxis(int jointNum) {
    guiCore()->beHomeAxis(jointNum);
    }


void GuiCore::beLoadTaskPlan(const QString& gcodeFile) {
    guiCore()->beLoadTaskPlan(gcodeFile);
    }


void GuiCore::beLoadToolTable(const QString& toolTableFile) {
    guiCore()->beLoadToolTable(toolTableFile);
    }


void GuiCore::beSendMDICommand(const QString& command) {
    guiCore()->beSendMDICommand(command);
    }


void GuiCore::beSetAuto(int autoMode, int line) {
    guiCore()->beSetAuto(autoMode, line);
    }


void GuiCore::beSetFeedOverride(double rate) {
    guiCore()->beSetFeedOverride(rate);
    }


void GuiCore::beSetRapidOverride(double rate) {
    guiCore()->beSetRapidOverride(rate);
    }


void GuiCore::beSetSpindle(bool enable, int speed, int direction) {
    guiCore()->beSetSpindle(enable, speed, direction);
    }


void GuiCore::beSetTaskMode(int mode) {
    guiCore()->beSetTaskMode(mode);
    }


void GuiCore::beSetTaskState(int state) {
    guiCore()->beSetTaskState(state);
    }


void GuiCore::beTaskPlanSynch() {
    guiCore()->beTaskPlanSynch();
    }
