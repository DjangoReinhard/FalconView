#ifndef ABSCENTERWIDGET_H
#define ABSCENTERWIDGET_H
#include <QWidget>
#include <PluginPageInterface.h>

QT_BEGIN_NAMESPACE
class CenterView;
class SettingsNotebook;
class QString;
class QAction;
class QFile;
QT_END_NAMESPACE


/*! loads widgets from uiFile and allows late initialization at page usage
 */
class AbstractCenterWidget : public QWidget, public PluginPageInterface
{
  Q_OBJECT
//  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "abstractCenterWidget.json")
  Q_INTERFACES(PluginPageInterface)
public:
  void     initialize(const QString& fileName, const QString& name, bool addScrollArea = false);
  QAction* viewAction();

  // called by central widget stack
  virtual void closeEvent(QCloseEvent* e) override; //I
  virtual void showEvent(QShowEvent* e) override;   //I
//  virtual void connectSignals() = 0;
//  virtual void updateStyles()   = 0;

signals:
  void dataChanged(AbstractCenterWidget* w, const QVariant& changed);

protected:
  explicit AbstractCenterWidget(QWidget* parent = nullptr);
  virtual ~AbstractCenterWidget() = default;

  virtual QWidget* createContent() override;  //I - default: load content from given filename

private:
  QAction*     vAction;
  QString      fileName;
  bool         addScrollArea;
  };
#endif // ABSCENTERWIDGET_H
