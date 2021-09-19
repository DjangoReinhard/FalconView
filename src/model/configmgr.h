#ifndef CONFIGMGR_H
#define CONFIGMGR_H
#include <QSettings>
#include <QString>
#include <QColor>
#include <QFont>
#include <valuemanager.h>
class ToolEntry;

class ConfigManager
{
public:
  ConfigManager(const QString& appName = "Config-Manager", const QString& group = "SRD");

  QColor           getBackground(int index);
  QColor           getForeground(int index);
  QFont            getFont(int index);
//  QVariant         getProperty(const QString& groupID, const QString& name);
//  const ToolEntry* getTool(int number);
  void             setBackground(int index, const QColor& color);
  void             setForeground(int index, const QColor& color);
  void             setFont(int index, const QFont& font);
//  void             setIniFile(const QString& fileName);
  QVariant         value(const QString& key, const QVariant& defaultValue = QVariant()) const;
  void             setValue(const QString& key, const QVariant& value);
  void             initialize();
//  void             load();

  QString      iniFileName;
//  LcProperties properties;
//  ToolTable    tools;
  ValueManager vm;
  QSettings    settings;
  };

#endif // CONFIGMGR_H
