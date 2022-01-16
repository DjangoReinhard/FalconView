#include <kernel.h>
#include <sysevent.h>
#include <QApplication>
#include <QTranslator>
#include <QDir>
#include <QDebug>


Kernel::Kernel(QApplication& app, const QString& appName, const QString& groupID)
 : simulator(false)
 , app(app)
 , cfg(new ConfigManager(appName, groupID))
 , curLocale(nullptr)
 , conn(nullptr)
 , appName(appName)
 , groupID(groupID) {
  }


int Kernel::axisMask() const {
  return 0;
  }


ConfigManager* Kernel::config() const {
  return cfg;
  }


ConfigManager* Kernel::config() {
  return cfg;
  }


DBConnection*  Kernel::databaseConnection() {
  return conn;
  }


QString Kernel::fileName4(const QString&) const {
  return QString();
  }


void Kernel::initialize(DBHelper&) {
  QDir        dir(QCoreApplication::applicationDirPath());

  dir.cd("i18n");
  langDir = dir.absolutePath();
  processAppArgs(app.arguments());
  curLocale = setupTranslators();
  }


bool Kernel::isSimulator() const {
  return false;
  }


QLocale Kernel::locale() const {
  return *curLocale;
  }


void Kernel::logSysEvent(const QString &msg) {
  logSysEvent(SysEvent(msg));
  }


void Kernel::logSysEvent(const SysEvent& se) {
  qDebug() << "system event" << se.type() << ":" << se.what() << " at:" << se.when();
  }


void Kernel::processAppArgs(const QStringList& args) {
  int mx = args.size();

  for (int i=0; i < mx; ++i) {
      if (args[i] == "-i18n" && mx > (i+1)) {
         langDir = args[++i];
         }
      }
  }


QLocale* Kernel::setupTranslators() {
  QLocale           sysLocale;
  QLocale::Language lang    = sysLocale.language();
  QLocale::Country  country = sysLocale.country();
  QLocale*          curLocale = new QLocale(lang, country);
  QDir              i18nDir(langDir);
  const auto        entryList = i18nDir.entryList(QDir::Files);
  bool              ok;

  qDebug() << "language:" << lang;
  qDebug() << "country:" << country;
  qDebug() << "syslocale:" << sysLocale.name() << "\tcurrent locale:" << curLocale->name();

  for (const QString& s : entryList) {
      QString      name = s.mid(0, s.size() - 9);
      QTranslator* tr   = new QTranslator();

      ok = tr->load(*curLocale, name, "_", i18nDir.absolutePath());

      qDebug() << "translation-messages:" << name << (ok ? "loaded" : "FAILED to load");

      if (ok) app.installTranslator(tr);
      else    delete tr;
      }
  return curLocale;
  }


QString Kernel::version() const {
  return "0.1";
  }
