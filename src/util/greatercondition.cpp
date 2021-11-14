#include <greatercondition.h>
#include <valuemodel.h>
#include <QDebug>


GreaterCondition::GreaterCondition(ValueModel* model, const QVariant& value, QObject *parent)
 : AbstractCondition(model, value, parent) {
  update();
  }


GreaterCondition::~GreaterCondition() {
  }


bool GreaterCondition::eval() {
//  qDebug() << "GreaterCondition::eval() ...";
  switch (model()->getValue().type()) {
    case QVariant::Type::Char:
    case QVariant::Type::Int:
//         qDebug() << "compare signed integers (>): " << model()->getValue().toInt()
//                  << "\tvalue: " << value().toInt();
         return model()->getValue().toInt() > value().toInt();
    case QVariant::Type::LongLong:
//         qDebug() << "compare signed integers (>): " << model()->getValue().toLongLong()
//                  << "\tvalue: " << value().toLongLong();
         return model()->getValue().toLongLong() > value().toLongLong();
    case QVariant::Type::UInt:
    case QVariant::Type::ULongLong:
//         qDebug() << "compare unsigned integers (>): " << model()->getValue().toLongLong()
//                  << "\tvalue: " << value().toLongLong();
         return model()->getValue().toULongLong() > value().toULongLong();
    case QVariant::Type::Double:
//         qDebug() << "compare decimals (>): " << model()->getValue().toDouble()
//                  << "\tvalue: " << value().toDouble();
         return model()->getValue().toDouble() > value().toDouble();
    default:
         return false;
    }
  return false;
  }
