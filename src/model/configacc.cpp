#include <configacc.h>
#include <core.h>
#include <core_p.h>


QColor Config::getBackground(int index) {
  return Core().core()->cfg.getBackground(index);
  }


QColor Config::getForeground(int index) {
  return Core().core()->cfg.getForeground(index);
  }


QFont Config::getFont(int index) {
  return Core().core()->cfg.getFont(index);
  }


QVariant Config::value(const QString& key, const QVariant& defaultValue) const {
  return Core().core()->cfg.value(key, defaultValue);
  }


void Config::setBackground(int index, const QColor& color) {
  Core().core()->cfg.setBackground(index, color);
  }


void Config::setForeground(int index, const QColor& color) {
  Core().core()->cfg.setForeground(index, color);
  }


void Config::setFont(int index, const QFont& font) {
  Core().core()->cfg.setFont(index, font);
  }


void Config::setValue(const QString& key, const QVariant& value) {
  Core().core()->cfg.setValue(key, value);
  }


const int      Config::guiSettingEntries = 12;
const QString  Config::guiSettings[]     = {
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
