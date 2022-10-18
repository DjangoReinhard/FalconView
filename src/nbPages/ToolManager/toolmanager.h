/* 
 * **************************************************************************
 * 
 *  file:       toolmanager.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    22.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
#ifndef TOOLMANAGER_H
#define TOOLMANAGER_H
#include <abscenterwidget.h>
#include <dbhelper.h>
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


class ToolManager : public AbstractCenterWidget, public DBHelperInterface
{
  Q_OBJECT
  Q_INTERFACES(DBHelperInterface)
#ifdef USE_PLUGINS
  Q_PLUGIN_METADATA(IID "ViewPluginInterface_iid" FILE "toolManagerV.json")
  Q_PLUGIN_METADATA(IID "DBHelperInterface_iid" FILE "toolManagerD.json")
#endif
public:
  explicit ToolManager(QWidget* parent = nullptr);
  virtual ~ToolManager();

  virtual void          connectSignals() override;
  virtual void          updateStyles() override;
  virtual bool          connect(const QString& path);
  virtual DBConnection* createDatabase(const QString& path);
  virtual void          createSampleData(DBConnection& conn);

public slots:
  void currentChanged(const QModelIndex& index);
  void setSize(int w, int h);
  void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

protected:
  virtual void showEvent(QShowEvent *event) override;
  virtual void closeEvent(QCloseEvent*) override;
  virtual bool eventFilter(QObject*, QEvent* e) override;
  virtual QWidget* createContent() override;
  void createCategory();
  void createTool();
  void deleteCategory();
  void deleteTool();
  void editTool();
  void renameCategory();
  void saveToolChanges();

private:
  DBConnection*          conn;
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
