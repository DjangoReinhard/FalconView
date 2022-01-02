#ifndef GCODEVIEWERINTERFACE_H
#define GCODEVIEWERINTERFACE_H
#include <PluginPageInterface.h>


class GCodeViewerInterface : public PluginPageInterface
{
public:
  virtual ~GCodeViewerInterface() = default;

  virtual QString currentRow() const = 0;
  virtual long    curLine() const    = 0;
  };

QT_BEGIN_NAMESPACE
#define GCodeViewerInterface_iid "de.schwarzrot.FalconView.GCodeViewer/0.1"
Q_DECLARE_INTERFACE(GCodeViewerInterface, GCodeViewerInterface_iid)
QT_END_NAMESPACE

#endif // GCODEVIEWERINTERFACE_H
