#ifndef AXISMASK_H
#define AXISMASK_H
#include <QObject>
class QString;


class AxisMask : public QObject
{
  Q_OBJECT
public:
  explicit AxisMask(const AxisMask& other);
  explicit AxisMask(const QString& iniValue);
  virtual ~AxisMask();

  int  activeAxis() const { return cntActive; }
  bool hasXAxis()   const { return axisSeen[0]; }
  bool hasYAxis()   const { return axisSeen[1]; }
  bool hasZAxis()   const { return axisSeen[2]; }
  bool hasAAxis()   const { return axisSeen[3]; }
  bool hasBAxis()   const { return axisSeen[4]; }
  bool hasCAxis()   const { return axisSeen[5]; }
  bool hasUAxis()   const { return axisSeen[6]; }
  bool hasVAxis()   const { return axisSeen[7]; }
  bool hasWAxis()   const { return axisSeen[8]; }
  bool hasAxis(int axis) const;
  void setup(const QString& axisLetters);
  int  joint4Axis(int axis) const;
  int  mask() const { return axisMask; }
  void dump() const;

protected:
  void calcActive();
  void parseIni(const QString& iniValue);
  void checkHomed(int axis, QVariant value);

private:
  int  cntActive;
  int  axisMask;
  int  joint2Axis[9];
  bool axisSeen[9];
  bool axisHomed[9];
  static const char axisLetters[];
  };
#endif // AXISMASK_H
