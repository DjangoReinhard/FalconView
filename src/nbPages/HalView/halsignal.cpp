#include "halsignal.h"
#include <rtapi.h>
#include <hal.h>
#include <hal_priv.h>
#include <QVariant>


HalSignal::HalSignal(int signal, HalElement* parent)
 : HalElement(parent) {
  if (signal) {
     p = static_cast<hal_sig_t*>((void*)(hal_shmem_base + signal));
     name = static_cast<hal_sig_t*>(p)->name;
     }
  }


HalSignal::~HalSignal() {
  }


QVariant HalSignal::data(int column) const {
  if (!column) return name;
  hal_sig_t* pSig = static_cast<hal_sig_t*>(p);
  hal_data_u* pData = (hal_data_u *) SHMPTR(pSig->data_ptr);

  return (double) pData->f;
  }


int HalSignal::next() const {
  return static_cast<hal_sig_t*>(p)->next_ptr;
  }
