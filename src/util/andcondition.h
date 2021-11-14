#ifndef ANDCONDITION_H
#define ANDCONDITION_H
#include <abstractcondition.h>


class AndCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit AndCondition(AbstractCondition* c0, AbstractCondition* c1, QObject *parent = nullptr);
  virtual ~AndCondition();

  AndCondition* addCondition(AbstractCondition* c);

public slots:
  virtual bool eval() override;

private:
  QList<AbstractCondition*> cl;
  };
#endif // ANDCONDITION_H
