#ifndef AXISMASK_H
#define AXISMASK_H


class AxisMask
{
public:
  AxisMask(int mask);
  AxisMask(const AxisMask& other);

  int activeAxis() const { return cntActive; }
  bool hasXAxis()  const { return axisMask & 0x001; }
  bool hasYAxis()  const { return axisMask & 0x002; }
  bool hasZAxis()  const { return axisMask & 0x004; }
  bool hasAAxis()  const { return axisMask & 0x008; }
  bool hasBAxis()  const { return axisMask & 0x010; }
  bool hasCAxis()  const { return axisMask & 0x020; }
  bool hasUAxis()  const { return axisMask & 0x040; }
  bool hasVAxis()  const { return axisMask & 0x080; }
  bool hasWAxis()  const { return axisMask & 0x100; }

protected:
  void calcActive();

private:
  int axisMask;
  int cntActive;
  };
#endif // AXISMASK_H
