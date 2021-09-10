#include <config.h>
#include <QVariant>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QDir>
#include <QDebug>


QColor Config::getBackground(int index) {
  return getInstance()->getBackground(index);
  }


QColor Config::getForeground(int index) {
  return getInstance()->getForeground(index);
  }


QFont Config::getFont(int index) {
  return getInstance()->getFont(index);
  }


QVariant Config::value(const QString& key, const QVariant& defaultValue) {
  return getInstance()->value(key, defaultValue);
  }


void Config::setBackground(int index, const QColor& color) {
  getInstance()->setBackground(index, color);
  }


void Config::setForeground(int index, const QColor& color) {
  getInstance()->setForeground(index, color);
  }


void Config::setFont(int index, const QFont& font) {
  getInstance()->setFont(index, font);
  }


void Config::setValue(const QString& key, const QVariant& value) {
  getInstance()->setValue(key, value);
  }


Config::ConfigManager* Config::getInstance() {
  if (!instance) instance = new ConfigManager();
  return instance;
  }


Config::ConfigManager::ConfigManager()
 : settings(QSettings::UserScope, "SRD", "QtUi") {
  initialize();
  }


void Config::ConfigManager::initialize() {
  for (int i=0; i < guiSettingEntries; ++i) {
      QString  k = QString("cfgBg") + guiSettings[i];
      QVariant v = settings.value(k, QColor(Qt::white));

//      qDebug() << "config key: " << k;
//      qDebug() << "background color: #" << QString("#%1").arg(v.value<QColor>().rgba(), 0, 16);
      vm.setValue(k, v);

      k = QString("cfgFg") + guiSettings[i];
      v = settings.value(k, QColor(Qt::black));
//      qDebug() << "config key: " << k;
//      qDebug() << "foreground color: #" << QString("#%1").arg(v.value<QColor>().rgba(), 0, 16);
      vm.setValue(k, v);

      k = QString("cfgF") + guiSettings[i];
      v = settings.value(k, QFont("Hack", 12));
//      qDebug() << "config key: " << k;
//      qDebug() << "font: " << v.value<QFont>().key();
      vm.setValue(k, v);
      }
  }


QColor Config::ConfigManager::getBackground(int index) {
  if (index < 0 || index >= guiSettingEntries)  return QColor(Qt::white);
  return vm.getValue("cfgBg" + guiSettings[index]).value<QColor>();
  }


QColor Config::ConfigManager::getForeground(int index) {
  if (index < 0 || index >= guiSettingEntries)  return QColor(Qt::black);
  return vm.getValue("cfgFg" + guiSettings[index]).value<QColor>();
  }


QFont Config::ConfigManager::getFont(int index) {
  if (index < 0 || index >= guiSettingEntries)  return QFont();
  return vm.getValue("cfgF" + guiSettings[index]).value<QFont>();
  }


QVariant Config::ConfigManager::value(const QString& key, const QVariant& defaultValue) {
  return settings.value(key, defaultValue);
}


void Config::ConfigManager::setBackground(int index, const QColor& color) {
  if (index < 0 || index >= guiSettingEntries)  return;
  QString key = QString("cfgBg") + guiSettings[index];

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void Config::ConfigManager::setForeground(int index, const QColor& color) {
  if (index < 0 || index > guiSettingEntries)  return;
  QString key = QString("cfgFg") + guiSettings[index];

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void Config::ConfigManager::setFont(int index, const QFont& font) {
  if (index < 0 || index > guiSettingEntries)  return;
  QString key = QString("cfgF") + guiSettings[index];

  vm.setValue(key, font);
  settings.setValue(key, font);
  }


void Config::ConfigManager::setValue(const QString& key, const QVariant& value) {
  settings.setValue(key, value);
  }


Config::ConfigManager* Config::instance          = nullptr;
const int              Config::guiSettingEntries = 12;
const QString          Config::guiSettings[]     = {
  "ActCodes"        /*  0 */
, "DroAbs"          /*  1 */
, "DroDtg"          /*  2 */
, "DroRel"          /*  3 */
, "DroTitle"        /*  4 */
, "Feed"            /*  5 */
, "Filename"        /*  6 */
, "GCode"           /*  7 */
, "Speed"           /*  8 */
, "ToolDesc"        /*  9 */
, "ToolNum"         /* 10 */
, "ToolNext"        /* 11 */
  };
