#ifndef NOTCONDITION_H
#define NOTCONDITION_H
#include <abstractcondition.h>


class NotCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit NotCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);
  virtual ~NotCondition();

public slots:
  virtual bool eval() override;
  };
#endif // NOTCONDITION_H
