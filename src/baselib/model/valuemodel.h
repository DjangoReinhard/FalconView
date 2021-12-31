#ifndef VALUEMODEL_H
#define VALUEMODEL_H
#include <QObject>
#include <QVariant>


class ValueModel : public QObject
{
  Q_OBJECT
public:
  explicit ValueModel(const QString& name, const QVariant& value = 0);

  void            setValue(const QVariant& value);
  const QVariant& getValue() const { return v; };
  const QString&  getName()  const { return n; };
  void            dump() const;

signals:
  void valueChanged(QVariant newValue);

private:
  QVariant v;
  QString  n;
  };
#endif // VALUEMODEL_H
