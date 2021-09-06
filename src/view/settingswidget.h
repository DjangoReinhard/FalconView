#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H
#include <dynwidget.h>
#include <config.h>
class QLabel;
class QPushButton;


class SettingsWidget : public DynWidget
{
  Q_OBJECT
public:
  SettingsWidget(const QString& uiFile, const QString& configFile, QWidget* parent = nullptr);

public slots:
  void save();

protected:
  void initializeWidget();
  void changeForegroundColor(int i);
  void changeBackgroundColor(int i);
  void changeFont(int i);
  void refresh();

private:
  Config            cfg;
  QLabel**          labels;
  QPushButton*      bgActCodes;
  QPushButton*      bgDroAbs;
  QPushButton*      bgDroDtg;
  QPushButton*      bgDroRel;
  QPushButton*      bgDroTitle;
  QPushButton*      bgFeed;
  QPushButton*      bgFilename;
  QPushButton*      bgGCode;
  QPushButton*      bgSpeed;
  QPushButton*      bgToolNum;
  QPushButton*      bgToolDesc;
  QPushButton*      bgToolNext;

  QPushButton*      fgActCodes;
  QPushButton*      fgDroAbs;
  QPushButton*      fgDroDtg;
  QPushButton*      fgDroRel;
  QPushButton*      fgDroTitle;
  QPushButton*      fgFeed;
  QPushButton*      fgFilename;
  QPushButton*      fgGCode;
  QPushButton*      fgSpeed;
  QPushButton*      fgToolDesc;
  QPushButton*      fgToolNext;
  QPushButton*      fgToolNum;

  QPushButton*      fontActCodes;
  QPushButton*      fontDroAbs;
  QPushButton*      fontDroDtg;
  QPushButton*      fontDroRel;
  QPushButton*      fontDroTitle;
  QPushButton*      fontFeed;
  QPushButton*      fontFilename;
  QPushButton*      fontGCode;
  QPushButton*      fontSpeed;
  QPushButton*      fontToolDesc;
  QPushButton*      fontToolNext;
  QPushButton*      fontToolNum;
  };
#endif // SETTINGSWIDGET_H
