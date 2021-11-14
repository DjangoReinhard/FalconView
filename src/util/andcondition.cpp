#include <andcondition.h>
#include <QDebug>


AndCondition::AndCondition(AbstractCondition* c0, AbstractCondition* c1, QObject* parent)
  : AbstractCondition(nullptr, QVariant(), parent) {
  addCondition(c0);
  addCondition(c1);
  }


AndCondition::~AndCondition() {
  }


AndCondition* AndCondition::addCondition(AbstractCondition* c) {
  connect(c, &AbstractCondition::conditionChanged, this, &AbstractCondition::update);
  cl.append(c);

  return this;
  }


bool AndCondition::eval() {
  for (auto c : qAsConst(cl)) {
//      qDebug() << "AndCondition::eval() ..." << c->result();
      if (!c->result()) return false;
      }
  return true;
  }
