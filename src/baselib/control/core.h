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
  explicit Core();
  explicit Core(const QString& iniFileName, const QString& appName, const QLocale& locale, DBHelper& dbAssist, const QString& group = "SRD");
  virtual ~Core() = default;

  virtual void    riseError(const QString& msg);

  int             axisMask() const;
  DBConnection*   databaseConnection();
  QString         fileName4(const QString& fileID) const;
  bool            isSimulator() const;
  void            help4Keyword(const QString& keyWord);
  QString         languagePrefix() const;
  QLocale         locale() const;
  bool            move2Backup(const QString& fileName);
  void            setAppMode(ApplicationMode m);
  void            showAllButCenter(bool visible);
  void            showHelp();
  bool            showHelpAtPageChange() const;

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
