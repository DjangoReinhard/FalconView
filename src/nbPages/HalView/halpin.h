#ifndef HALPIN_H
#define HALPIN_H
#include "halelement.h"

class HalSignal;


class HalPin : public HalElement
{
public:
  explicit HalPin(int pin, HalElement*  parent = nullptr);
  virtual ~HalPin();

  virtual QVariant data(int column) const override;
  virtual int next() const override;
  virtual int owner() const;

protected:
  QString typeName(int type) const;
  QString dirName(int dir) const;
  double  value() const;

private:
  HalSignal* sig;
  };
#endif // HALPIN_H
