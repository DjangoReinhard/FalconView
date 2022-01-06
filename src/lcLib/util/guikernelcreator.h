#ifndef GUIKERNELCREATOR_H
#define GUIKERNELCREATOR_H
#include <kernelcreator.h>


class GuiKernelCreator : public KernelCreator
{
public:
  virtual Kernel* kernel(const QStringList& appArgs, const QString& appName, const QString& groupID);
  };

#endif // GUIKERNELCREATOR_H
