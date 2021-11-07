#include <and3condition.h>
#include <QDebug>


And3Condition::And3Condition(const AbstractCondition& c0
                           , const AbstractCondition& c1
                           , const AbstractCondition& c2
                           , QObject *parent)
 : AbstractCondition(nullptr, QVariant(), parent)
 , c0(c0)
 , c1(c1)
 , c2(c2) {
  connect(&c0, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  connect(&c1, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  connect(&c2, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  }


And3Condition::~And3Condition() {
  }


bool And3Condition::eval() {
  qDebug() << "And3Condition::eval() ..." << c0.result()
           << "<>" << c1.result()
           << "<>" << c2.result();

  return c0.result() && c1.result() && c2.result();
  }
