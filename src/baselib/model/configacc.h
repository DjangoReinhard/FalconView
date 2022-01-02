#ifndef CONFIG_H
#define CONFIG_H
#include <valuemanager.h>
#include <QString>
#include <QSettings>
class ConfigManager;
class AbstractCenterWidget;
class QColor;
class QFont;
class QFile;


class Config
{
public:
  // sync with ConfigManager::geToString(int i) !
  enum GuiElem {
    ActCodes
  , CurSeg
  , DroAbs
  , DroDtg
  , DroRel
  , DroTitle
  , EdLinNum
  , Feed
  , Filename
  , GCode
  , Speed
  , ToolDesc
  , ToolNum
  , ToolNext
  , LineHL
  , FixPrompt
  , FixTitle
  , FixDisabledTitle
  , FixEdit
  , RapidMove
  , WorkMove
  , OldSeg
  , WorkPiece
  , WorkLimit
  , LastKey
    };

  explicit Config();
  QColor   getBackground(GuiElem key) const;
  QColor   getForeground(GuiElem key) const;
  QFont    getFont(GuiElem key) const;
  void     beginGroup(const QString& name);
  void     endGroup();
  void     setBackground(GuiElem key, const QColor& color);
  void     setForeground(GuiElem key, const QColor& color);
  void     setFont(GuiElem key, const QFont& font);
  QVariant value(const QString& key, const QVariant& defaultValue = QVariant()) const;
  void     setValue(const QString& key, const QVariant& value);
  QString  nameOf(GuiElem key) const;
  int      numGuiElements() const { return LastKey; }

private:
  explicit Config(void* p);
  static ConfigManager* cfg;
  friend class AbstractCenterWidget;
  friend class PluginPageFactory;
  };
#endif // CONFIG_H
