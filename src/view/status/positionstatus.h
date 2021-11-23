#ifndef POSITIONSTATUS_H
#define POSITIONSTATUS_H
#include <dyncenterwidget.h>
#include <labeladapter.h>
#include <axismask.h>
#include <QDockWidget>
#include <QLabel>
#include <QResizeEvent>
class QString;


class PositionStatus : public DynCenterWidget
{
  Q_OBJECT
public:
  PositionStatus(const QString& fileName, const AxisMask& axisMask, QWidget* parent = nullptr);
  PositionStatus(const QString& fileName, const AxisMask& axisMask, QWidget* parent, QString ledOn, QString ledOff);
  virtual ~PositionStatus();

  void setLedStyles(QString onStyle, QString offStyle);
  void setXHomed(QVariant arg = QVariant(true));
  void setYHomed(QVariant arg = QVariant(true));
  void setZHomed(QVariant arg = QVariant(true));
  void setAHomed(QVariant arg = QVariant(true));
  void setBHomed(QVariant arg = QVariant(true));
  void setCHomed(QVariant arg = QVariant(true));
  void setUHomed(QVariant arg = QVariant(true));
  void setVHomed(QVariant arg = QVariant(true));
  void setWHomed(QVariant arg = QVariant(true));

public slots:
  void setAbsolute(QVariant arg = QVariant(true));
  void setRelative();

protected:
  virtual void updateStyles() override;
  virtual void connectSignals() override;
  virtual QWidget* createContent() override;
  void updatePos();
  void setActive();

private:
  QLabel* lblX;
  QLabel* lblY;
  QLabel* lblZ;
  QLabel* lblA;
  QLabel* lblB;
  QLabel* lblC;
  QLabel* lblU;
  QLabel* lblV;
  QLabel* lblW;
  QLabel* ledX;
  QLabel* ledY;
  QLabel* ledZ;
  QLabel* ledA;
  QLabel* ledB;
  QLabel* ledC;
  QLabel* ledU;
  QLabel* ledV;
  QLabel* ledW;
  LabelAdapter** droRel;
  LabelAdapter** droAbs;
  LabelAdapter** droDtg;
  int  height;
  bool absolute;
  AxisMask axisMask;
  QString  ledOn;
  QString  ledOff;

  static const char* a[];
  };

#endif // POSITIONSTATUS_H
