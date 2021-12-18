#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H
#include <dyncenterwidget.h>
#include <QVariant>
class QLineEdit;
class QCheckBox;
class QPushButton;
class QShowEvent;


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
  virtual bool eventFilter(QObject *, QEvent *event) override;
  void setupLabels();

protected slots:
  void changeForegroundColor(int i);
  void changeBackgroundColor(int i);
  void changeFont(int i);
  void statusInsideChanged(const QVariant& state);
  void statusShowHelpChanged(const QVariant& state);
  void statusToolMgrChanged(const QVariant& state);
  virtual void showEvent(QShowEvent* e) override;

private:
  QLineEdit**   labels;
  QPushButton** bgButtons;
  QPushButton** fgButtons;
  QPushButton** fontButtons;
  QCheckBox*    cbStatesInside;
  QCheckBox*    cbHelp;
  QCheckBox*    cbToolManager;
  int           count;
  static const QString& className;
  };
#endif // PREFERENCESEDITOR_H
