/* 
 * **************************************************************************
 * 
 *  file:       filemanager.h
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
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
#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <abscenterwidget.h>

QT_BEGIN_NAMESPACE
class QDir;
class QSplitter;
class QTreeView;
class QTableView;
class QPlainTextEdit;
class QSortFilterProxyModel;
class DirModel;
class FileModel;
class QItemSelection;
class QKeyEvent;
class QFileInfo;
class FileManagerClient;
QT_END_NAMESPACE


class FileManager : public AbstractCenterWidget
{
  Q_OBJECT
public:
  static const QString className;
  explicit FileManager(const QDir& baseDir, QWidget *parent = nullptr);

  virtual void connectSignals() override;
  virtual void updateStyles() override;
  virtual QWidget* createContent() override;
  void setClient(FileManagerClient* c);

signals:
  void fileSelected(const QString& filePath /*, bool switchPage = true*/);

public slots:
  void currentChanged(const QModelIndex& index);
  void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);

protected:
  virtual bool eventFilter(QObject* src, QEvent* event) override;
  virtual void showEvent(QShowEvent* event) override;
  virtual void closeEvent(QCloseEvent*) override;
  void createDirectory();
  void renameDirectory();

private:
  QSplitter*             spH;
  QSplitter*             spV;
  QTreeView*             dirs;
  QTableView*            files;
  QPlainTextEdit*        preView;
  DirModel*              dirModel;
  FileModel*             fileModel;
  QSortFilterProxyModel* pxDirs;
  QSortFilterProxyModel* pxFiles;
  FileManagerClient*     client;
  QFileInfo*             file2Copy;
  QFileInfo*             file2Move;
  };
#endif // FILEMANAGER_H
