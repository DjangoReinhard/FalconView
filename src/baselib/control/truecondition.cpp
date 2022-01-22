#include "truecondition.h"

TrueCondition::TrueCondition(QObject *parent)
 : AbstractCondition(nullptr, QVariant(), parent) {
  }


TrueCondition::~TrueCondition() {
  }


bool TrueCondition::eval() {
  return true;
  }


bool TrueCondition::result() const {
  return true;
  }
