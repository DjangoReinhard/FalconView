#ifndef KERNEL_H
#define KERNEL_H
#include <QObject>
#include <QBasicTimer>
#include <QLocale>
#include <configmgr.h>
class DBHelper;
class DBConnection;
class SysEvent;


class Kernel : public QObject
{
  Q_OBJECT
public:
  virtual void logSysEvent(const SysEvent& se);

protected:
  explicit Kernel(const QStringList& appArgs, const QString& appName, const QString& groupID);
  virtual ~Kernel() = default;

  virtual int  axisMask() const;
  virtual void logSysEvent(const QString& msg);
  virtual void initialize(const QLocale& locale, DBHelper& dbAssist);
  virtual QString fileName4(const QString& fileID) const;
  virtual void processAppArgs(const QStringList& args);

  bool                simulator;
  ConfigManager*      cfg;
  QLocale*            locale;
  DBConnection*       conn;  
  QStringList         appArgs;
  QString             appName;
  QString             groupID;
  QBasicTimer         timer;

  friend class Core;
  friend class Config;
  friend class KernelCreator;
  };
#endif // KERNEL_H
