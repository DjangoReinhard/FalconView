#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QDebug>


int main(int argc, char *argv[]) {
  QTranslator translator;
  QApplication a(argc, argv);
  bool ok = translator.load(QLocale(QLocale::German, QLocale::Germany)
                          , "QtScreen"
                          , "_"
                          , "../QtScreen");

  qDebug() << "locale messages found: " << ok;
  a.installTranslator(&translator);
  MainWindow w;

  w.show();

  return a.exec();
  }
