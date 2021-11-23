#ifndef CURCODESSTATUS_H
#define CURCODESSTATUS_H
#include <dyncenterwidget.h>
class QWidget;
class QLabel;

class CurCodesStatus : public DynCenterWidget
{
  Q_OBJECT
public:
  CurCodesStatus(const QString& fileName, QWidget* parent = nullptr);

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual QWidget* createContent() override;

private:
  QLabel** labels;
  };
#endif // CURCODESSTATUS_H
