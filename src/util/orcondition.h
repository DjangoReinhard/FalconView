#ifndef ORCONDITION_H
#define ORCONDITION_H
#include <abstractcondition.h>


class OrCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit OrCondition(const AbstractCondition& c0, const AbstractCondition& c1, QObject *parent = nullptr);
  virtual ~OrCondition();

  void addCondition(const AbstractCondition& c);

public slots:
  virtual bool eval() override;

private:
  const AbstractCondition& c0;
  const AbstractCondition& c1;
  };
#endif // ORCONDITION_H
