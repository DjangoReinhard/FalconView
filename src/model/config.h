#ifndef CONFIG_H
#define CONFIG_H
#include <valuemanager.h>
#include <QString>
class QColor;
class QFont;
class QFile;


class Config
{
public:
  Config(const QString& fileName);
 ~Config();

  QColor getBackground(int index);
  QColor getForeground(int index);
  QFont getFont(int index);
  void setBackground(int index, const QColor& color);
  void setForeground(int index, const QColor& color);
  void setFont(int index, const QFont& font);
  void store();

  static const int guiSettingEntries;
  static const QString guiSettings[];

protected:
  void initialize();
  void load();
  void processConfigLine(const QString& line);
  ValueManager vm;

private:
  QFile* file;
  };
#endif // CONFIG_H
