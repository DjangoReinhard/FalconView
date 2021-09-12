#include <greatercondition.h>
#include <valuemodel.h>
#include <QDebug>


GreaterCondition::GreaterCondition(ValueModel* model, const QVariant& value, QObject *parent)
 : AbstractCondition(model, value, parent) {
  update();
  }


bool GreaterCondition::eval() {
//  qDebug() << "GreaterCondition::eval() ...";
  switch (model()->getValue().type()) {
    case QMetaType::Char:
    case QMetaType::Short:
    case QMetaType::Int:
//         qDebug() << "compare signed integers (>): " << model()->getValue().toInt()
//                  << "\tvalue: " << value().toInt();
         return model()->getValue().toInt() > value().toInt();
    case QMetaType::Long:
    case QMetaType::LongLong:
//         qDebug() << "compare signed integers (>): " << model()->getValue().toLongLong()
//                  << "\tvalue: " << value().toLongLong();
         return model()->getValue().toLongLong() > value().toLongLong();
    case QMetaType::UChar:
    case QMetaType::UShort:
    case QMetaType::UInt:
    case QMetaType::ULong:
    case QMetaType::ULongLong:
//         qDebug() << "compare unsigned integers (>): " << model()->getValue().toLongLong()
//                  << "\tvalue: " << value().toLongLong();
         return model()->getValue().toULongLong() > value().toULongLong();
    case QMetaType::Float:
    case QMetaType::Double:
//         qDebug() << "compare decimals (>): " << model()->getValue().toDouble()
//                  << "\tvalue: " << value().toDouble();
         return model()->getValue().toDouble() > value().toDouble();
    }
  return false;
  }
