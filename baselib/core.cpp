#include <core.h>
#include <kernelcreator.h>
#include <kernel.h>
#include <QTime>
#include <QTimerEvent>
#include <QApplication>
#include <QTranslator>
#include <QString>
#include <QVector3D>
#include <QSqlError>
#include <QMessageBox>
#include <core.h>
#include <sysevent.h>
#include <syseventmodel.h>
#include <lcproperties.h>
#include <dynframe.h>
#include <tooltable.h>
#include <canonif.h>
#include <configacc.h>
#include <configmgr.h>
#include <cassert>
#include <emc.hh>


Core::Core(const QString& iniFileName, const QString& appName, DBHelper& dbAssist, const QString& group) {
  if (!kernel) {
     assert(kc);
     kernel = kc->kernel(iniFileName, appName, group);
     kernel->initialize(dbAssist);
     }
  }


int Core::axisMask() const {
  return core()->axisMask();
  }


Kernel* Core::core() {
  assert(kernel != nullptr);
  return kernel;
  }


const Kernel* Core::core() const {
  assert(kernel != nullptr);
  return kernel;
  }


DBConnection* Core::databaseConnection() {
  return core()->conn;
  }


QString Kernel::fileName4(const QString &fileID) {
  if (fileID == "helpFile") {
     return QApplication::applicationDirPath() + "/../share/doc/falconview/FalconView.qzh";
     }
  return fileName;
  }


void Core::setKernelCreator(KernelCreator* kc) {
  Core::kc = kc;
  }


bool Core::isSimulator() const {
  return core()->simulator;
  }


bool Core::move2Backup(const QString& fileName) {
  QString   backupPat(fileName);
  QFileInfo fi(fileName);
  QString   extension(QString(".%1").arg(fi.completeSuffix()));

  backupPat.replace(extension, ".bak%1");
  QFileInfo check(backupPat.arg(""));

  if (check.exists()) {
     QFile last(backupPat.arg(9));

     if (last.exists()) last.remove();
     for (int i=8; i > 0; --i) {
         QFile tmp(backupPat.arg(i));

         if (tmp.exists()) tmp.rename(backupPat.arg(i+1));
         }
     QFile tmp(check.absoluteFilePath());

     tmp.rename(backupPat.arg(1));
     }
  QFile file(fileName);

  return file.rename(check.absoluteFilePath());
  }


void Core::setAppMode(ApplicationMode m) {
  ValueManager().setValue("appMode", m);
  }


void Core::setLocale(const QLocale &l) {
  core()->locale = l;
  }


QLocale Core::locale() const {
  return core()->locale;
  }


void Core::showAllButCenter(bool visible) {
  ValueManager().setValue("showAllButCenter", visible);
  }


void Core::help4Keyword(const QString &keyWord) {
  qDebug() << "Core::help4Keyword(" << keyWord << ") NEEDS to get REIMPLEMENTED !!!";
//  if (core()->mainWindow) {
//     core()->mainWindow->helpDialog()->help4Keyword(keyWord);
//     }
  }


bool Core::showHelpAtPageChange() const {
  return core()->cfg.value("showHelpAtPageChange").toBool();
  }


QString Core::languagePrefix() const {
  return core()->locale.name().mid(0, 2);
  }


void Core::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  core()->logSysEvent(se);
  }


void Core::showHelp() {
  setAppMode(ApplicationMode::Help);
  }

Kernel*        Core::kernel  = nullptr;
KernelCreator* Core::kc = nullptr;
int            Core::checked = -1;
