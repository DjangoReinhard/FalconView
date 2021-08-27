#ifndef VALUEMODEL_H
#define VALUEMODEL_H

#include <QObject>
#include <QVariant>


class ValueModel : public QObject
{
  Q_OBJECT

public:
  explicit ValueModel(QVariant v = 0);
  void setValue(QVariant v);
  QVariant getValue() const { return value; };

signals:
  void valueChanged(QVariant newValue);

private:
  QVariant value;
  };
#endif // VALUEMODEL_H
