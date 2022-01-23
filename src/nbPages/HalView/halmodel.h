#ifndef HALMODEL_H
#define HALMODEL_H
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
class HalElement;


class HalModel : public QAbstractItemModel
{
  Q_OBJECT
public:
  explicit HalModel(QObject *parent = nullptr);
  ~HalModel();

  QVariant      data(const QModelIndex& index, int role) const override;
  QVariant      headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QModelIndex   index(int row, int column, const QModelIndex& parent = QModelIndex()) const override;
  QModelIndex   parent(const QModelIndex& index) const override;
  Qt::ItemFlags flags(const QModelIndex&index) const override;
//  HalElement*   root() const;
  HalElement*   getItem(const QModelIndex& index) const;
  int           rowCount(const QModelIndex& parent = QModelIndex()) const override;
  int           columnCount(const QModelIndex& parent = QModelIndex()) const override;
//  bool          insertDirectory(const QModelIndex& parentIdx, HalElement* entry);
//  bool          setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

private:
  void          setupModelData(HalElement* parent);
  void          processPins(int component, HalElement*);

  HalElement*   root;
  QString       name;
  int           compID;
  };
#endif // HALMODEL_H
