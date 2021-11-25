#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H
#include <dyncenterwidget.h>
#include <QVariant>
class QLabel;
class QCheckBox;
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

protected slots:
  void changeForegroundColor(int i);
  void changeBackgroundColor(int i);
  void changeFont(int i);
  void statusInsideChanged(QVariant state);

private:
  QLabel**      labels;
  QPushButton** bgButtons;
  QPushButton** fgButtons;
  QPushButton** fontButtons;
  QCheckBox*    cbStatesInside;
  static const QString& className;
  };
#endif // PREFERENCESEDITOR_H
