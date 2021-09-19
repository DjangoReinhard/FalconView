#ifndef TOOLCATEGORYMODEL_H
#define TOOLCATEGORYMODEL_H
#include <QSqlTableModel>


class ToolCategoryModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit ToolCategoryModel(QObject *parent = nullptr);

  int      nextId() const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  };
#endif // TOOLCATEGORYMODEL_H
