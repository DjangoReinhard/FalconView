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
    ActCodes        /*  0 */
  , CurSeg          /*  1 */
  , DroAbs          /*  2 */
  , DroDtg          /*  3 */
  , DroRel          /*  4 */
  , DroTitle        /*  5 */
  , EdLinNum        /*  6 */
  , Feed            /*  7 */
  , Filename        /*  8 */
  , FixEdit         /*  9 */
  , FixPrompt       /* 10 */
  , FixTitle        /* 11 */
  , GCode           /* 12 */
  , LineHL          /* 13 */
  , OldSeg          /* 14 */
  , RapidMove       /* 15 */
  , Speed           /* 16 */
  , ToolDesc        /* 17 */
  , ToolNext        /* 18 */
  , ToolNum         /* 19 */
  , WorkLimit       /* 20 */
  , WorkMove        /* 21 */
  , WorkPiece       /* 22 */
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
