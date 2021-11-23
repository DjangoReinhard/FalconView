#ifndef SPEEDSTATUS_H
#define SPEEDSTATUS_H
#include <dyncenterwidget.h>
class LabelAdapter;
class QString;
class QWidget;
class QSlider;


class SpeedStatus : public DynCenterWidget
{
  Q_OBJECT
public:
  SpeedStatus(const QString& fileName, QWidget* parent = nullptr);
  virtual ~SpeedStatus();

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual QWidget* createContent() override;

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
  LabelAdapter* curFeed;
  LabelAdapter* curFastFeed;
  LabelAdapter* curSpeed;
  LabelAdapter* cmdFeed;
  LabelAdapter* cmdFastFeed;
  LabelAdapter* cmdSpeed;
  LabelAdapter* feedFactor;
  LabelAdapter* fastfeedFactor;
  LabelAdapter* speedFactor;
  QSlider*      slFeed;
  QSlider*      slFastFeed;
  QSlider*      slSpeed;
  };
#endif // SPEEDSTATUS_H
