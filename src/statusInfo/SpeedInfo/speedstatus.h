#ifndef SPEEDSTATUS_H
#define SPEEDSTATUS_H
#include <abscenterwidget.h>
class QLabel;
class QSlider;


class SpeedStatus : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "speedInfo.json")
#endif
public:
  SpeedStatus(QWidget* parent = nullptr);
  virtual ~SpeedStatus();

protected:
  virtual void     connectSignals() override;
  virtual QWidget* createContent() override;
  virtual QString  fileName() const override;
  virtual void     patch(void* pk, void* pc, void* pv, void* pu = nullptr, bool flag = false) override;
  virtual void     updateStyles() override;

protected slots:
  // slider callbacks
  void feedChanged(const QVariant& v);
  void fastFeedChanged(const QVariant& v);
  void speedChanged(const QVariant& v);
  // backend callbacks
  void feedRateChanged(const QVariant& v);
  void fastFeedRateChanged(const QVariant& v);
  void speedRateChanged(const QVariant& v);

private:
  bool    isVertical;
  QLabel *cmdFastFeed;
  QLabel *cmdFeed;
  QLabel *cmdSpeed;
  QLabel *curFastFeed;
  QLabel *curFeed;
  QLabel *curSpeed;
  QLabel *fastfeedFactor;
  QLabel *feedFactor;
  QLabel *label;
  QLabel *label_3;
  QLabel *label_9;
  QLabel *speedFactor;
  QSlider *slFastFeed;
  QSlider *slFeed;
  QSlider *slSpeed;
  };
#endif // SPEEDSTATUS_H
