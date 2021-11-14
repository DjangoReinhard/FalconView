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

  QColor       getBackground(int index);
  QColor       getForeground(int index);
  QFont        getFont(int index);
  void         setBackground(int index, const QColor& color);
  void         setForeground(int index, const QColor& color);
  void         setFont(int index, const QFont& font);
  QVariant     value(const QString& key, const QVariant& defaultValue = QVariant()) const;
  void         setValue(const QString& key, const QVariant& value);
  QString      geToString(int i);
  void         initialize();

  QString      iniFileName;
  ValueManager vm;
  QSettings    settings;

private:
  const int          lastIndex;
  static const char* guiElemNames[];
  };

#endif // CONFIGMGR_H
