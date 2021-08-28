#include "labeladapter.h"
#include <QTextStream>

LabelAdapter::LabelAdapter(QLabel* label, int realDigits)
 : QObject(nullptr)
 , lbl(label)
 , digits(realDigits) {
  }


void LabelAdapter::setValue(QVariant value) {
  if (!lbl) return;
//  arg(double a, int fieldWidth = 0, char format = 'g', int precision = -1, QChar fillChar = QLatin1Char(' ')) const
  QString tv = QString("%L1").arg(value.toDouble(), 0, 'f', 3/*, QLatin1Char('0')*/);
/*
  QTextStream ts(&tv);

  ts.setFieldWidth(9);
  ts.setRealNumberPrecision(digits);
  ts.setRealNumberNotation(QTextStream::FixedNotation);

  ts << value.toDouble();
*/
  lbl->setText(tv);
  }
