#ifndef SYSEVENTVIEW_H
#define SYSEVENTVIEW_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class QTableView;
class SysEventModel;
class DBConnection;
class QSortFilterProxyModel;
QT_END_NAMESPACE


class SysEventView : public AbstractCenterWidget
{
  Q_OBJECT
public:
  static const QString className;
  explicit SysEventView(DBConnection& conn, QWidget* parent = nullptr);
  virtual ~SysEventView();

protected:
  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual bool eventFilter(QObject* o, QEvent* e) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual QWidget* createContent() override;

private:
  QTableView*            table;
  SysEventModel*         model;
  QSortFilterProxyModel* px;
  };
#endif // SYSEVENTVIEW_H
