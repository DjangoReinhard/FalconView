#ifndef NUMLABEL_H
#define NUMLABEL_H
#include <QLabel>


class NumLabel : public QLabel
{
  Q_OBJECT
public:
  explicit NumLabel(QWidget* parent = nullptr, int digits = 3);
  virtual ~NumLabel();

  void setDigits(int digits);
  void setValue(const QVariant& v);

private:
  int     digits;
  };
#endif // NUMLABEL_H
