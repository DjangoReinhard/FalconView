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
  static const QString className;
  explicit LCToolTable(QWidget* parent = nullptr);
  virtual ~LCToolTable();

  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void keyReleaseEvent(QKeyEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;

private:
  QTableView*            table;
  ToolTable*             model;
  QSortFilterProxyModel* px;
  };
#endif // LCTOOLTABLE_H
