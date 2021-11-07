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
 : settings(QSettings::UserScope, group, appName)
 , lastIndex(static_cast<Config::GuiElem>(Config::GuiElem::LastKey)) {
  initialize();
  }


void ConfigManager::initialize() {
  for (int i=0; i < lastIndex; ++i) {
      QString  k = QString("cfgBg") + geToString(i);
      QVariant v = settings.value(k, QColor(Qt::white));

//      qDebug() << "config key: " << k;
//      qDebug() << "background color: #" << QString("#%1").arg(v.value<QColor>().rgba(), 0, 16);
      vm.setValue(k, v);

      k = QString("cfgFg") + geToString(i);
      v = settings.value(k, QColor(Qt::black));
//      qDebug() << "config key: " << k;
//      qDebug() << "foreground color: #" << QString("#%1").arg(v.value<QColor>().rgba(), 0, 16);
      vm.setValue(k, v);

      k = QString("cfgF") + geToString(i);
      v = settings.value(k, QFont("Hack", 12));
//      qDebug() << "config key: " << k;
//      qDebug() << "font: " << v.value<QFont>().key();
      vm.setValue(k, v);
      }
  }


QColor ConfigManager::getBackground(int index) {
  if (index < 0 || index >= lastIndex)  return QColor(Qt::white);
  return vm.getValue("cfgBg" + geToString(index)).value<QColor>();
  }


QColor ConfigManager::getForeground(int index) {
  if (index < 0 || index >= lastIndex)  return QColor(Qt::black);
  return vm.getValue("cfgFg" + geToString(index)).value<QColor>();
  }


QFont ConfigManager::getFont(int index) {
  if (index < 0 || index >= lastIndex)  return QFont();
  return vm.getValue("cfgF" + geToString(index)).value<QFont>();
  }


QVariant ConfigManager::value(const QString& key, const QVariant& defaultValue) const {
  return settings.value(key, defaultValue);
  }


void ConfigManager::setBackground(int index, const QColor& color) {
  if (index < 0 || index >= lastIndex)  return;
  QString key = QString("cfgBg") + geToString(index);

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void ConfigManager::setForeground(int index, const QColor& color) {
  if (index < 0 || index >= lastIndex)  return;
  QString key = QString("cfgFg") + geToString(index);

  vm.setValue(key, color);
  settings.setValue(key, color);
  }


void ConfigManager::setFont(int index, const QFont& font) {
  if (index < 0 || index >= lastIndex)  return;
  QString key = QString("cfgF") + geToString(index);

  vm.setValue(key, font);
  settings.setValue(key, font);
  }


void ConfigManager::setValue(const QString& key, const QVariant& value) {
  settings.setValue(key, value);
  }

#define asString( name ) # name
// sync with Config::GuiElem
QString ConfigManager::geToString(int i) {
  switch (static_cast<Config::GuiElem>(i)) {
    case Config::GuiElem::ActCodes: return asString(ActCodes);
    case Config::GuiElem::DroAbs:   return asString(DroAbs);
    case Config::GuiElem::DroDtg:   return asString(DroDtg);
    case Config::GuiElem::DroRel:   return asString(DroRel);
    case Config::GuiElem::DroTitle: return asString(DroTitle);
    case Config::GuiElem::EdLinNum: return asString(EdLinNum);
    case Config::GuiElem::LineHL:   return asString(LineHL);
    case Config::GuiElem::Feed:     return asString(Feed);
    case Config::GuiElem::Filename: return asString(Filename);
    case Config::GuiElem::FixFrame: return asString(FixFrame);
    case Config::GuiElem::FixTitle: return asString(FixTitle);
    case Config::GuiElem::Fixture:  return asString(Fixture);
    case Config::GuiElem::GCode:    return asString(GCode);
    case Config::GuiElem::Speed:    return asString(Speed);
    case Config::GuiElem::ToolDesc: return asString(ToolDesc);
    case Config::GuiElem::ToolNext: return asString(ToolNext);
    case Config::GuiElem::ToolNum:  return asString(ToolNum);
    default: break;
    }
  return QString();
  }
