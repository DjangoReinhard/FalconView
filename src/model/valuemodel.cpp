#include "valuemodel.h"


ValueModel::ValueModel(const QString& name, const QVariant& value)
 : QObject(nullptr)
 , v(value)
 , n(name) {
  }


void ValueModel::setValue(const QVariant& value) {
  if (v != value) {
     v = value;
     emit valueChanged(v);
     }
  }
