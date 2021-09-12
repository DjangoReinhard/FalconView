#ifndef SMALLERCONDITION_H
#define SMALLERCONDITION_H
#include <abstractcondition.h>


class SmallerCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit SmallerCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);

public slots:
  virtual bool eval();
  };
#endif // SMALLERCONDITION_H
