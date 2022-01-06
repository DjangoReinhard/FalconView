#include <guikernelcreator.h>
#include <guikernel.h>


Kernel* GuiKernelCreator::kernel(const QStringList& appArgs, const QString& appName, const QString& groupID) {
  return new GuiKernel(appArgs, appName, groupID);
  }
