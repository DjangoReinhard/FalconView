#include <mainwindow.h>
#include <falconviewdb.h>
#include <core.h>
#include <QApplication>
#include <QTranslator>
#include <QKeySequence>
#include <QDebug>


int main(int argc, char *argv[]) {
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
  QStringList args = QCoreApplication::arguments();
  QString iniFileName = getenv("INI_FILE_NAME");

  qDebug() << "locale messages found: " << ok;
#if QT_VERSION >= QT_VERSION_CHECK(6, 0, 0)
  // set default font for all gui elements. Needed with Qt > 6xx
  a.setFont(QFont("Noto Sans", 15));
#endif
  if (args.length() > 1) iniFileName = args[1];
  FalconViewDB dbHelper("FalconView");
  Core appCore(iniFileName, "FalconView", dbHelper);

  a.installTranslator(&translator);
  MainWindow w;

  appCore.setMainWindow(&w);
  appCore.checkBE();
  w.show();

  int rv = a.exec();

  qDebug() << "left event loop with rv ==" << rv;

  return rv;
  }
