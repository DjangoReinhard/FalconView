#ifndef ABSCENTERWIDGET_H
#define ABSCENTERWIDGET_H
#include <QWidget>
#include <PluginPageInterface.h>

QT_BEGIN_NAMESPACE
class CenterView;
class DBConnection;
class SettingsNotebook;
class PluginPageFactory;
class ValueManager;
class GuiCore;
class Config;
class QString;
class QAction;
class QFile;
QT_END_NAMESPACE


/*! loads widgets from uiFile and allows late initialization at page usage
 */
class AbstractCenterWidget : public QWidget, public PluginPageInterface
{
  Q_OBJECT
  Q_INTERFACES(PluginPageInterface)
public:
  QAction*     viewAction();

  // called by central widget stack
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void showEvent(QShowEvent* e) override;

signals:
  void dataChanged(AbstractCenterWidget* w, const QVariant& changed);

protected:
  explicit AbstractCenterWidget(QWidget* parent = nullptr);
  virtual ~AbstractCenterWidget() = default;

  virtual void initialize(const QString& uiFile = QString(), const QString& name = QString(), bool addScrollArea = false);
  virtual void patch(void* pk, void* pc, void* pv, void* pu = nullptr);
  virtual QWidget* createContent() override;

  GuiCore*      core;
  Config*       cfg;
  ValueManager* vm;

private:
  QAction*      vAction;
  QString       fileName;
  bool          addScrollArea;
  friend class PluginPageFactory;
  };
#endif // ABSCENTERWIDGET_H
