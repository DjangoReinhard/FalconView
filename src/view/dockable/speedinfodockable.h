#ifndef SPEEDINFODOCKABLE_H
#define SPEEDINFODOCKABLE_H
#include <dockable.h>
class LabelAdapter;
class QString;
class QWidget;
class QSlider;


class SpeedInfoDockable : public Dockable
{
  Q_OBJECT
public:
  SpeedInfoDockable(const QString& fileName, QWidget* parent = nullptr);
  virtual ~SpeedInfoDockable();

protected:
  void initializeWidget(QWidget* widget);
  void connectSignals();
  void updateStyles();

protected slots:
  void feedChanged(const QVariant& v);
  void fastFeedChanged(const QVariant& v);
  void speedChanged(const QVariant& v);

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
#endif // SPEEDINFODOCKABLE_H
