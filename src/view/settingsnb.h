#ifndef SETTINGSNB_H
#define SETTINGSNB_H
#include <dyncenterwidget.h>
#include <QTabWidget>
class QCloseEvent;


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
  bool switchTabPage(int pageIndex);
  void currentChanged(int index);

private:
  QTabWidget* tw;
  };
#endif // SETTINGSNB_H
