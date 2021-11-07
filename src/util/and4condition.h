#ifndef AND4CONDITION_H
#define AND4CONDITION_H
#include <abstractcondition.h>


class And4Condition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit And4Condition(const AbstractCondition& c0
                       , const AbstractCondition& c1
                       , const AbstractCondition& c2
                       , const AbstractCondition& c3
                       , QObject *parent = nullptr);
  virtual ~And4Condition();

public slots:
  virtual bool eval() override;

private:
  const AbstractCondition& c0;
  const AbstractCondition& c1;
  const AbstractCondition& c2;
  const AbstractCondition& c3;
  };
#endif // AND4CONDITION_H
