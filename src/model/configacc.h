#ifndef CONFIG_H
#define CONFIG_H
#include <valuemanager.h>
#include <lcproperties.h>
#include <tooltable.h>
#include <QString>
#include <QSettings>
class ConfigManager;
class QColor;
class QFont;
class QFile;


class Config
{
public:
  static const int     guiSettingEntries;
  static const QString guiSettings[];

  QColor           getBackground(int index);
  QColor           getForeground(int index);
  QFont            getFont(int index);
  void             setBackground(int index, const QColor& color);
  void             setForeground(int index, const QColor& color);
  void             setFont(int index, const QFont& font);
  QVariant         value(const QString& key, const QVariant& defaultValue = QVariant()) const;
  void             setValue(const QString& key, const QVariant& value);
  };
#endif // CONFIG_H
