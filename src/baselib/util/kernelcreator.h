#ifndef KERNELCREATOR_H
#define KERNELCREATOR_H
class QApplication;
class QString;
class KernelInterface;


class KernelCreator
{
public:
  virtual KernelInterface* kernel(QApplication& app, const QString& appName, const QString& groupID) = 0;
  };
#endif // KERNELCREATOR_H
