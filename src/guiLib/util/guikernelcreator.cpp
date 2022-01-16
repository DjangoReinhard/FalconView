#include <guikernelcreator.h>
#include <guikernel.h>


Kernel* GuiKernelCreator::kernel(QApplication& app, const QString& appName, const QString& groupID) {
  return new GuiKernel(app, appName, groupID);
  }
