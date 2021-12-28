#include <axismask.h>
#include <valuemanager.h>
#include <iostream>
#include <QString>
#include <QRegularExpression>
#include <QDebug>


AxisMask::AxisMask(const QString& iniValue)
 : QObject(nullptr)
 , cntActive(0)
 , axisMask(0) {
  memset(&joint2Axis, -1, sizeof(joint2Axis));
  memset(&axisSeen, 0, sizeof(axisSeen));
  parseIni(iniValue);
  }


AxisMask::AxisMask(const AxisMask& other)
 : QObject(nullptr)
 , cntActive(other.cntActive)
 , axisMask(other.axisMask) {
  for (int i=0; i < 9; ++i) {
      joint2Axis[i] = other.joint2Axis[i];
      axisSeen[i]   = other.axisSeen[i];
      }
  }


AxisMask::~AxisMask() {
  }


void AxisMask::calcActive() {
  ValueManager vm;

  for (int i=0; i < 9; ++i)
      if (axisSeen[i]) {
         ++cntActive;
         axisMask |= 1 << i;
         connect(vm.getModel(QString("homedJoint%1").arg(joint2Axis[i])), &ValueModel::valueChanged
                 , this, [=](){ ValueManager vmgr;
                                checkHomed(i, vmgr.getValue(QString("homedJoint%1").arg(joint2Axis[i]))); });
         }
  qDebug() << "\tfound " << cntActive << " active axis. Mask set to:" << axisMask;
  }


void AxisMask::checkHomed(int axis, QVariant value) {
  if (axis > -1 && axis < 9) axisHomed[axis] = value.toBool();
  bool allHomed = true;

  for (int i=0; i < 9; ++i) {
      if (axisSeen[i] && !axisHomed[i]) {
         allHomed = false;
         break;
         }
      }
  if (allHomed) ValueManager().setValue("allHomed", true);
  }


bool AxisMask::hasAxis(int axis) const {
  if (axis > 0 && axis < 9) return axisSeen[axis];
  return false;
  }


int AxisMask::joint4Axis(int axis) const {
  if (axis >= 0 && axis < 9) return joint2Axis[axis];
  return -1;
  }


void AxisMask::dump() const {
  qDebug() <<   "X:" << (hasXAxis() ? "yes" : "no")
           << "\nY:" << (hasYAxis() ? "yes" : "no")
           << "\nZ:" << (hasZAxis() ? "yes" : "no")
           << "\nA:" << (hasAAxis() ? "yes" : "no")
           << "\nB:" << (hasBAxis() ? "yes" : "no")
           << "\nC:" << (hasCAxis() ? "yes" : "no")
           << "\nU:" << (hasUAxis() ? "yes" : "no")
           << "\nV:" << (hasVAxis() ? "yes" : "no")
           << "\nW:" << (hasWAxis() ? "yes" : "no");
  for (int i=0; i < 9; ++i) qDebug() << "axis #" << i << "is joint #" << joint2Axis[i];
  }


void AxisMask::parseIni(const QString& iniValue) {
//  qDebug() << "parseIni(" << iniValue << ") - check for '='";

  if (!iniValue.isEmpty() && iniValue.contains("=")) {
     QStringList parts = iniValue.split(QRegularExpression("\\s*=\\s*"));

     if (parts.size() > 1) setup(parts[1]);
     }
  }


void AxisMask::setup(const QString &iniValue) {
  QString pattern(iniValue);

  pattern.remove(' ');
  int mx = pattern.size();

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
  calcActive();
  }


const char AxisMask::axisLetters[] = "XYZABCUVW";
