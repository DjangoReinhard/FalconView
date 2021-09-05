#ifndef POSITIONDOCKABLE_H
#define POSITIONDOCKABLE_H
#include <dockable.h>
#include <labeladapter.h>
#include <axismask.h>
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

  void setRelStyles(QString styles);
  void setAbsStyles(QString styles);
  void setLblStyles(QString styles);
  void setDtgStyles(QString styles);
  void setLedStyles(QString onStyle, QString offStyle);
  void setFontSize(int size);
  void setXHomed(QVariant arg = QVariant(true));
  void setYHomed(QVariant arg = QVariant(true));
  void setZHomed(QVariant arg = QVariant(true));
  void setAHomed(QVariant arg = QVariant(true));
  void setBHomed(QVariant arg = QVariant(true));
  void setCHomed(QVariant arg = QVariant(true));
  void setUHomed(QVariant arg = QVariant(true));
  void setVHomed(QVariant arg = QVariant(true));
  void setWHomed(QVariant arg = QVariant(true));

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
  void setAbsolute(QVariant arg = QVariant(true));
  void setAxisMask(QVariant axisMask);
  void setRelative();

protected:
  virtual void resizeEvent(QResizeEvent* event);
  void initializeWidget(QWidget* widget);
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

#endif // POSITIONDOCKABLE_H
