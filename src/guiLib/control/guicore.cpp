#include <guikernel.h>
#include <guicore.h>
#include <kernelcreator.h>
#include <pos9.h>
#include <ally3d.h>
#include <sysevent.h>
#include <syseventmodel.h>
#include <dbconnection.h>
#include <dbhelper.h>
#include <centerpage.h>
#include <settingsnb.h>
#include <pluginpagefactory.h>
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


std::pair<QVector3D, QVector3D> GuiCore::machineLimits() const {
  return guiCore()->lcIF->machineLimits();
  }


QMainWindow* GuiCore::mainWindow() {
  return guiCore()->mainWindow;
  }


QList<QString> GuiCore::pluggableMainPages() {
  return guiCore()->mainPages.keys();
  }


PluginPageInterface* GuiCore::pluggableMainPage(const QString pageID) {
  if (guiCore()->mainPages.contains(pageID))
     return guiCore()->mainPages[pageID];
  return nullptr;
  }


QList<QString> GuiCore::pluggableNotebookPages() {
  return guiCore()->nbPages.keys();
  }


PluginPageInterface* GuiCore::pluggableNotebookPage(const QString pageID) {
  if (guiCore()->nbPages.contains(pageID))
     return guiCore()->nbPages[pageID];
  return nullptr;
  }


//void GuiCore::processGCodeFile(const QString &fileName) {
//  QFile gcFile(fileName);

//  if (gcFile.exists()) guiCore()->processGCodeFile(gcFile);
//  }


void GuiCore::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  kernel->logSysEvent(se);
  QMessageBox::critical(guiCore()->mainWindow
                      , SysEvent::toString(se.type())
                      , se.what());
  }


void GuiCore::setViewStack(PageStack* v) {
  guiCore()->centerView = v;
  }


QList<QString> GuiCore::statusInfos() {
  return guiCore()->statusInfos.keys();
  }


void GuiCore::showHelp() const {
  if (guiCore()->help) guiCore()->help->showHelp();
  }

PluginPageInterface* GuiCore::statusInfo(const QString infoID) {
  if (guiCore()->statusInfos.contains(infoID))
     return guiCore()->statusInfos[infoID];
  return nullptr;
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


void GuiCore::setWindowTitle(const QString &title) {
  if (guiCore()->mainWindow) {
     guiCore()->mainWindow->setWindowTitle(guiCore()->mainWindow->objectName()
                                      + " - "
                                      + title);
     }
  }


Pos9 GuiCore::toolOffset() const {
  throw std::system_error(-1, std::system_category(), "need to reimplement tool-offset!");
  return Pos9(); // guiCore()->canonIF->canon.toolOffset);
  }


ToolTable& GuiCore::toolTable() {
  return *guiCore()->tt;
  }


ToolTable* GuiCore::toolTableModel() {
  return guiCore()->tt;
  }


OcctQtViewer* GuiCore::view3D() {
  qDebug() << "GuiCore: kernel is:" << guiCore();
  return guiCore()->view3D;
  }


PageStack* GuiCore::viewStack() {
  return guiCore()->centerView;
  }


void GuiCore::windowClosing(QCloseEvent *e) {
  guiCore()->windowClosing(e);
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
