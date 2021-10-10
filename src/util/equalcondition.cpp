#include <equalcondition.h>
#include <valuemodel.h>
#include <QVariant>
#include <QDebug>


EqualCondition::EqualCondition(ValueModel* model, const QVariant& value, QObject *parent)
 : AbstractCondition(model, value, parent) {
  update();
  }


bool EqualCondition::eval() {
//  qDebug() << "EqualCondition::eval() ...";
  if (model()->getValue().typeId() == value().typeId())
     return model()->getValue() == value();
  else return false;
  }
