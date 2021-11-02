#ifndef AXISMASK_H
#define AXISMASK_H
class QString;


class AxisMask
{
public:
//  AxisMask(int mask = 0);
  AxisMask(const AxisMask& other);
  AxisMask(const QString& iniValue);
//  AxisMask(bool hasX, bool hasY, bool hasZ, bool hasA, bool hasB, bool hasC, bool hasU, bool hasV, bool hasW);

  int  activeAxis() const { return cntActive; }
  int  mask()       const { return axisMask;  }
  bool hasXAxis()   const { return axisMask & 0x001; }
  bool hasYAxis()   const { return axisMask & 0x002; }
  bool hasZAxis()   const { return axisMask & 0x004; }
  bool hasAAxis()   const { return axisMask & 0x008; }
  bool hasBAxis()   const { return axisMask & 0x010; }
  bool hasCAxis()   const { return axisMask & 0x020; }
  bool hasUAxis()   const { return axisMask & 0x040; }
  bool hasVAxis()   const { return axisMask & 0x080; }
  bool hasWAxis()   const { return axisMask & 0x100; }
  int  joint4Axis(int axis) const;
  void dump() const;

protected:
  void calcActive();
  void parseIni(const QString& iniValue);
  int  assembleMask(bool hasX, bool hasY, bool hasZ, bool hasA, bool hasB, bool hasC, bool hasU, bool hasV, bool hasW);

private:
  int axisMask;
  int cntActive;
  int joint2Axis[9];
  static const char axisLetters[];
  };
#endif // AXISMASK_H
