#ifndef GUIKERNELCREATOR_H
#define GUIKERNELCREATOR_H
#include <kernelcreator.h>


class GuiKernelCreator : public KernelCreator
{
public:
  virtual KernelInterface* kernel(QApplication& app, const QString& appName, const QString& groupID);
  };

#endif // GUIKERNELCREATOR_H
