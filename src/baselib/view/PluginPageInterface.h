#ifndef PLUGINPAGEINTERFACE_H
#define PLUGINPAGEINTERFACE_H
#include <QtPlugin>

class DBConnection;
class GuiCore;
QT_BEGIN_NAMESPACE
class QWidget;
class QCloseEvent;
class QShowEvent;
QT_END_NAMESPACE


class PluginPageInterface
{
public:
  virtual ~PluginPageInterface() = default;

  virtual void closeEvent(QCloseEvent* e) = 0;
  virtual void showEvent(QShowEvent* e) = 0;

  virtual QWidget* createContent() = 0;
  virtual void connectSignals() = 0;
  virtual void updateStyles()   = 0;
  };

QT_BEGIN_NAMESPACE
#define PluginPageInterface_iid "de.schwarzrot.FalconView.PluginPage/0.1"
Q_DECLARE_INTERFACE(PluginPageInterface, PluginPageInterface_iid)
QT_END_NAMESPACE

#endif // PLUGINPAGEINTERFACE_H
