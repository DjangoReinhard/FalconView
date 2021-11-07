#ifndef SETTINGSNB_H
#define SETTINGSNB_H
#include <dynwidget.h>
class QTabWidget;


class SettingsNotebook : public DynWidget //QTabWidget
{
  Q_OBJECT
public:
  explicit SettingsNotebook(QWidget *parent = nullptr);
  virtual ~SettingsNotebook();

  virtual void connectSignals() override;
  virtual void updateStyles() override;

  void addPage(DynWidget* page);

private:
  QTabWidget* tw;
  };
#endif // SETTINGSNB_H
