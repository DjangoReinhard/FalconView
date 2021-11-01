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

  virtual void connectSignals();
  virtual void updateStyles();

protected:
  void initializeWidget();
  void setupLabels();
  void changeForegroundColor(int i);
  void changeBackgroundColor(int i);
  void changeFont(int i);

private:
  QLabel**      labels;
  QPushButton** bgButtons;
  QPushButton** fgButtons;
  QPushButton** fontButtons;
  };
#endif // SETTINGSEDITOR_H
