#ifndef SETTINGSEDITOR_H
#define SETTINGSEDITOR_H
#include <dynwidget.h>
class QLabel;
class QPushButton;


class SettingsEditor : public DynWidget
{
  Q_OBJECT
public:
  SettingsEditor(const QString& uiFile, QWidget* parent = nullptr);
 ~SettingsEditor();

protected:
  void initializeWidget();
  void setupLabels();
  void changeForegroundColor(int i);
  void changeBackgroundColor(int i);
  void changeFont(int i);

private:
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
#endif // SETTINGSEDITOR_H
