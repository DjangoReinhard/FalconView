#ifndef CORE_H
#define CORE_H
#include <QString>
#include <applicationmode.h>
class Kernel;
class KernelCreator;
class DBConnection;
class DBHelper;
class QLocale;


class Core
{
public:
  Core(const QString& iniFileName, const QString& appName, DBHelper& dbAssist, const QString& group = "SRD");
  Core() {}

  virtual int     axisMask() const;
  virtual QString fileName4(const QString& fileID) const;
  DBConnection*   databaseConnection();
  void            help4Keyword(const QString& keyWord);
  QString         languagePrefix() const;
  QLocale         locale() const;
  bool            isSimulator() const;
  bool            move2Backup(const QString& fileName);
  void            riseError(const QString& msg);
  void            showAllButCenter(bool visible);
  bool            showHelpAtPageChange() const;
  void            setLocale(const QLocale& l);
  void            setAppMode(ApplicationMode m);
  void            showHelp();
  static void     setKernelCreator(KernelCreator* kc);

protected:
  Kernel*               core();
  const Kernel*         core() const;
  static Kernel*        kernel;
  static KernelCreator* kc;
  static int            checked;
  friend class Config;
  };
#endif
