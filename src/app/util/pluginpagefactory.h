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

  AbstractCenterWidget* createDockable(const   QString& name, bool flag = false);
  AbstractCenterWidget* createCenterPage(const QString& name);
  AbstractCenterWidget* createNotebookPage(const QString& name);

private:
  GuiCore*      core;
  Config*       cfg;
  ValueManager* vm;
  };
#endif // PLUGINPAGEFACTORY_H
