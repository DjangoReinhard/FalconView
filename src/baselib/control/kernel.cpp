#include <kernel.h>
#include <sysevent.h>
#include <QDebug>


Kernel::Kernel(const QStringList& appArgs, const QString& appName, const QString& groupID)
 : QObject(nullptr)
 , simulator(false)
 , cfg(new ConfigManager(appName, groupID))
 , locale(nullptr)
 , conn(nullptr)
 , appArgs(appArgs)
 , appName(appName)
 , groupID(groupID) {
  }


int Kernel::axisMask() const {
  return 0;
  }


QString Kernel::fileName4(const QString&) const {
  return QString();
  }


void Kernel::initialize(const QLocale& locale, DBHelper&) {
  this->locale = new QLocale(locale);
  processAppArgs(appArgs);
  }


void Kernel::logSysEvent(const QString &msg) {
  logSysEvent(SysEvent(msg));
  }


void Kernel::logSysEvent(const SysEvent& se) {
  qDebug() << "system event" << se.type() << ":" << se.what() << " at:" << se.when();
  }


void Kernel::processAppArgs(const QStringList& args) {
  }
