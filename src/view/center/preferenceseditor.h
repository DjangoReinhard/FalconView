#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H
#include <dyncenterwidget.h>
class QLabel;
class QPushButton;


class PreferencesEditor : public DynCenterWidget
{
  Q_OBJECT
public:
  PreferencesEditor(const QString& uiFile, QWidget* parent = nullptr);
 ~PreferencesEditor();

  virtual void connectSignals() override;
  virtual void updateStyles() override;

protected:
  virtual QWidget* createContent() override;
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
