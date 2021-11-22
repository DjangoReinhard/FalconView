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

  void addPage(DynCenterWidget* page);

protected:
  QString loadStyles(QTabWidget::TabPosition tp);
  virtual void keyPressEvent(QKeyEvent* e) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual QWidget* createContent() override;

private:
  QTabWidget* tw;
  };
#endif // SETTINGSNB_H
