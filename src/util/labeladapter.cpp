#include "labeladapter.h"
#include <QTextStream>
#include <QResizeEvent>
#include <QDebug>


LabelAdapter::LabelAdapter(QLabel* label, int realDigits)
 : QObject(label)
 , lbl(label)
 , digits(realDigits) {
  }


void LabelAdapter::setValue(QVariant value) {
  if (!lbl) return;
  QString tv = QString("%1").arg(value.toDouble(), 0, 'f', digits);

  lbl->setText(tv);
  }
