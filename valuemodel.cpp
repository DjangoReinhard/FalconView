#include "valuemodel.h"


ValueModel::ValueModel(QVariant v)
 : QObject(nullptr)
 , value(v) {
  }


void ValueModel::setValue(QVariant v) {
  if (v != value) {
     value = v;
     emit valueChanged(v);
     }
  }
