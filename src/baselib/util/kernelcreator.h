#ifndef KERNELCREATOR_H
#define KERNELCREATOR_H

class QApplication;
class QString;
class Kernel;


class KernelCreator
{
public:
  virtual Kernel* kernel(QApplication& app, const QString& appName, const QString& groupID);
  };

#endif // KERNELCREATOR_H
