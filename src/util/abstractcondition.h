#ifndef ABSTRACTCONDITION_H
#define ABSTRACTCONDITION_H
#include <QObject>
#include <QVariant>
class ValueModel;


class AbstractCondition : public QObject
{
  Q_OBJECT
public:
  explicit AbstractCondition(ValueModel* model, const QVariant& value, QObject *parent = nullptr);
  virtual ~AbstractCondition();

  bool result() const { return met; }

public slots:
  virtual bool eval() = 0;
  virtual void update();

signals:
  void conditionChanged(bool result);

protected:
  ValueModel* model() { return m; }
  QVariant    value() { return v; }

private:
  ValueModel* m;
  QVariant    v;
  bool        met;
  bool        initialized;
  };

#endif // ABSTRACTCONDITION_H
