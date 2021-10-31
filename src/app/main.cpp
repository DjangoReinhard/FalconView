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

//  a.setFont(QFont("Noto Sans", 15));  // needed with Qt > 6xx
  if (args.length() > 1) iniFileName = args[1];
  Core appCore(iniFileName, "FalconView");

  qDebug() << "current locale settings - lang: " << curLocale.language()
           << "\tcountry: " << curLocale.country()
           << "\tname: " << curLocale.name();
  qDebug() << "syslocale.name: " << sysLocale.name();
  qDebug() << "locale messages found: " << ok;
  a.installTranslator(&translator);
  MainWindow w;

#ifdef REDNOSE
  QString name = "foo";
  QString   gc = "";
  QString ttFN = "bar";

  if (args.length() > 1) name = args[1];
  if (args.length() > 2) ttFN = args[2];

  setenv("INI_FILE_NAME", name.toStdString().c_str(), 1);
  QFileInfo    fi(name);
  LcProperties ir(fi.absoluteFilePath());

  /*
   * read tool table filename from ini
   */
  ttFN = ir.value("EMCIO", "TOOL_TABLE").toString();
  QFile fTT(ttFN);

  if (!fTT.exists()) fTT.setFileName(fi.dir().absolutePath() + "/" + ttFN);
  ToolTable tt(fTT.fileName());
  if (args.length() > 3) gc = args[3];
  QFile gcFile(gc);

  if (gcFile.exists()) {
     LCInterface lcIF(ir, tt);
     CanonIF     ci(ir, tt);

     ci.setTraverseColor(QColor(Qt::cyan));
     ci.setFeedColor(QColor(Qt::white));
     ci.setLimitsColor(QColor(150, 255, 150));
     lcIF.setupToolTable();
     qDebug() << "gonna parse gcode-file: " << gcFile.fileName();
     QTime       start = QTime::currentTime();

     lcIF.parseInline(gcFile.fileName());
     QTime end  = QTime::currentTime();
     long delta = end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay();

     qDebug() << "parsing of " << gcFile.fileName() << " took: " << delta << "ms";

//     w.updatePath();
     }
#endif
  w.show();

  return a.exec();
  }
