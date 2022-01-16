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


Core::Core(QApplication& app, const QString& appName, DBHelper& dbAssist, const QString& group) {
  if (!kernel) {
     assert(kc);
     kernel = kc->kernel(app, appName, group);
     kernel->initialize(dbAssist);
     }
  }


Core::Core() {
  assert(kernel);
  }


// dumb, but plugins have their own copy of statics :(
Core::Core(void* pFromOuterAdressSpace) {
  if (!kernel) kernel = (Kernel*)pFromOuterAdressSpace;
  assert(kernel);
  }


int Core::axisMask() const {
  return kernel->axisMask();
  }


DBConnection* Core::databaseConnection() {
  return kernel->databaseConnection();
  }


QString Core::fileName4(const QString &fileID) const {
  return kernel->fileName4(fileID);
  }


void Core::setKernelCreator(KernelCreator* kc) {
  Core::kc = kc;
  }


bool Core::isSimulator() const {
  return kernel->isSimulator();
  }


QLocale Core::locale() const {
  return kernel->locale();
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
  return kernel->locale().name().mid(0, 2);
  }


void Core::riseError(const QString &msg) {
  ValueManager().setValue("errorActive", true);
  SysEvent se(msg);

  kernel->logSysEvent(se);
  }


void Core::showAllButCenter(bool visible) {
  ValueManager().setValue("showAllButCenter", visible);
  }


bool Core::showHelpAtPageChange() const {
  return kernel->config()->value("showHelpAtPageChange").toBool();
  }

KernelInterface* Core::kernel  = nullptr;
KernelCreator*   Core::kc      = nullptr;
int              Core::checked = -1;
