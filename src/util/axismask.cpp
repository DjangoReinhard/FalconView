#include <axismask.h>
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


AxisMask& AxisMask::operator=(const AxisMask& o) {
  if (&o != this) axisMask = o.axisMask;
  return *this;
  }


AxisMask& AxisMask::operator=(int axisMask) {
  this->axisMask = axisMask;
  return *this;
  }


void AxisMask::calcActive() {
//  std::cout << "axisMask: " << axisMask;
  for (int i=0; i < 9; ++i) {
      if (axisMask & (1 << i)) ++cntActive;
      }
//  std::cout << "\tfound " << cntActive << " active axis" << std::endl;
  }
