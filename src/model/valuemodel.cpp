#include <valuemodel.h>
#include <QDebug>


ValueModel::ValueModel(const QString& name, const QVariant& value)
 : QObject(nullptr)
 , v(value)
 , n(name) {
  }


void ValueModel::setValue(const QVariant& value) {
//  qDebug() << "ValueModel[" <<  n << "] got new value:" << value;
  if (v != value) {
//     qDebug() << "ValueModel[" <<  n << "] value WILL change:" << v << " -> " << value;
     v = value;
     emit valueChanged(v);
     }
  }


void ValueModel::dump() const {
  qDebug() << "ValueModel[" << n  << "] has value:" << v;
  }
