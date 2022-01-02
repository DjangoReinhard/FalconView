#ifndef MDIEDITORINTERFACE_H
#define MDIEDITORINTERFACE_H
#include <PluginPageInterface.h>


class MDIEditorInterface : public PluginPageInterface
{
public:
  virtual ~MDIEditorInterface() = default;

  virtual void    append(const QString& command) = 0;
  virtual QString command() const                = 0;
  };

QT_BEGIN_NAMESPACE
#define MDIEditorInterface_iid "de.schwarzrot.FalconView.MDIEditor/0.1"
Q_DECLARE_INTERFACE(MDIEditorInterface, MDIEditorInterface_iid)
QT_END_NAMESPACE

#endif // MDIEDITORINTERFACE_H
