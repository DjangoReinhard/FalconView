#include <and4condition.h>
#include <QDebug>


And4Condition::And4Condition(const AbstractCondition& c0
                           , const AbstractCondition& c1
                           , const AbstractCondition& c2
                           , const AbstractCondition& c3
                           , QObject *parent)
 : AbstractCondition(nullptr, QVariant(), parent)
 , c0(c0)
 , c1(c1)
 , c2(c2)
 , c3(c3) {
  connect(&c0, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  connect(&c1, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  connect(&c2, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  connect(&c3, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  }


And4Condition::~And4Condition() {
  }


bool And4Condition::eval() {
  qDebug() << "And4Condition::eval() ..." << c0.result()
           << "<>" << c1.result()
           << "<>" << c2.result()
           << "<>" << c3.result();

  return c0.result() && c1.result() && c2.result() && c3.result();
  }
