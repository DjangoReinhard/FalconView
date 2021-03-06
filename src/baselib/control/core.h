#ifndef CORE_H
#define CORE_H
#include <QString>
#include <applicationmode.h>
class KernelInterface;
class KernelCreator;
class DBConnection;
class DBHelper;
class QLocale;
class QApplication;


class Core
{
public:
  explicit Core();
  explicit Core(QApplication& app, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  virtual ~Core() = default;

  virtual void    riseError(const QString& msg);

  int             axisMask() const;
  DBConnection*   databaseConnection();
  QString         fileName4(const QString& fileID) const;
  bool            isSimulator() const;
  QString         languagePrefix() const;
  QLocale         locale() const;
  bool            move2Backup(const QString& fileName);
  void            setAppMode(ApplicationMode m);
  void            showAllButCenter(bool visible);
  bool            showHelpAtPageChange() const;

  static void     setKernelCreator(KernelCreator* kc);

protected:
  explicit Core(void* p); // for plugins
  static KernelInterface* kernel;
  static KernelCreator*      kc;
  static int                 checked;
  friend class Config;
  friend class AbstractCenterWidget;
  friend class PluginPageFactory;
  };
#endif
