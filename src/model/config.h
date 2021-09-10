#ifndef CONFIG_H
#define CONFIG_H
#include <valuemanager.h>
#include <QString>
#include <QSettings>
class QColor;
class QFont;
class QFile;


class Config
{
public:    
  static const int guiSettingEntries;
  static const QString guiSettings[];

  QColor getBackground(int index);
  QColor getForeground(int index);
  QFont getFont(int index);
  void setBackground(int index, const QColor& color);
  void setForeground(int index, const QColor& color);
  void setFont(int index, const QFont& font);
  QVariant value(const QString& key, const QVariant& defaultValue = QVariant());
  void setValue(const QString& key, const QVariant& value);

protected:
  class ConfigManager {
  public:
    ConfigManager();

    QColor getBackground(int index);
    QColor getForeground(int index);
    QFont getFont(int index);
    void setBackground(int index, const QColor& color);
    void setForeground(int index, const QColor& color);
    void setFont(int index, const QFont& font);
    QVariant value(const QString& key, const QVariant& defaultValue = QVariant());
    void setValue(const QString& key, const QVariant& value);

  protected:
    void initialize();
    void load();
    ValueManager vm;
    QSettings settings;
    };

  ConfigManager* getInstance();

private:
  static ConfigManager* instance;
  };
#endif // CONFIG_H
