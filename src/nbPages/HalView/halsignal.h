#ifndef HALSIGNAL_H
#define HALSIGNAL_H
#include "halelement.h"

class QVariant;


class HalSignal : public HalElement
{
public:
  explicit HalSignal(int signal, HalElement* parent = nullptr);
  virtual ~HalSignal();

  virtual int      next() const;
  virtual QVariant data(int column) const;
  };
#endif // HALSIGNAL_H
