#ifndef SPEEDSTATUS_H
#define SPEEDSTATUS_H
#include <abscenterwidget.h>
class QLabel;
class QSlider;


class SpeedStatus : public AbstractCenterWidget
{
  Q_OBJECT
public:
  SpeedStatus(const QString& fileName, QWidget* parent = nullptr);
  virtual ~SpeedStatus();

protected:
  QWidget* createContent() override;
  void     connectSignals() override;
  void     updateStyles() override;

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
