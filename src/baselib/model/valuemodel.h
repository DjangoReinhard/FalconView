#ifndef VALUEMODEL_H
#define VALUEMODEL_H
#include <QObject>
#include <QVariant>


class ValueModel : public QObject
{
  Q_OBJECT
public:
  explicit ValueModel(const QString& name, const QVariant& value = 0);

  void     setValue(const QVariant& value);
  QVariant getValue() const { return v; };
  QString  getName()  const { return n; };
  void     dump() const;

signals:
  void valueChanged(const QVariant& newValue);

private:
  QVariant v;
  QString  n;
  };
#endif // VALUEMODEL_H
