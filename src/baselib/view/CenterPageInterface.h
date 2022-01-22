#ifndef CENTERPAGEINTERFACE_H
#define CENTERPAGEINTERFACE_H
#include <ViewPluginInterface.h>


class CenterPageInterface : public virtual ViewPluginInterface
{
public:
  virtual ~CenterPageInterface() = default;

  virtual QAction* viewAction() = 0;
  };

QT_BEGIN_NAMESPACE
#define CenterPageInterface_iid "de.schwarzrot.FalconView.CenterPage/0.1"
Q_DECLARE_INTERFACE(CenterPageInterface, CenterPageInterface_iid)
QT_END_NAMESPACE

#endif // CENTERPAGEINTERFACE_H
