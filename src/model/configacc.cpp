#include <configacc.h>
#include <core.h>
#include <core_p.h>


QColor Config::getBackground(GuiElem key) const {
  return Core().core()->cfg.getBackground(key);
  }


QColor Config::getForeground(GuiElem key) const {
  return Core().core()->cfg.getForeground(key);
  }


QFont Config::getFont(GuiElem key) const {
  return Core().core()->cfg.getFont(key);
  }


QVariant Config::value(const QString& key, const QVariant& defaultValue) const {
  return Core().core()->cfg.value(key, defaultValue);
  }


void Config::setBackground(GuiElem key, const QColor& color) {
  Core().core()->cfg.setBackground(key, color);
  }


void Config::setForeground(GuiElem key, const QColor& color) {
  Core().core()->cfg.setForeground(key, color);
  }


void Config::setFont(GuiElem key, const QFont& font) {
  Core().core()->cfg.setFont(key, font);
  }


void Config::setValue(const QString& key, const QVariant& value) {
  Core().core()->cfg.setValue(key, value);
  }


QString Config::nameOf(GuiElem key) const {
  return Core().core()->cfg.geToString(key);
  }
