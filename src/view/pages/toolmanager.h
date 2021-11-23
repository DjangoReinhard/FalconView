#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H
#include <dyncenterwidget.h>
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


class ToolManager : public DynCenterWidget
{
  Q_OBJECT
public:
  static const QString& className;
  explicit ToolManager(DBConnection& conn, QWidget* parent = nullptr);
  virtual ~ToolManager();

  virtual void connectSignals() override;
  virtual void updateStyles() override;

public slots:
  void currentChanged(const QModelIndex& index);
  void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

protected:
  virtual void keyReleaseEvent(QKeyEvent *event) override;
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual QWidget* createContent() override;
  void createCategory();
  void createTool();
  void deleteCategory();
  void deleteTool();
  void editTool();
  void renameCategory();
  void saveToolChanges();

private:
  DBConnection&          conn;
  QSplitter*             spH;
  QTreeView*             categories;
  QSplitter*             spV;
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
