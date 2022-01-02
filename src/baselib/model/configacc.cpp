#include <configacc.h>
#include <core.h>
#include <kernel.h>
#include <QColor>
#include <QFont>

Config::Config() {
  if (!Config::cfg) Config::cfg = Core().kernel->cfg;
  assert(Config::cfg);
  }


Config::Config(void* pFromOuterAddressSpace) {
  if (!Config::cfg) Config::cfg = (ConfigManager*)pFromOuterAddressSpace;
  }


QColor Config::getBackground(GuiElem key) const {
  return cfg->getBackground(key);
  }


QColor Config::getForeground(GuiElem key) const {
  return cfg->getForeground(key);
  }


QFont Config::getFont(GuiElem key) const {
  return cfg->getFont(key);
  }


void Config::beginGroup(const QString &name) {
  cfg->settings.beginGroup(name);
  }


void Config::endGroup() {
  cfg->settings.endGroup();
  }


QVariant Config::value(const QString& key, const QVariant& defaultValue) const {
  return cfg->value(key, defaultValue);
  }


void Config::setBackground(GuiElem key, const QColor& color) {
  cfg->setBackground(key, color);
  }


void Config::setForeground(GuiElem key, const QColor& color) {
  cfg->setForeground(key, color);
  }


void Config::setFont(GuiElem key, const QFont& font) {
  cfg->setFont(key, font);
  }


void Config::setValue(const QString& key, const QVariant& value) {
  cfg->setValue(key, value);
  }


QString Config::nameOf(GuiElem key) const {
  return cfg->geToString(key);
  }

ConfigManager* Config::cfg = nullptr;
