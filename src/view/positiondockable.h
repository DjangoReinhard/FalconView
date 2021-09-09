#ifndef POSITIONDOCKABLE_H
#define POSITIONDOCKABLE_H
#include <dockable.h>
#include <labeladapter.h>
#include <axismask.h>
#include <config.h>
#include <QDockWidget>
#include <QLabel>
#include <QResizeEvent>
class QString;


class PositionDockable : public Dockable
{
  Q_OBJECT
public:
  PositionDockable(const QString& fileName, const AxisMask& axisMask, QWidget* parent = nullptr);
  PositionDockable(const QString& fileName, const AxisMask& axisMask, QWidget* parent, QString ledOn, QString ledOff);
  virtual ~PositionDockable();

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
  void setAxisMask(QVariant axisMask);
  void setRelative();

protected:
  void initializeWidget(QWidget* widget);
  void updateStyles();
  void connectSignals();
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
  int height;
  bool absolute;
  AxisMask axisMask;
  QString ledOn;
  QString ledOff;

  static const char* a[];
  };

#endif // POSITIONDOCKABLE_H
