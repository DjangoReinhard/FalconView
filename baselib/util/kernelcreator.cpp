#include <kernelcreator.h>
#include <kernel.h>


Kernel* KernelCreator::kernel(const QString& fileName, const QString& appName, const QString& groupID) {
  return new Kernel(fileName, appName, groupID);
  }
