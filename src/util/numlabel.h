#ifndef NUMLABEL_H
#define NUMLABEL_H
#include <QLabel>


class NumLabel : public QLabel
{
  Q_OBJECT
public:
  explicit NumLabel(QWidget* parent = nullptr, int digits = 3);
  virtual ~NumLabel();

  void setDependant(QLabel* client);
  void setDigits(int digits);
  void setValue(const QVariant& v);

protected:
  virtual void resizeEvent(QResizeEvent* e) override;

private:
  QLabel* client;
  int     digits;
  };
#endif // NUMLABEL_H
