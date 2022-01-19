#ifndef SETTINGSNB_H
#define SETTINGSNB_H
#include <abscenterwidget.h>
#include <QTabWidget>
class QCloseEvent;
class QVariant;


class SettingsNotebook : public AbstractCenterWidget
{
  Q_OBJECT
public:
  explicit SettingsNotebook(QWidget *parent = nullptr);
  virtual ~SettingsNotebook();

  void addPage(AbstractCenterWidget* page);
  void dump();

protected:
  virtual bool eventFilter(QObject *obj, QEvent *event) override;
  virtual void resizeEvent(QResizeEvent *event) override;
  QString loadStyles(QTabWidget::TabPosition tp);
  virtual QWidget* createContent() override;
  void pageChanged(AbstractCenterWidget* page, const QVariant& dirty);
  bool switchTabPage(int pageIndex);
  void currentChanged(int index);

  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual void showEvent(QShowEvent* e) override;

protected slots:
  void enableTabs(const QVariant& enable);

private:
  QTabWidget* tw;
  };
#endif // SETTINGSNB_H
