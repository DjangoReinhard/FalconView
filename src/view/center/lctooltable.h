#ifndef LCTOOLTABLE_H
#define LCTOOLTABLE_H
#include <dynwidget.h>
#include <QObject>
class QTableView;
class ToolTable;
class QSortFilterProxyModel;


class LCToolTable : public DynWidget
{
  Q_OBJECT
public:
  explicit LCToolTable(QWidget* parent = nullptr);
  virtual ~LCToolTable();

  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void keyReleaseEvent(QKeyEvent *event) override;

private:
  QTableView*            table;
  ToolTable*             model;
  QSortFilterProxyModel* px;
  };
#endif // LCTOOLTABLE_H
