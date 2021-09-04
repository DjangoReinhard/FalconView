#include "labeladapter.h"
#include <QTextStream>

LabelAdapter::LabelAdapter(QLabel* label, int realDigits)
 : QObject(label)
 , lbl(label)
 , digits(realDigits) {
  }


void LabelAdapter::setValue(QVariant value) {
  if (!lbl) return;
  QString tv = QString("%L1").arg(value.toDouble(), 0, 'f', 3);

  lbl->setText(tv);
  }
