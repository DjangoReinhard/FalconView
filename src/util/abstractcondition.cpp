#include <abstractcondition.h>
#include <valuemodel.h>
#include <QDebug>


AbstractCondition::AbstractCondition(ValueModel* model, const QVariant& value, QObject *parent)
 : QObject(parent)
 , m(model)
 , v(value)
 , met(false)
 , initialized(false) {
  if (m) connect(m, &ValueModel::valueChanged, this, &AbstractCondition::update);
  }


AbstractCondition::~AbstractCondition() {
  }


void AbstractCondition::update() {
  qDebug() << "AbstractCondition::update() ...";
  bool rv = eval();

  qDebug() << "\teval returned: " << (rv ? "true" : "false");
  if (!initialized || rv != met) {
     met = rv;
     qDebug() << "\tgonna fire condition changed event ...";
     emit  conditionChanged(met);
     initialized = true;
     }
  }
