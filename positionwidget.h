#ifndef POSITIONWIDGET_H
#define POSITIONWIDGET_H

#include "labeladapter.h"
#include "axismask.h"
#include <QDockWidget>
#include <QFile>
#include <QLabel>
#include <QResizeEvent>


class PositionWidget : public QDockWidget
{
  Q_OBJECT

  const int DockingTitleHeight = 39;
public:
  PositionWidget(QFile& uiDesc, const AxisMask& axisMask, QWidget* parent = nullptr);
  PositionWidget(QFile& uiDesc, const AxisMask& axisMask, QWidget* parent, QString ledOn, QString ledOff);

  void setRelStyles(QString styles);
  void setAbsStyles(QString styles);
  void setLblStyles(QString styles);
  void setDtgStyles(QString styles);
  void setLedStyles(QString onStyle, QString offStyle);
  void setFontSize(int size);
  void setXHomed(bool homed=true);
  void setYHomed(bool homed=true);
  void setZHomed(bool homed=true);
  void setAHomed(bool homed=true);
  void setBHomed(bool homed=true);
  void setCHomed(bool homed=true);
  void setUHomed(bool homed=true);
  void setVHomed(bool homed=true);
  void setWHomed(bool homed=true);

  LabelAdapter* getXRel() { return relX; }
  LabelAdapter* getYRel() { return relY; }
  LabelAdapter* getZRel() { return relZ; }
  LabelAdapter* getARel() { return relA; }
  LabelAdapter* getBRel() { return relB; }
  LabelAdapter* getCRel() { return relC; }
  LabelAdapter* getURel() { return relU; }
  LabelAdapter* getVRel() { return relV; }
  LabelAdapter* getWRel() { return relW; }
  LabelAdapter* getXAbs() { return absX; }
  LabelAdapter* getYAbs() { return absY; }
  LabelAdapter* getZAbs() { return absZ; }
  LabelAdapter* getAAbs() { return absA; }
  LabelAdapter* getBAbs() { return absB; }
  LabelAdapter* getCAbs() { return absC; }
  LabelAdapter* getUAbs() { return absU; }
  LabelAdapter* getVAbs() { return absV; }
  LabelAdapter* getWAbs() { return absW; }
  LabelAdapter* getXDtg() { return dtgX; }
  LabelAdapter* getYDtg() { return dtgX; }
  LabelAdapter* getZDtg() { return dtgX; }
  LabelAdapter* getADtg() { return dtgX; }
  LabelAdapter* getBDtg() { return dtgX; }
  LabelAdapter* getCDtg() { return dtgX; }
  LabelAdapter* getUDtg() { return dtgX; }
  LabelAdapter* getVDtg() { return dtgX; }
  LabelAdapter* getWDtg() { return dtgX; }

public slots:
  void setAbsolute();
  void setRelative();

protected:
  virtual void resizeEvent(QResizeEvent *event);
  void initializeWidget(QFile& uiDesc);
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
  LabelAdapter* relX;
  LabelAdapter* relY;
  LabelAdapter* relZ;
  LabelAdapter* relA;
  LabelAdapter* relB;
  LabelAdapter* relC;
  LabelAdapter* relU;
  LabelAdapter* relV;
  LabelAdapter* relW;
  LabelAdapter* absX;
  LabelAdapter* absY;
  LabelAdapter* absZ;
  LabelAdapter* absA;
  LabelAdapter* absB;
  LabelAdapter* absC;
  LabelAdapter* absU;
  LabelAdapter* absV;
  LabelAdapter* absW;
  LabelAdapter* dtgX;
  LabelAdapter* dtgY;
  LabelAdapter* dtgZ;
  LabelAdapter* dtgA;
  LabelAdapter* dtgB;
  LabelAdapter* dtgC;
  LabelAdapter* dtgU;
  LabelAdapter* dtgV;
  LabelAdapter* dtgW;
  int height;
  bool absolute;
  AxisMask axisMask;
  QString ledOn;
  QString ledOff;
  };

#endif // POSITIONWIDGET_H
