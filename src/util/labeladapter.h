#ifndef LABELADAPTER_H
#define LABELADAPTER_H

#include <QObject>
#include <QLabel>
#include <QVariant>


class LabelAdapter : public QObject
{
  Q_OBJECT

public:
  explicit LabelAdapter(QLabel* label, int realDigits = 3);
  QLabel*  label() { return lbl; };

public slots:
  void setValue(QVariant value);

private:
  QLabel* lbl;
  int     digits;
  };

#endif // LABELADAPTER_H
