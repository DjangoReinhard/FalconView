#ifndef SPEEDINFODOCKABLE_H
#define SPEEDINFODOCKABLE_H
#include <QDockWidget>
class LabelAdapter;
class QFile;


class SpeedInfoDockable : public QDockWidget
{
  Q_OBJECT
public:
  SpeedInfoDockable(QFile& uiDesc, QWidget* parent = nullptr);
  virtual ~SpeedInfoDockable();

protected:
  void initializeWidget(QFile& uiDesc);

private:
  LabelAdapter* curFeed;
  LabelAdapter* curFastFeed;
  LabelAdapter* curSpeed;
  LabelAdapter* cmdFeed;
  LabelAdapter* cmdFastFeed;
  LabelAdapter* cmdSpeed;
  };
#endif // SPEEDINFODOCKABLE_H
