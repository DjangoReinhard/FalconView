#ifndef DIRMODEL_H
#define DIRMODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
class DirEntry;


class DirModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit DirModel(const QString& baseDir, QObject *parent = nullptr);
  ~DirModel();

  QVariant      data(const QModelIndex& index, int role) const override;
  QVariant      headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QModelIndex   index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex   parent(const QModelIndex& index) const override;
  Qt::ItemFlags flags(const QModelIndex&index) const override;
  DirEntry*     root() const;
  DirEntry*     getItem(const QModelIndex& index) const;
  int           rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int           columnCount(const QModelIndex& parent = QModelIndex()) const override;
  bool          insertDirectory(const QModelIndex& parentIdx, DirEntry* entry);
  bool          setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
  void          setupModelData(const QString& baseDir, DirEntry* parent);

  DirEntry*     rootItem;
  };
#endif // DIRMODEL_H
