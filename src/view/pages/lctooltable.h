#ifndef LCTOOLTABLE_H
#define LCTOOLTABLE_H
#include <dyncenterwidget.h>
#include <QObject>
class QTableView;
class ToolTable;
class QSortFilterProxyModel;


class LCToolTable : public DynCenterWidget
{
  Q_OBJECT
public:
  static const QString className;
  explicit LCToolTable(QWidget* parent = nullptr);
  virtual ~LCToolTable();

  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual QWidget* createContent() override;

private:
  QTableView*            table;
  ToolTable*             model;
  QSortFilterProxyModel* px;
  };
#endif // LCTOOLTABLE_H
