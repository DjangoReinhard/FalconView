#ifndef EQUALCONDITION_H
#define EQUALCONDITION_H
#include <abstractcondition.h>


class EqualCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit EqualCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);

public slots:
  virtual bool eval() override;
  };
#endif // EQUALCONDITION_H
