#ifndef ABSCENTERWIDGET_H
#define ABSCENTERWIDGET_H
#include <QWidget>
#include <PluginPageInterface.h>

QT_BEGIN_NAMESPACE
class CenterView;
class DBConnection;
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
  Q_INTERFACES(PluginPageInterface)
public:
  void     initialize(const QString& fileName = QString(), const QString& name = QString(), DBConnection* conn = nullptr, bool addScrollArea = false);
  QAction* viewAction();

  // called by central widget stack
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void showEvent(QShowEvent* e) override;

signals:
  void dataChanged(AbstractCenterWidget* w, const QVariant& changed);

protected:
  explicit AbstractCenterWidget(QWidget* parent = nullptr);
  virtual ~AbstractCenterWidget() = default;

  virtual QWidget* createContent() override;
  virtual void dbSetup(DBConnection* conn) override;

private:
  QAction*     vAction;
  QString      fileName;
  bool         addScrollArea;
  };
#endif // ABSCENTERWIDGET_H
