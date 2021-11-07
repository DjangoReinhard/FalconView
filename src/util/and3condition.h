#ifndef AND3CONDITION_H
#define AND3CONDITION_H
#include <abstractcondition.h>


class And3Condition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit And3Condition(const AbstractCondition& c0
                       , const AbstractCondition& c1
                       , const AbstractCondition& c2
                       , QObject *parent = nullptr);
  virtual ~And3Condition();

public slots:
  virtual bool eval() override;

private:
  const AbstractCondition& c0;
  const AbstractCondition& c1;
  const AbstractCondition& c2;
  };
#endif // AND3CONDITION_H
