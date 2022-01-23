#ifndef HALVIEW_H
#define HALVIEW_H
#include <abscenterwidget.h>

class HalModel;
QT_BEGIN_NAMESPACE
class QAction;
class QLineEdit;
class QTreeView;
QT_END_NAMESPACE


class HalView : public AbstractCenterWidget
{
  Q_OBJECT
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewCenterPage_iid" FILE "halView.json")
#endif
public:
  explicit HalView(QWidget* parent = nullptr);
  virtual ~HalView();

  virtual QWidget* createContent() override;
  virtual void     connectSignals() override;
  virtual void     updateStyles() override;

protected slots:
  void currentChanged(const QModelIndex &current, const QModelIndex &previous);
//  virtual bool eventFilter(QObject* o, QEvent* e) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;

private:
  QTreeView* tree;
  HalModel*  model;
  };
#endif // HALVIEW_H
