#ifndef HALCOMPONENT_H
#define HALCOMPONENT_H
#include "halelement.h"


class HalComponent : public HalElement
{
public:
  explicit HalComponent(int component, HalElement* parent = nullptr);
  virtual ~HalComponent();

  virtual int next() const override;
  };
#endif // HALCOMPONENT_H
