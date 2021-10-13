#include "axismask.h"
#include <iostream>


AxisMask::AxisMask(int mask)
 : axisMask(mask)
 , cntActive(0) {
  calcActive();
  }


AxisMask::AxisMask(const AxisMask& other)
 : axisMask(other.axisMask)
 , cntActive(other.cntActive) {
  }


AxisMask::AxisMask(bool hasX, bool hasY, bool hasZ, bool hasA, bool hasB, bool hasC, bool hasU, bool hasV, bool hasW)
 : axisMask(0)
 , cntActive(0) {
  axisMask |= hasX ? 0x001 : 0;
  axisMask |= hasY ? 0x002 : 0;
  axisMask |= hasZ ? 0x004 : 0;
  axisMask |= hasA ? 0x008 : 0;
  axisMask |= hasB ? 0x010 : 0;
  axisMask |= hasC ? 0x020 : 0;
  axisMask |= hasU ? 0x040 : 0;
  axisMask |= hasV ? 0x080 : 0;
  axisMask |= hasW ? 0x100 : 0;
  calcActive();
  }


void AxisMask::calcActive() {
  std::cout << "axisMask: " << axisMask;
  for (int i=0; i < 9; ++i) {
      if (axisMask & (1 << i)) ++cntActive;
      }
  std::cout << "\tfound " << cntActive << " active axis" << std::endl;
}
