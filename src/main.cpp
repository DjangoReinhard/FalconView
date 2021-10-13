#include <mainwindow.h>
#include <configmgr.h>
#include <LCInter.h>
#include <canonif.h>
#include <DocumentCommon.h>
#include <QApplication>
#include <QTranslator>
#include <QTime>
#include <QDebug>


int main(int argc, char *argv[]) {
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
  QStringList args = QCoreApplication::arguments();
  Config      cfg;

//  a.setFont(QFont("Noto Sans", 15));  // needed with Qt > 6xx
  if (args.length() > 1) cfg.setIniFile(args[1]);
  cfg.value("whatEver");
  qDebug() << "current locale settings - lang: " << curLocale.language()
           << "\tcountry: " << curLocale.country()
           << "\tname: " << curLocale.name();
  qDebug() << "syslocale.name: " << sysLocale.name();
  qDebug() << "locale messages found: " << ok;
  a.installTranslator(&translator);
  MainWindow w;
  QString   gc = "";
  QString name = "foo";
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

     w.doc3D->setObjects(CanonIF().toolPath());
     w.doc3D->setLimits(ir);
     }
  w.show();

  return a.exec();
  }
