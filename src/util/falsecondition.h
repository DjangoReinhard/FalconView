#ifndef FALSECONDITION_H
#define FALSECONDITION_H

#include "abstractcondition.h"

class FalseCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit FalseCondition(QObject *parent = nullptr);
  virtual ~FalseCondition();

  virtual bool result() const;

public slots:
  virtual bool eval() override;
  };
#endif // FALSECONDITION_H
