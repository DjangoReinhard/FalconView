#ifndef FILEMODEL_H
#define FILEMODEL_H
#include <QAbstractTableModel>
#include <QFileInfo>


class FileModel : public QAbstractTableModel
{
  Q_OBJECT
public:
  explicit FileModel(QObject *parent = nullptr);
  FileModel(const QVector<QFileInfo>& contacts, QObject *parent = nullptr);

  int           rowCount(const QModelIndex &parent) const override;
  int           columnCount(const QModelIndex &parent) const override;
  QVariant      data(const QModelIndex &index, int role) const override;
  QVariant      headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QFileInfo     fileInfo(int row) const;
//  const QVector<QFileInfo*> &files() const;
  void          setupModel(const QString& baseDir);

private:
  QVector<QFileInfo> vFiles;
  };
#endif // FILEMODEL_H
