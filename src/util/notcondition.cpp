#include <notcondition.h>
#include <valuemodel.h>
#include <QDebug>


NotCondition::NotCondition(ValueModel* model, const QVariant& value, QObject* parent)
 : AbstractCondition(model, value, parent) {
  update();
  }


NotCondition::~NotCondition() {
  }


bool NotCondition::eval() {
  qDebug() << "NotCondition::eval() ...";
  if (model()->getValue().type() == value().type()) {
     qDebug() << "model type matches value type" << model()->getValue() << "<>" << value();
     return model()->getValue() != value();
     }
  else return false;
  }
