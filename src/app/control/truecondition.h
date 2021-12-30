#ifndef TRUECONDITION_H
#define TRUECONDITION_H
#include <abstractcondition.h>


class TrueCondition : public AbstractCondition
{
  Q_OBJECT
public:
  explicit TrueCondition(QObject *parent = nullptr);
  virtual ~TrueCondition();

  virtual bool result() const override;

public slots:
  virtual bool eval() override;
  };
#endif // TRUECONDITION_H
