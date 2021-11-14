#include <timestamp.h>
#include <QFile>
#include <QTextStream>


long TimeStamp::rtSequence() {
  QFile sysTime("/proc/uptime");

  if (sysTime.open(QIODevice::ReadOnly | QIODevice::Text)) {
     QTextStream in(&sysTime);
     QStringList parts = in.readLine().split(" ");
     bool   ok = false;
     double ts = 0;

     sysTime.close();
     if (parts.size()) ts = parts[0].toDouble(&ok);
     if (ok) return ts * 1000;
     }
  return 0;
  }
