#include <guikernelcreator.h>
#include <guikernel.h>
#include "rs274ngc.hh"


KernelInterface* GuiKernelCreator::kernel(QApplication& app, const QString& appName, const QString& groupID) {
  return new GuiKernel(ACTIVE_G_CODES, ACTIVE_M_CODES, app, appName, groupID);
  }
