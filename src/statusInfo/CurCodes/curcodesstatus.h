#ifndef CURCODESSTATUS_H
#define CURCODESSTATUS_H
#include <abscenterwidget.h>
class QWidget;
class QLabel;

class CurCodesStatus : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "curCodes.json")
#endif
public:
  explicit CurCodesStatus(QWidget* parent = nullptr);
  virtual ~CurCodesStatus() = default;

protected:
  virtual void     connectSignals() override;
  virtual QWidget* createContent() override;
  virtual QString  fileName() const override;
  virtual void     patch(void* pk, void* pc, void* pv, void* pu = nullptr, bool flag = false) override;
  virtual void     updateStyles() override;

private:
  bool     isVertical;
  QLabel** labels;
  };
#endif // CURCODESSTATUS_H
