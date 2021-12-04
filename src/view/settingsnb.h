#ifndef SETTINGSNB_H
#define SETTINGSNB_H
#include <dyncenterwidget.h>
#include <QTabWidget>
class QCloseEvent;
class QVariant;


class SettingsNotebook : public DynCenterWidget
{
  Q_OBJECT
public:
  static const QString className;
  explicit SettingsNotebook(QWidget *parent = nullptr);
  virtual ~SettingsNotebook();

  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void closeEvent(QCloseEvent*) override;

  void addPage(DynCenterWidget* page);

protected:
  virtual bool eventFilter(QObject *obj, QEvent *event) override;
  QString loadStyles(QTabWidget::TabPosition tp);
  virtual QWidget* createContent() override;
  void pageChanged(DynCenterWidget* page, const QVariant& dirty);
  bool switchTabPage(int pageIndex);
  void currentChanged(int index);

protected slots:
  void enableTabs(const QVariant& enable);

private:
  QTabWidget* tw;
  };
#endif // SETTINGSNB_H
