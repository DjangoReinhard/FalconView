#ifndef SYSEVENTVIEW_H
#define SYSEVENTVIEW_H
#include <abscenterwidget.h>
#include <CenterPageInterface.h>

QT_BEGIN_NAMESPACE
class QTableView;
class QAction;
class SysEventModel;
class DBConnection;
class QSortFilterProxyModel;
QT_END_NAMESPACE


class SysEventView : public AbstractCenterWidget, public CenterPageInterface
{
  Q_OBJECT
  Q_INTERFACES(CenterPageInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "CenterPageInterface_iid" FILE "sysEventView.json")
#endif
public:
  explicit SysEventView(QWidget* parent = nullptr);
  virtual ~SysEventView();

protected:
  virtual void closeEvent(QCloseEvent* e) override;
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual bool eventFilter(QObject* o, QEvent* e) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual QWidget* createContent() override;
  virtual QAction* viewAction() override;

private:
  QTableView*            table;
  SysEventModel*         model;
  QSortFilterProxyModel* px;
  };
#endif // SYSEVENTVIEW_H
