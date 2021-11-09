#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H
#include <dynwidget.h>
class QDir;
class QSplitter;
class QTreeView;
class QTableView;
class QPlainTextEdit;
class QSortFilterProxyModel;
class CategoryTreeModel;
class ToolCategoryModel;
class ToolModel;
class ToolEditor;
class DBConnection;
class QItemSelection;
class QKeyEvent;


class ToolManager : public DynWidget
{
  Q_OBJECT
public:
  explicit ToolManager(DBConnection& conn, QWidget* parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles() override;

public slots:
  void currentChanged(const QModelIndex& index);
  void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

protected:
  virtual void keyReleaseEvent(QKeyEvent *event) override;
  virtual void showEvent(QShowEvent *event) override;
  void createCategory();
  void createTool();
  void deleteCategory();
  void deleteTool();
  void editTool();
  void renameCategory();
  void saveToolChanges();
  long timeStamp();

private:
  DBConnection&          conn;
  QSplitter*             spH;
  QSplitter*             spV;
  QTreeView*             categories;
  QTableView*            tools;
  CategoryTreeModel*     categoryTreeModel;
  ToolCategoryModel*     categoryTableModel;
  ToolModel*             toolModel;
  ToolEditor*            tEdit;
  QSize                  edSize;
  int                    tool2Edit;
  long                   tsMsgBox;
  QSortFilterProxyModel* pxCat;
  QSortFilterProxyModel* pxTools;
  };
#endif // TOOLMANAGER_H
