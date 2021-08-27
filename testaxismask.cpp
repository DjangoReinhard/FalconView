#include "testaxismask.h"
#include "axismask.h"
#include <iostream>


void TestAxisMask::test3() {
  AxisMask am(0x07);

  QCOMPARE(am.activeAxis(), 3);
  }


void TestAxisMask::test5() {
  AxisMask am(0x01F);

  QCOMPARE(am.activeAxis(), 5);
  }


void TestAxisMask::test9() {
  AxisMask am(0x01FF);

  QCOMPARE(am.activeAxis(), 9);
  }
