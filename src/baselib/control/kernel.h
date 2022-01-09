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
  explicit Kernel(QApplication& app, const QString& appName, const QString& groupID);
  virtual ~Kernel() = default;

  virtual int      axisMask() const;
  virtual void     logSysEvent(const QString& msg);
  virtual void     initialize(DBHelper& dbAssist);
  virtual QString  fileName4(const QString& fileID) const;
  virtual void     processAppArgs(const QStringList& args);
  virtual QLocale* setupTranslators();
  virtual QString  version() const;

  bool                simulator;
  QApplication&       app;
  ConfigManager*      cfg;
  QLocale*            locale;
  DBConnection*       conn;  
  QString             appName;
  QString             groupID;
  QString             langDir;
  QBasicTimer         timer;

  friend class Core;
  friend class Config;
  friend class KernelCreator;
  };
#endif // KERNEL_H
