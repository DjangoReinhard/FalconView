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
  explicit SysEventView(DBConnection& conn, QWidget* parent = nullptr);
  virtual ~SysEventView();

  virtual void connectSignals() override;
  virtual void updateStyles() override;
//  virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
  QTableView*            table;
  SysEventModel*         model;
  QSortFilterProxyModel* px;
  };
#endif // SYSEVENTVIEW_H
