#include <kernelcreator.h>
#include <kernel.h>


Kernel* KernelCreator::kernel(QApplication& app, const QString& appName, const QString& groupID) {
  return new Kernel(app, appName, groupID);
  }
