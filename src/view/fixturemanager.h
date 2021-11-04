#ifndef FIXTUREMANAGER_H
#define FIXTUREMANAGER_H

#include <dynwidget.h>
class FixtureEdit;


class FixtureManager : public DynWidget
{
  Q_OBJECT
public:
  FixtureManager(QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;

protected:
  virtual void showEvent(QShowEvent *event) override;
  virtual void resizeEvent(QResizeEvent *event) override;

private:
  QList<FixtureEdit*> editors;
  QWidget*            client;
  };
#endif // FIXTUREMANAGER_H
