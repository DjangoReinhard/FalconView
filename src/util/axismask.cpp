#include "axismask.h"
#include <iostream>
#include <QString>
#include <QRegularExpression>
#include <QDebug>


//AxisMask::AxisMask(int mask)
// : axisMask(mask)
// , cntActive(0) {
//  calcActive();
//  }


AxisMask::AxisMask(const QString& iniValue)
 : axisMask(0)
 , cntActive(0) {
  memset(&joint2Axis, -1, sizeof(joint2Axis));
  parseIni(iniValue);
  }


AxisMask::AxisMask(const AxisMask& other)
 : axisMask(other.axisMask)
 , cntActive(other.cntActive) {
  for (int i=0; i < 9; ++i) joint2Axis[i] = other.joint2Axis[i];
  }


//AxisMask::AxisMask(bool hasX, bool hasY, bool hasZ, bool hasA, bool hasB, bool hasC, bool hasU, bool hasV, bool hasW)
// : axisMask(0)
// , cntActive(0) {
//  axisMask = assembleMask(hasX, hasY, hasZ, hasA, hasB, hasC, hasU, hasV, hasW);
//  calcActive();
//  }


int AxisMask::assembleMask(bool hasX, bool hasY, bool hasZ, bool hasA, bool hasB, bool hasC, bool hasU, bool hasV, bool hasW) {
  int mask = 0;

  mask |= hasX ? 0x001 : 0;
  mask |= hasY ? 0x002 : 0;
  mask |= hasZ ? 0x004 : 0;
  mask |= hasA ? 0x008 : 0;
  mask |= hasB ? 0x010 : 0;
  mask |= hasC ? 0x020 : 0;
  mask |= hasU ? 0x040 : 0;
  mask |= hasV ? 0x080 : 0;
  mask |= hasW ? 0x100 : 0;

  return mask;
  }


void AxisMask::calcActive() {
  std::cout << "axisMask: " << axisMask;
  for (int i=0; i < 9; ++i) {
      if (axisMask & (1 << i)) ++cntActive;
      }
  std::cout << "\tfound " << cntActive << " active axis" << std::endl;
}


int AxisMask::joint4Axis(int axis) const {
  if (axis >= 0 && axis < 9) return joint2Axis[axis];
  return -1;
  }


void AxisMask::dump() const {
  qDebug() << "AxisMask is" << QString("0x%1").arg(axisMask, 0, 16);
  qDebug() <<   "X:" << (hasXAxis() ? "yes" : "no")
           << "\nY:" << (hasYAxis() ? "yes" : "no")
           << "\nZ:" << (hasZAxis() ? "yes" : "no")
           << "\nA:" << (hasAAxis() ? "yes" : "no")
           << "\nB:" << (hasBAxis() ? "yes" : "no")
           << "\nC:" << (hasCAxis() ? "yes" : "no")
           << "\nU:" << (hasUAxis() ? "yes" : "no")
           << "\nV:" << (hasVAxis() ? "yes" : "no")
           << "\nW:" << (hasWAxis() ? "yes" : "no");
  for (int i=0; i < 9; ++i) {
      qDebug() << "axis #" << i << "is joint #" << joint2Axis[i];
      }
  }


void AxisMask::parseIni(const QString& iniValue) {
  bool axisSeen[9] = {0};

  if (!iniValue.isEmpty() && iniValue.contains("=")) {
     QStringList parts = iniValue.split(QRegularExpression("\\s*=\\s*"));

     if (parts.size() > 1) {
        const QString& pattern = parts[1];
        int mx = pattern.size();

        qDebug() << "AxisMask initialized with pattern: " << pattern;

        // i is sequence number of axis
        for (int i=0; i < 9; ++i) {
            // n is index of letters in inifile-pattern, which equals to joint number
            for (int n=0; n < mx; ++n) {
                const char axisLetter = pattern[n].toUpper().toLatin1();

                if (axisLetter == axisLetters[i]) {
                   joint2Axis[i] = n;   // i is axis-, n is joint number
                   axisSeen[i]   = true;
                   }
                }
            }
        }
     }
  axisMask = assembleMask(axisSeen[0]
                        , axisSeen[1]
                        , axisSeen[2]
                        , axisSeen[3]
                        , axisSeen[4]
                        , axisSeen[5]
                        , axisSeen[6]
                        , axisSeen[7]
                        , axisSeen[8]);
  }

const char AxisMask::axisLetters[] = "XYZABCUVW";
