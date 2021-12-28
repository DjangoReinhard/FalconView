#ifndef SMALLERCONDITION_H
#define SMALLERCONDITION_H
#include <abstractcondition.h>


class SmallerCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit SmallerCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);
  virtual ~SmallerCondition();

public slots:
  virtual bool eval() override;
  };
#endif // SMALLERCONDITION_H
