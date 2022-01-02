#ifndef PLUGINPAGEFACTORY_H
#define PLUGINPAGEFACTORY_H
class AbstractCenterWidget;
class GuiCore;
class AxisMask;
class Config;
class ValueManager;
class QString;


class PluginPageFactory
{
public:
  explicit PluginPageFactory();
  virtual ~PluginPageFactory();

  AbstractCenterWidget* createDockable(const   QString& name, bool horizontal = true);
  AbstractCenterWidget* createCenterPage(const QString& name);

private:
  GuiCore*      core;
  Config*       cfg;
  ValueManager* vm;
//  AxisMask*     axisMask;
  };
#endif // PLUGINPAGEFACTORY_H
