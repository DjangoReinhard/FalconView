#ifndef GREATERCONDITION_H
#define GREATERCONDITION_H
#include <abstractcondition.h>


class GreaterCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit GreaterCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);
  virtual ~GreaterCondition();

public slots:
  virtual bool eval() override;
  };
#endif // GREATERCONDITION_H
