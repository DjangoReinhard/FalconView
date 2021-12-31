#include <core.h>
#include <kernelcreator.h>
#include <kernel.h>
#include <configacc.h>
#include <configmgr.h>
#include <sysevent.h>
#include <syseventmodel.h>

#include <QApplication>
#include <QFileInfo>
#include <QDebug>

#include <cassert>
#include <emc.hh>


Core::Core(const QString& iniFileName, const QString& appName, const QLocale& locale, DBHelper& dbAssist, const QString& group) {
  if (!kernel) {
     assert(kc);
     kernel = kc->kernel(iniFileName, appName, group);
     kernel->initialize(locale, dbAssist);
     }
  }


Core::Core() {
  assert(kernel);
  }


int Core::axisMask() const {
  return core()->axisMask();
  }


Kernel* Core::core() {
  return kernel;
  }


const Kernel* Core::core() const {
  return kernel;
  }


DBConnection* Core::databaseConnection() {
  return core()->conn;
  }


QString Core::fileName4(const QString &fileID) const {
  return core()->fileName4(fileID);
  }


void Core::help4Keyword(const QString &keyWord) {
  qDebug() << "Core::help4Keyword(" << keyWord << ") NEEDS to get REIMPLEMENTED !!!";
//  if (core()->mainWindow) {
//     core()->mainWindow->helpDialog()->help4Keyword(keyWord);
//     }
  }


void Core::setKernelCreator(KernelCreator* kc) {
  Core::kc = kc;
  }


bool Core::isSimulator() const {
  return core()->simulator;
  }


QLocale Core::locale() const {
  return *core()->locale;
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


QString Core::languagePrefix() const {
  return core()->locale->name().mid(0, 2);
  }


void Core::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  core()->logSysEvent(se);
  }


void Core::showAllButCenter(bool visible) {
  ValueManager().setValue("showAllButCenter", visible);
  }


void Core::showHelp() {
  setAppMode(ApplicationMode::Help);
  }


bool Core::showHelpAtPageChange() const {
  return core()->cfg->value("showHelpAtPageChange").toBool();
  }

Kernel*        Core::kernel  = nullptr;
KernelCreator* Core::kc      = nullptr;
int            Core::checked = -1;
