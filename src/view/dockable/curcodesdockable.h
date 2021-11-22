#ifndef CURCODESDOCKABLE_H
#define CURCODESDOCKABLE_H
#include <dyncenterwidget.h>
class QWidget;
class QLabel;

class CurCodesDockable : public DynCenterWidget
{
  Q_OBJECT
public:
  CurCodesDockable(const QString& fileName, QWidget* parent = nullptr);

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual QWidget* createContent() override;

private:
  QLabel** labels;
  };
#endif // CURCODESDOCKABLE_H
