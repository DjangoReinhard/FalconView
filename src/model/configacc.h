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
  enum GuiElem {
    ActCodes        /*  0 */
  , DroAbs          /*  1 */
  , DroDtg          /*  2 */
  , DroRel          /*  3 */
  , DroTitle        /*  4 */
  , Feed            /*  5 */
  , Filename        /*  6 */
  , GCode           /*  7 */
  , Speed           /*  8 */
  , ToolDesc        /*  9 */
  , ToolNum         /* 10 */
  , ToolNext        /* 11 */
  , EdLinNum        /* 12 */
  , LineHL          /* 13 */
  , Fixture         /* 14 */
  , FixTitle        /* 15 */
  , FixFrame        /* 16 */
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
