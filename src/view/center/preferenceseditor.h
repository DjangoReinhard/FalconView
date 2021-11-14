#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H
#include <dynwidget.h>
class QLabel;
class QPushButton;


class PreferencesEditor : public DynWidget
{
  Q_OBJECT
public:
  PreferencesEditor(const QString& uiFile, QWidget* parent = nullptr);
 ~PreferencesEditor();

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
#endif // PREFERENCESEDITOR_H
