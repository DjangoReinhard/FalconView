#ifndef KERNELCREATOR_H
#define KERNELCREATOR_H

class QString;
class Kernel;


class KernelCreator
{
public:
  virtual Kernel* kernel(const QString& fileName, const QString& appName, const QString& groupID);
  };

#endif // KERNELCREATOR_H
