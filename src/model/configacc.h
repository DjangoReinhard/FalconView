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
  // sync with ConfigManager::geToString(int i) !
  enum GuiElem {
    DroAbs
  , DroRel
  , DroDtg
  , DroTitle
  , ToolDesc
  , ToolNum
  , ToolNext
  , ActCodes
  , Feed
  , Speed
  , Filename
  , GCode
  , EdLinNum
  , LineHL
  , FixPrompt
  , FixTitle
  , FixDisabledTitle
  , FixEdit
  , RapidMove
  , WorkMove
  , CurSeg
  , OldSeg
  , WorkPiece
  , WorkLimit
  , LastKey
    };

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
  };
#endif // CONFIG_H
