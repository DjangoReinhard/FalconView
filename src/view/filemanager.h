#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <dynwidget.h>
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


class FileManager : public DynWidget
{
  Q_OBJECT
public:
  explicit FileManager(const QDir& baseDir, QWidget *parent = nullptr);

  virtual void connectSignals();
  virtual void updateStyles();

signals:
  void fileSelected(QVariant filePath);

public slots:
  void currentChanged(const QModelIndex& index);
  void selectionChanged(const QItemSelection& selected, const QItemSelection& deselected);
  void toggleView();

protected:
  void keyReleaseEvent(QKeyEvent *event);

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
  };
#endif // FILEMANAGER_H
