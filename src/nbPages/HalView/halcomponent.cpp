#include "halcomponent.h"
#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>


HalComponent::HalComponent(int component, HalElement* parent)
 : HalElement(parent) {
  p = static_cast<hal_comp_t*>((void*)(hal_shmem_base + component));
  if (component) name = static_cast<hal_comp_t*>(p)->name;
  else           name = "Root";
  }


HalComponent::~HalComponent() {
  }


int HalComponent::next() const {
  return static_cast<hal_comp_t*>(p)->next_ptr;
  }
