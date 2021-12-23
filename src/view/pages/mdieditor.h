#ifndef MDIEDITOR_H
#define MDIEDITOR_H
#include <dyncenterwidget.h>
class QLineEdit;
class QListWidget;


class MDIEditor : public DynCenterWidget
{
  Q_OBJECT
public:
  static const QString className;
  explicit MDIEditor(const QString& file, QWidget* parent = nullptr);
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
