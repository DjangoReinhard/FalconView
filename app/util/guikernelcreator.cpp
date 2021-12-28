#include <guikernelcreator.h>
#include <guikernel.h>


Kernel* GuiKernelCreator::kernel(const QString& fileName, const QString& appName, const QString& groupID) {
  return new GuiKernel(fileName, appName, groupID);
  }
