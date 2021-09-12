#include <equalcondition.h>
#include <valuemodel.h>
#include <QDebug>


EqualCondition::EqualCondition(ValueModel* model, const QVariant& value, QObject *parent)
 : AbstractCondition(model, value, parent) {
  update();
  }


bool EqualCondition::eval() {
//  qDebug() << "EqualCondition::eval() ...";
  if (model()->getValue().type() == value().type())
     return model()->getValue() == value();
  else return false;
  }
