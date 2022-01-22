#include <guicore.h>
#include <KernelInterface.h>
#include <kernelcreator.h>
#include <pos9.h>
#include <ally3d.h>
#include <sysevent.h>
#include <syseventmodel.h>
#include <dbconnection.h>
#include <dbhelper.h>
#include <centerpage.h>
#include <settingsnb.h>
#include <helpdockable.h>
#include <pagestack.h>
#include <configacc.h>
#include <configmgr.h>

#include <QTime>
#include <QTimerEvent>
#include <QApplication>
#include <QFileInfo>
#include <QTranslator>
#include <QString>
#include <QVector3D>
#include <QSqlError>
#include <QMessageBox>
#include <QMainWindow>

#include <occtviewer.h>
#include <emc_nml.hh>

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

  kernel->activatePage(QString("%1Frame").arg(pageName));
  }


int GuiCore::activeGCodes() const {
  return kernel->activeGCodes();
  }


int GuiCore::activeMCodes() const {
  return kernel->activeMCodes();
  }


int GuiCore::axisMask() const {
  return kernel->axisMask();
  }


bool GuiCore::checkBE() {
  return kernel->checkBE();
  }


QString GuiCore::curPage() const {
  return kernel->activePage();
  }


//DBConnection* GuiCore::databaseConnection() {
//  return kernel->databaseConnection();
//  }


double GuiCore::defaultVelocity(int jointNum) const {
  return kernel->defaultVelocity(jointNum);
  }


double GuiCore::maxVelocity(int jointNum) const {
  return kernel->maxVelocity(jointNum);
  }


void GuiCore::help4Keyword(const QString &keyWord) {
  kernel->help4Keyword(keyWord);
  }


bool GuiCore::isLatheMode() const {
  return kernel->isLatheMode();
  }


LcProperties& GuiCore::lcProperties() {
  return kernel->lcProperties();
  }


std::pair<QVector3D, QVector3D> GuiCore::machineLimits() const {
  return kernel->machineLimits();
  }


QMainWindow* GuiCore::mainWindow() {
  return kernel->mainWindow();
  }


QList<QString> GuiCore::pluggableMainPages() {
  return kernel->pluggableMainPages();
  }


ViewPluginInterface* GuiCore::pluggableMainPage(const QString& pageID) {
  return kernel->pluggableMainPage(pageID);
  }


QList<QString> GuiCore::pluggableNotebookPages() {
  return kernel->pluggableNotebookPages();
  }


ViewPluginInterface* GuiCore::pluggableNotebookPage(const QString& pageID) {
  return kernel->pluggableNotebookPage(pageID);
  }


void GuiCore::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  kernel->logSysEvent(se);
  QMessageBox::critical(kernel->mainWindow()
                      , SysEvent::toString(se.type())
                      , se.what());
  }


void GuiCore::setViewStack(PageStack* v) {
  kernel->setViewStack(v);
  }


void GuiCore::setKernelCreator(KernelCreator* kc) {
  GuiCore::kc = kc;
  }


void GuiCore::showHelp() const {
  kernel->showHelp();
  }


QList<QString> GuiCore::statusInfos() {
  return kernel->statusInfos();
  }


ViewPluginInterface* GuiCore::statusInfo(const QString& infoID) {
  return kernel->statusInfo(infoID);
  }


void GuiCore::setAppMode4PageID(const QString& pageID) {
  kernel->setAppMode4PageID(pageID);
  }


void GuiCore::setMainWindow(QMainWindow *w) {
  kernel->setMainWindow(w);
  }


QWidget* GuiCore::stackedPage(const QString& pageName) {
  return kernel->stackedPage(QString("%1Frame").arg(pageName));
  }


void GuiCore::setWindowTitle(const QString &title) {
  kernel->setWindowTitle(title);
  }


Pos9 GuiCore::toolOffset() const {
  throw std::system_error(-1, std::system_category(), "need to reimplement tool-offset!");
  return Pos9(); // kernel->canonIF->canon.toolOffset);
  }


ToolTable& GuiCore::toolTable() {
  return kernel->toolTable();
  }


ToolTable* GuiCore::toolTableModel() {
  return kernel->toolTableModel();
  }


OcctQtViewer* GuiCore::view3D() {
  qDebug() << "GuiCore: kernel is:" << kernel;

  return kernel->view3D();
  }


PageStack* GuiCore::viewStack() {
  return kernel->viewStack();
  }


void GuiCore::windowClosing(QCloseEvent *e) {
  kernel->windowClosing(e);
  }


void GuiCore::beAbortTask() {
  kernel->beAbortTask();
  }


void GuiCore::beEnableBlockDelete(bool enable) {
    kernel->beEnableBlockDelete(enable);
    }


void GuiCore::beEnableFlood(bool enable) {
    kernel->beEnableFlood(enable);
    }


void GuiCore::beEnableMist(bool enable) {
    kernel->beEnableMist(enable);
    }


void GuiCore::beEnableOptionalStop(bool enable) {
    kernel->beEnableOptionalStop(enable);
    }


void GuiCore::beSetSpindleOverride(double rate) {
    kernel->beSetSpindleOverride(rate);
    }


void GuiCore::beJogStep(int axis, double stepSize, double speed) {
    kernel->beJogStep(axis, stepSize, speed);
    }


void GuiCore::beJogStart(int axis, double speed) {
    kernel->beJogStart(axis, speed);
    }


void GuiCore::beJogStop(int axis) {
    kernel->beJogStop(axis);
    }


void GuiCore::beHomeAxis(int jointNum) {
    kernel->beHomeAxis(jointNum);
    }


void GuiCore::beLoadTaskPlan(const QString& gcodeFile) {
    kernel->beLoadTaskPlan(gcodeFile);
    }


void GuiCore::beLoadToolTable(const QString& toolTableFile) {
    kernel->beLoadToolTable(toolTableFile);
    }


void GuiCore::beSendMDICommand(const QString& command) {
    kernel->beSendMDICommand(command);
    }


void GuiCore::beSetAuto(int autoMode, int line) {
    kernel->beSetAuto(autoMode, line);
    }


void GuiCore::beSetFeedOverride(double rate) {
    kernel->beSetFeedOverride(rate);
    }


void GuiCore::beSetRapidOverride(double rate) {
    kernel->beSetRapidOverride(rate);
    }


void GuiCore::beSetSpindle(bool enable, int speed, int direction) {
    kernel->beSetSpindle(enable, speed, direction);
    }


void GuiCore::beSetTaskMode(int mode) {
    kernel->beSetTaskMode(mode);
    }


void GuiCore::beSetTaskState(int state) {
    kernel->beSetTaskState(state);
    }


void GuiCore::beTaskPlanSynch() {
    kernel->beTaskPlanSynch();
    }

const int GuiCore::taskStateOn        = EMC_TASK_STATE_ENUM::EMC_TASK_STATE_ON;
const int GuiCore::taskWaiting4Motion = EMC_TASK_EXEC_ENUM::EMC_TASK_EXEC_WAITING_FOR_MOTION;
