#ifndef KERNEL_H
#define KERNEL_H
#include <KernelInterface.h>
#include <QObject>
#include <QBasicTimer>
#include <QLocale>
#include <configmgr.h>
class DBHelper;
class DBConnection;
class SysEvent;


class Kernel : public QObject , public virtual KernelInterface
{
  Q_OBJECT
public:
  virtual int            axisMask() const override;
  virtual ConfigManager* config() const override;
  virtual ConfigManager* config() override;
  virtual DBConnection*  databaseConnection() override;
  virtual QString        fileName4(const QString& fileID) const override;
  virtual void           initialize(DBHelper& dbAssist) override;
  virtual bool           isSimulator() const override;
  virtual QLocale        locale() const override;
  virtual void           logSysEvent(const QString& msg) override;
  virtual void           logSysEvent(const SysEvent& se) override;
  virtual void           processAppArgs(const QStringList& args) override;
  virtual QLocale*       setupTranslators() override;
  virtual QString        version() const override;

protected:
  explicit Kernel(QApplication& app, const QString& appName, const QString& groupID);
  virtual ~Kernel() = default;

  bool                simulator;
  QApplication&       app;
  ConfigManager*      cfg;
  QLocale*            curLocale;
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
