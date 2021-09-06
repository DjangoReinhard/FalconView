#include <config.h>
#include <QVariant>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QDir>
#include <QDebug>


Config::Config(const QString& fileName) {
  file = new QFile(QDir::homePath() + "/." + fileName);
  if (file && file->exists()) load();
  else                        initialize();
  }


Config::~Config() {
  delete file;
  }


void Config::initialize() {
  QVariant v;

  v = QColor(Qt::white);
  for (int i=0; i < guiSettingEntries; ++i) vm.setValue("cfgBg" + guiSettings[i], v);
  v = QColor(Qt::black);
  for (int i=0; i < guiSettingEntries; ++i) vm.setValue("cfgFg" + guiSettings[i], v);
  v = QFont("Hack", 12);
  for (int i=0; i < guiSettingEntries; ++i) vm.setValue("cfgF" + guiSettings[i], v);
  }


QColor Config::getBackground(int index) {
  if (index < 0 || index >= guiSettingEntries)  return QColor(Qt::white);
  return vm.getValue("cfgBg" + guiSettings[index]).value<QColor>();
  }


QColor Config::getForeground(int index) {
  if (index < 0 || index >= guiSettingEntries)  return QColor(Qt::black);
  return vm.getValue("cfgFg" + guiSettings[index]).value<QColor>();
  }


QFont Config::getFont(int index) {
  if (index < 0 || index >= guiSettingEntries)  return QFont();
  return vm.getValue("cfgF" + guiSettings[index]).value<QFont>();
  }


void Config::load() {
  if (!file || !file->exists()) return;
  if (file->open(QIODevice::ReadOnly | QIODevice::Text)) {
     QTextStream in(file);
     QString line = in.readLine();

     while (!line.isNull()) {
           processConfigLine(line);
           line = in.readLine();
           }
     file->close();
     }
  }


void Config::processConfigLine(const QString& line) {
  qDebug() << "config: " << line;
  }


void Config::setBackground(int index, const QColor& color) {
  if (index < 0 || index >= guiSettingEntries)  return;
  vm.setValue("cfgBg" + guiSettings[index], color);
  }


void Config::setForeground(int index, const QColor& color) {
  if (index < 0 || index > guiSettingEntries)  return;
  vm.setValue("cfgFg" + guiSettings[index], color);
  }


void Config::setFont(int index, const QFont& font) {
  if (index < 0 || index > guiSettingEntries)  return;
  vm.setValue("cfgF" + guiSettings[index], font);
  }


void Config::store() {
  if (file && file->open(QIODevice::WriteOnly | QIODevice::Text)) {
     QTextStream out(file);

     for (int i=0; i < guiSettingEntries; ++i) {
         out << guiSettings[i] << "\t"
             << "bg = " << vm.getValue("cfgBg" + guiSettings[i]).toString() << ", "
             << "fg = " << vm.getValue("cfgFg" + guiSettings[i]).toString() << ", "
             << "f = "  << vm.getValue("cfgF"  + guiSettings[i]).toString() << "\n";
         }
     file->close();
     }
  }


const int Config::guiSettingEntries = 12;
const QString Config::guiSettings[] = {
  "ActCodes"
, "DroAbs"
, "DroDtg"
, "DroRel"
, "DroTitle"
, "Feed"
, "Filename"
, "GCode"
, "Speed"
, "ToolDesc"
, "ToolNum"
, "ToolNext"
  };
