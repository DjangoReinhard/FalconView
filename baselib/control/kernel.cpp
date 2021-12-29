#include <kernel.h>
#include <sysevent.h>
#include <QDebug>


Kernel::Kernel(const QString& fileName, const QString& appName, const QString& groupID)
 : QObject(nullptr)
 , simulator(false)
 , cfg(appName, groupID)
 , conn(nullptr)
 , fileName(fileName)
 , appName(appName)
 , groupID(groupID) {
  }


int Kernel::axisMask() const {
  return 0;
  }


QString Kernel::fileName4(const QString&) {
  return fileName;
  }


void Kernel::initialize(DBHelper&) {
  }


void Kernel::logSysEvent(const QString &msg) {
  logSysEvent(SysEvent(msg));
  }


void Kernel::logSysEvent(const SysEvent& se) {
  qDebug() << "system event" << se.type() << ":" << se.what() << " at:" << se.when();
  }
