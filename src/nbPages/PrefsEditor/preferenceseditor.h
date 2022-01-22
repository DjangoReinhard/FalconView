#ifndef PREFERENCESEDITOR_H
#define PREFERENCESEDITOR_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QCheckBox;
class QPushButton;
class QShowEvent;
QT_END_NAMESPACE


class PreferencesEditor : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "prefsEditor.json")
#endif
public:
  PreferencesEditor(QWidget* parent = nullptr);
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
  virtual void showEvent(QShowEvent* e) override;

private:
  QLineEdit**   labels;
  QPushButton** bgButtons;
  QPushButton** fgButtons;
  QPushButton** fontButtons;
  QCheckBox*    cbStatesInside;
  QCheckBox*    cbHelp;
  QCheckBox*    cbPreviewCenter;
  int           count;
  };
#endif // PREFERENCESEDITOR_H
