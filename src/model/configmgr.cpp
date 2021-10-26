#include <configmgr.h>
#include <configacc.h>
#include <core.h>
#include <QVariant>
#include <QColor>
#include <QFont>
#include <QFile>
#include <QDir>
#include <QDebug>


ConfigManager::ConfigManager(const QString& appName, const QString& group)
 : settings(QSettings::UserScope, group, appName) {
  initialize();
  }


void ConfigManager::initialize() {
  for (int i=0; i < Config::guiSettingEntries; ++i) {
      QString  k = QString("cfgBg") + Config::guiSettings[i];
      QVariant v = settings.value(k, QColor(Qt::white));

//      qDebug() << "config key: " << k;
//      qDebug() << "background color: #" << QString("#%1").arg(v.value<QColor>().rgba(), 0, 16);
      vm.setValue(k, v);

      k = QString("cfgFg") + Config::guiSettings[i];
      v = settings.value(k, QColor(Qt::black));
//      qDebug() << "config key: " << k;
//      qDebug() << "foreground color: #" << QString("#%1").arg(v.value<QColor>().rgba(), 0, 16);
      vm.setValue(k, v);

      k = QString("cfgF") + Config::guiSettings[i];
      v = settings.value(k, QFont("Hack", 12));
//      qDebug() << "config key: " << k;
//      qDebug() << "font: " << v.value<QFont>().key();
      vm.setValue(k, v);
      }
  }


QColor ConfigManager::getBackground(int index) {
  if (index < 0 || index >= Config::guiSettingEntries)  return QColor(Qt::white);
  return vm.getValue("cfgBg" + Config::guiSettings[index]).value<QColor>();
  }


QColor ConfigManager::getForeground(int index) {
  if (index < 0 || index >= Config::guiSettingEntries)  return QColor(Qt::black);
  return vm.getValue("cfgFg" + Config::guiSettings[index]).value<QColor>();
  }


QFont ConfigManager::getFont(int index) {
  if (index < 0 || index >= Config::guiSettingEntries)  return QFont();
  return vm.getValue("cfgF" + Config::guiSettings[index]).value<QFont>();
  }


QVariant ConfigManager::value(const QString& key, const QVariant& defaultValue) const {
  return settings.value(key, defaultValue);
  }


void ConfigManager::setBackground(int index, const QColor& color) {
  if (index < 0 || index >= Config::guiSettingEntries)  return;
  QString key = QString("cfgBg") + Config::guiSettings[index];

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void ConfigManager::setForeground(int index, const QColor& color) {
  if (index < 0 || index > Config::guiSettingEntries)  return;
  QString key = QString("cfgFg") + Config::guiSettings[index];

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void ConfigManager::setFont(int index, const QFont& font) {
  if (index < 0 || index > Config::guiSettingEntries)  return;
  QString key = QString("cfgF") + Config::guiSettings[index];

  vm.setValue(key, font);
  settings.setValue(key, font);
  }


void ConfigManager::setValue(const QString& key, const QVariant& value) {
  settings.setValue(key, value);
  }
