#ifndef MDIEDITOR_H
#define MDIEDITOR_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class QLineEdit;
class QListWidget;
QT_END_NAMESPACE


class MDIEditor : public AbstractCenterWidget
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "mdiEditor.json")
public:
  static const QString className;
  explicit MDIEditor(QWidget* parent = nullptr);
  virtual ~MDIEditor();

  void             append(const QString& command);
  QString          command() const;
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
