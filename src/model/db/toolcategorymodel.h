#ifndef TOOLCATEGORYMODEL_H
#define TOOLCATEGORYMODEL_H
#include <QSqlTableModel>
class DBConnection;
class FalconViewDB;


class ToolCategoryModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit ToolCategoryModel(DBConnection& conn, QObject *parent = nullptr);

  int      nextId() const;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

private:
  static bool  createTable();
  friend class FalconViewDB;
  };
#endif // TOOLCATEGORYMODEL_H
