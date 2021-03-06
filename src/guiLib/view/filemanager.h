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
