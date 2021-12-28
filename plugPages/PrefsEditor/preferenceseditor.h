#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H
#include <abscenterwidget.h>
//#include <QVariant>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QPushButton;
class QShowEvent;
QT_END_NAMESPACE


class PreferencesEditor : public AbstractCenterWidget
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
  void previewCenterChanged(const QVariant& state);
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
  QCheckBox*    cbPreviewCenter;
  QCheckBox*    cbToolManager;
  int           count;
  static const QString& className;
  };
#endif // PREFERENCESEDITOR_H
