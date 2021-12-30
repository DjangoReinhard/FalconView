#ifndef FIXTUREMANAGER_H
#define FIXTUREMANAGER_H
#include <abscenterwidget.h>
#include <PluginPageInterface.h>

QT_BEGIN_NAMESPACE
class FixtureEdit;
class AxisMask;
QT_END_NAMESPACE


class FixtureManager : public AbstractCenterWidget
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "fixtureManager.json")
  Q_INTERFACES(PluginPageInterface)
public:
  FixtureManager(QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles()   override;
  void activateEditor(int index);

protected:
  virtual void keyPressEvent(QKeyEvent* event) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual QWidget* createContent() override;

private:
  QWidget*  client;
  QFont     cFonts[4];
  QString   cStyle[4];
  AxisMask* axisMask;
  };
#endif // FIXTUREMANAGER_H
