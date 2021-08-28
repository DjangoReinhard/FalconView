#ifndef SPEEDINFOWIDGET_H
#define SPEEDINFOWIDGET_H
#include <QDockWidget>
class LabelAdapter;
class QFile;


class SpeedInfoWidget : public QDockWidget
{
  Q_OBJECT
public:
  SpeedInfoWidget(QFile& uiDesc, QWidget* parent = nullptr);
  virtual ~SpeedInfoWidget();

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
#endif // SPEEDINFOWIDGET_H
