#include <kernelcreator.h>
#include <kernel.h>


KernelInterface* KernelCreator::kernel(QApplication& app, const QString& appName, const QString& groupID) {
  return new Kernel(app, appName, groupID);
  }
