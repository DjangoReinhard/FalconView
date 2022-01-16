#ifndef KERNELINTERFACE_H
#define KERNELINTERFACE_H
#include <QObject>
class ConfigManager;
class DBConnection;
class DBHelper;
class SysEvent;
class QString;
class QLocale;
class QStringList;


class KernelInterface : public QObject
{
  Q_OBJECT
public:
  virtual int            axisMask() const                        = 0;
  virtual ConfigManager* config() const                          = 0;
  virtual ConfigManager* config()                                = 0;
  virtual DBConnection*  databaseConnection()                    = 0;
  virtual QLocale        locale() const                          = 0;
  virtual void           logSysEvent(const QString& msg)         = 0;
  virtual void           logSysEvent(const SysEvent& se)         = 0;
  virtual void           initialize(DBHelper& dbAssist)          = 0;
  virtual bool           isSimulator() const                     = 0;
  virtual QString        fileName4(const QString& fileID) const  = 0;
  virtual void           processAppArgs(const QStringList& args) = 0;
  virtual QLocale*       setupTranslators()                      = 0;
  virtual QString        version() const                         = 0;
  };
#endif // KERNELINTERFACE_H
