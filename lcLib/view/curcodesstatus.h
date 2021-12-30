#ifndef CURCODESSTATUS_H
#define CURCODESSTATUS_H
#include <abscenterwidget.h>
class QWidget;
class QLabel;

class CurCodesStatus : public AbstractCenterWidget
{
  Q_OBJECT
public:
  explicit CurCodesStatus(QWidget* parent = nullptr);
  virtual ~CurCodesStatus() = default;

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual QWidget* createContent() override;

private:
  QLabel** labels;
  };
#endif // CURCODESSTATUS_H
