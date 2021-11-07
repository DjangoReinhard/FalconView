#ifndef FIXTUREMANAGER_H
#define FIXTUREMANAGER_H

#include <dynwidget.h>
class FixtureEdit;
class AxisMask;


class FixtureManager : public DynWidget
{
  Q_OBJECT
public:
  FixtureManager(const AxisMask& mask, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;
  void activateEditor(int index);

protected:
  virtual void keyReleaseEvent(QKeyEvent* event) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void resizeEvent(QResizeEvent *event) override;

private:
  QWidget*            client;
  const AxisMask&     axisMask;
  };
#endif // FIXTUREMANAGER_H
