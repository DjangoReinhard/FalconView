#include <mainwindow.h>
#include <config.h>
#include <QApplication>
#include <QTranslator>
#include <QDebug>


int main(int argc, char *argv[]) {
  QGuiApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::Ceil);
  QTranslator       translator;
  QApplication      a(argc, argv);
  QLocale           sysLocale;
  QLocale::Language lang    = sysLocale.language();
  QLocale::Country  country = sysLocale.country();
  QLocale           curLocale(lang, country);
  bool              ok = translator.load(curLocale
                                       , "QtUi"
                                       , "_"
                                       , "../QtUi/src/i18n");

  qDebug() << "current locale settings - lang: " << curLocale.language()
           << "\tcountry: " << curLocale.country()
           << "\tname: " << curLocale.name();
  qDebug() << "syslocale.name: " << sysLocale.name();
  qDebug() << "locale messages found: " << ok;
  a.installTranslator(&translator);
  MainWindow w;

  w.show();

  return a.exec();
  }
