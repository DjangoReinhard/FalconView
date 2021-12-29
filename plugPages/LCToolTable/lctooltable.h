#ifndef LCTOOLTABLE_H
#define LCTOOLTABLE_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class QTableView;
class ToolTable;
class QSortFilterProxyModel;
QT_END_NAMESPACE


class LCToolTable : public AbstractCenterWidget
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "PluginPageInterface_iid" FILE "lcToolTable.json")
public:
  static const QString className;
  explicit LCToolTable(QWidget* parent = nullptr);
  virtual ~LCToolTable();

  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual void keyPressEvent(QKeyEvent *event) override;
  virtual void keyReleaseEvent(QKeyEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual QWidget* createContent() override;

protected slots:
  void modelChanged();

private:
  QTableView*            table;
  ToolTable*             model;
  QSortFilterProxyModel* px;
  };
#endif // LCTOOLTABLE_H
