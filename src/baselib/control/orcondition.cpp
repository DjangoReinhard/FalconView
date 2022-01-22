#include <orcondition.h>
#include <QDebug>


OrCondition::OrCondition(AbstractCondition* c0, AbstractCondition* c1, QObject *parent)
 : AbstractCondition(nullptr, QVariant(), parent) {
  addCondition(c0);
  addCondition(c1);
  }


OrCondition::~OrCondition() {
  }


OrCondition& OrCondition::addCondition(AbstractCondition* c) {
  connect(c, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  cl.append(c);

  return *this;
  }


bool OrCondition::eval() {
  for (auto c : qAsConst(cl)) {
//      qDebug() << "OrCondition::eval() ..." << c->result();
      if (c->result()) return true;
      }
  return false;
  }
