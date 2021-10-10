#ifndef CONFIG_H
#define CONFIG_H
#include <valuemanager.h>
#include <lcproperties.h>
#include <tooltable.h>
#include <QString>
#include <QSettings>
class QColor;
class QFont;
class QFile;


class Config
{
public:    
  static const int     guiSettingEntries;
  static const QString guiSettings[];

  QColor    getBackground(int index);
  QColor    getForeground(int index);
  QFont     getFont(int index);
  QVariant  getProperty(const QString& groupID, const QString& name);
  ToolEntry getTool(int number);
  void      setBackground(int index, const QColor& color);
  void      setForeground(int index, const QColor& color);
  void      setFont(int index, const QFont& font);
  void      setIniFile(const QString& fileName);
  QVariant  value(const QString& key, const QVariant& defaultValue = QVariant());
  void      setValue(const QString& key, const QVariant& value);

protected:
  class ConfigManager {
    friend class Config;

    ConfigManager();

    QColor       getBackground(int index);
    QColor       getForeground(int index);
    QFont        getFont(int index);
    QVariant     getProperty(const QString& groupID, const QString& name);
    ToolEntry    getTool(int number);
    void         setBackground(int index, const QColor& color);
    void         setForeground(int index, const QColor& color);
    void         setFont(int index, const QFont& font);
    void         setIniFile(const QString& fileName);
    QVariant     value(const QString& key, const QVariant& defaultValue = QVariant());
    void         setValue(const QString& key, const QVariant& value);
    void         initialize();
    void         load();

    QString      iniFileName;
    LcProperties properties;
    ToolTable    tools;
    ValueManager vm;
    QSettings    settings;
    };

  ConfigManager* getInstance();

private:
  static ConfigManager* instance;
  };
#endif // CONFIG_H
