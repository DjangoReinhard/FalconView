#include <kernelcreator.h>
#include <kernel.h>


Kernel* KernelCreator::kernel(const QStringList& appArgs, const QString& appName, const QString& groupID) {
  return new Kernel(appArgs, appName, groupID);
  }
