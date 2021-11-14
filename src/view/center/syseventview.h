#ifndef SYSEVENTVIEW_H
#define SYSEVENTVIEW_H
#include <dynwidget.h>
class QTableView;
class SysEventModel;
class DBConnection;
class QSortFilterProxyModel;


class SysEventView : public DynWidget
{
  Q_OBJECT
public:
  static const QString className;
  explicit SysEventView(DBConnection& conn, QWidget* parent = nullptr);
  virtual ~SysEventView();

  virtual void connectSignals() override;
  virtual void updateStyles() override;
//  virtual void keyReleaseEvent(QKeyEvent *event) override;
  virtual void showEvent(QShowEvent* e) override;
  virtual void hideEvent(QHideEvent* e) override;

private:
  QTableView*            table;
  SysEventModel*         model;
  QSortFilterProxyModel* px;
  };
#endif // SYSEVENTVIEW_H
