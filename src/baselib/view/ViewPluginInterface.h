#ifndef VIEWPLUGININTERFACE_H
#define VIEWPLUGININTERFACE_H
#include <QtPlugin>

class DBConnection;
class GuiCore;
QT_BEGIN_NAMESPACE
class QAction;
class QWidget;
class QCloseEvent;
class QShowEvent;
QT_END_NAMESPACE


class ViewPluginInterface
{
public:
  virtual ~ViewPluginInterface() = default;

  virtual void     closeEvent(QCloseEvent* e) = 0;
  virtual void     showEvent(QShowEvent* e)   = 0;

  virtual QWidget* createContent()  = 0;
  virtual void     connectSignals() = 0;
  virtual void     updateStyles()   = 0;
//  virtual QString  windowTitle()    = 0;
//  virtual QString  objectName()     = 0;
  };

QT_BEGIN_NAMESPACE
#define ViewPluginInterface_iid "de.schwarzrot.FalconView.ViewPlugin/0.1"
Q_DECLARE_INTERFACE(ViewPluginInterface, ViewPluginInterface_iid)
QT_END_NAMESPACE

#endif // VIEWPLUGININTERFACE_H
