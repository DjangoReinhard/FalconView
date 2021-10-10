#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H
#include <QWidget>
class QDir;
class QSplitter;
class QTreeView;
class QTableView;
class QPlainTextEdit;
class QSortFilterProxyModel;
class ToolCategoryModel;
class ToolModel;
class QItemSelection;
class QKeyEvent;


class ToolManager : public QWidget
{
  Q_OBJECT
public:
  explicit ToolManager(QWidget *parent = nullptr);

public slots:
  void currentChanged(const QModelIndex& index);
  void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
  void toggleView();

protected:
  void keyReleaseEvent(QKeyEvent *event);

private:
  QSplitter*             spH;
  QSplitter*             spV;
  QTreeView*             categories;
  QTableView*            tools;
  QPlainTextEdit*        preView;
  ToolCategoryModel*     categoryModel;
  ToolModel*             toolModel;
  QSortFilterProxyModel* pxCat;
  QSortFilterProxyModel* pxTools;
  };
#endif // TOOLMANAGER_H
