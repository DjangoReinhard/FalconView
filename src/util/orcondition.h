#ifndef ORCONDITION_H
#define ORCONDITION_H
#include <abstractcondition.h>


class OrCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit OrCondition(AbstractCondition* c0, AbstractCondition* c1, QObject *parent = nullptr);
  virtual ~OrCondition();

  OrCondition& addCondition(AbstractCondition* c);

public slots:
  virtual bool eval() override;

private:
  QList<AbstractCondition*> cl;
  };
#endif // ORCONDITION_H
