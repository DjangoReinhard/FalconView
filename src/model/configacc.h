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
    DroAbs          /*  2 */
  , DroRel          /*  4 */
  , DroDtg          /*  3 */
  , DroTitle        /*  5 */
  , ToolDesc        /* 17 */
  , ToolNum         /* 19 */
  , ToolNext        /* 18 */
  , ActCodes        /*  0 */
  , Feed            /*  7 */
  , Speed           /* 16 */
  , Filename        /*  8 */
  , GCode           /* 12 */
  , EdLinNum        /*  6 */
  , LineHL          /* 13 */
  , FixPrompt       /* 10 */
  , FixTitle        /* 11 */
  , FixEdit         /*  9 */
  , RapidMove       /* 15 */
  , WorkMove        /* 21 */
  , CurSeg          /*  1 */
  , OldSeg          /* 14 */
  , WorkPiece       /* 22 */
  , WorkLimit       /* 20 */
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
