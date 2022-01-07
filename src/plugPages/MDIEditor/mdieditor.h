#ifndef MDIEDITOR_H
#define MDIEDITOR_H
#include <abscenterwidget.h>
#include <mdieditorinterface.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QListWidget;
QT_END_NAMESPACE


class MDIEditor : public AbstractCenterWidget, public MDIEditorInterface
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_INTERFACES(MDIEditorInterface)
  Q_PLUGIN_METADATA(IID "MDIEditorInterface_iid" FILE "mdiEditor.json")
#endif
public:
  explicit MDIEditor(QWidget* parent = nullptr);
  virtual ~MDIEditor();

  virtual void     append(const QString& command) override;
  virtual QString  command() const override;
  virtual QWidget* createContent() override;
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;

protected slots:
  void currentChanged(const QModelIndex &current, const QModelIndex &previous);
  virtual bool eventFilter(QObject* o, QEvent* e) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;

protected:
  void createTestData();

private:
  QListWidget* history;
  QLineEdit*   cmd;
  static const QString testData[];
  };
#endif // MDIEDITOR_H
