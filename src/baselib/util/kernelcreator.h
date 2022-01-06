#ifndef KERNELCREATOR_H
#define KERNELCREATOR_H

class QStringList;
class QString;
class Kernel;


class KernelCreator
{
public:
  virtual Kernel* kernel(const QStringList& appArgs, const QString& appName, const QString& groupID);
  };

#endif // KERNELCREATOR_H
