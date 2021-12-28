#ifndef KERNEL_H
#define KERNEL_H
#include <QObject>
#include <configmgr.h>
#include <QBasicTimer>
#include <QLocale>
class DBHelper;
class DBConnection;
class SysEvent;


class Kernel : public QObject
{
  Q_OBJECT
protected:
  explicit Kernel(const QString& iniFilename, const QString& appName, const QString& groupID);

  virtual int  axisMask() const;
  virtual void logSysEvent(const QString& msg);
  virtual void logSysEvent(const SysEvent& se);
  virtual void initialize(DBHelper& dbAssist);
  virtual QString fileName4(const QString& fileID);

  bool                simulator;
  ConfigManager       cfg;
  QLocale             locale;
  DBConnection*       conn;
  QString             fileName;
  QString             appName;
  QString             groupID;
  QBasicTimer         timer;

  friend class Core;
  friend class Config;
  friend class KernelCreator;
  };
#endif // KERNEL_H
