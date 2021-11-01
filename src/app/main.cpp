#include <mainwindow.h>
#include <core.h>
#include <QApplication>
#include <QTranslator>
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

#ifdef USE_QT_V6xx
  // set default font for all gui elements. Needed with Qt > 6xx
  a.setFont(QFont("Noto Sans", 15));
#endif
  if (args.length() > 1) iniFileName = args[1];
  Core appCore(iniFileName, "FalconView");

//  qDebug() << "current locale settings - lang: " << curLocale.language()
//           << "\tcountry: " << curLocale.country()
//           << "\tname: " << curLocale.name();
//  qDebug() << "syslocale.name: " << sysLocale.name();
  qDebug() << "locale messages found: " << ok;
  a.installTranslator(&translator);
  MainWindow w;

  w.show();

  return a.exec();
  }
