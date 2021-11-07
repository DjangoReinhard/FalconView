#include <orcondition.h>
#include <QDebug>


OrCondition::OrCondition(const AbstractCondition& c0, const AbstractCondition& c1, QObject *parent)
 : AbstractCondition(nullptr, QVariant(), parent)
 , c0(c0)
 , c1(c1) {
  connect(&c0, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  connect(&c1, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  }


OrCondition::~OrCondition() {
  }


bool OrCondition::eval() {
  qDebug() << "OrCondition::eval() ..." << c0.result() << "<>" << c1.result();

  return c0.result() || c1.result();
  }
