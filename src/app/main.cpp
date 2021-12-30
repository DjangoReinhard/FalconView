#include <mainwindow.h>
#include <testmain.h>
#include <falconviewdb.h>
#include <guicore.h>
#include <guikernelcreator.h>
#include <QCoreApplication>
#include <QApplication>
#include <QFileInfo>
#include <QStyleFactory>
#include <QTranslator>
#include <QKeySequence>
#include <QDebug>


static QString findIni(const QStringList& args) {
  int mx = args.size();

  for (int i=0; i < mx; ++i) {
      if (args.at(i) == "-ini") {
         if ((i+1) < mx) return args.at(i+1);
         }
      }
  return QString();
  }


int main(int argc, char *argv[]) {
  try {
      QTranslator       translator;
      QApplication      a(argc, argv);
      QLocale           sysLocale;
      QLocale::Language lang    = sysLocale.language();
      QLocale::Country  country = sysLocale.country();
      QLocale           curLocale(lang, country);
      bool              ok = translator.load(curLocale
                                          , "FalconView"
                                          , "_"
                                          , "../FalconView/src/i18n");
      QStringList args        = QCoreApplication::arguments();
      QString     iniFileName = findIni(args);
      QStringList sl          = QStyleFactory::keys();

      a.installTranslator(&translator);
//      qDebug() << "application arguments: " << args;
      qDebug() << "locale messages found: " << ok;
      qDebug() << "language:" << lang;
      qDebug() << "country:" << country;
      qDebug() << "syslocale:" << sysLocale.name() << "\tcurrent locale:" << curLocale.name();
      qDebug() << "gonna use ini-file: " << iniFileName;
      qDebug() << "check for styles ...";
      for (const QString& s : sl) {
          qDebug() << "available style: " << s;
          }
      qDebug() << "style check done ...";
      QFileInfo ifi(iniFileName);

      if (!ifi.exists() || ifi.size() < 1) throw std::invalid_argument("invalid or not existant inifile");
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
      // set default font for all gui elements. Needed with Qt > 6xx
      a.setFont(QFont("Noto Sans", 15));
#endif
#ifdef REDNOSE
      FalconViewDB dbHelper;
      GuiCore      appCore(iniFileName, "FalconView", dbHelper);

      appCore.checkBE();
      appCore.mainWindow()->show();
#else
      GuiCore::setKernelCreator(new GuiKernelCreator());
      FalconViewDB dbHelper;
      GuiCore      appCore(iniFileName, "FalconView", dbHelper);
      TestMain*    mainWindow = new TestMain(QCoreApplication::applicationDirPath());

      appCore.setMainWindow(mainWindow);

      mainWindow->show();
#endif
      int rv = a.exec();

//      qDebug() << "left event loop with rv ==" << rv;

      return rv;
      }
  catch (const QString& s) {
      qDebug() << s;
      }
  catch (const std::exception& e) {
      qDebug() << e.what();
      }
  }
