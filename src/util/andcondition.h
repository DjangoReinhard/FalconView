#ifndef ANDCONDITION_H
#define ANDCONDITION_H
#include <abstractcondition.h>


class AndCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit AndCondition(const AbstractCondition& c0, const AbstractCondition& c1, QObject *parent = nullptr);
  virtual ~AndCondition();

public slots:
  virtual bool eval() override;

private:
  const AbstractCondition& c0;
  const AbstractCondition& c1;
  };
#endif // ANDCONDITION_H
