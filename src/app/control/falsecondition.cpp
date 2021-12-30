#include "falsecondition.h"

FalseCondition::FalseCondition(QObject *parent)
 : AbstractCondition(nullptr, QVariant(), parent) {
  }


FalseCondition::~FalseCondition() {
  }


bool FalseCondition::eval() {
  return false;
  }


bool FalseCondition::result() const {
  return false;
  }
