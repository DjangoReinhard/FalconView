#ifndef TOOLMODEL_H
#define TOOLMODEL_H
#include <QSqlTableModel>
#include <QIcon>
class FalconViewDB;
class DBConnection;
class GuiCore;


class ToolModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit ToolModel(DBConnection& conn, QObject *parent = nullptr);

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  QVariant promptData(int section, int role = Qt::DisplayRole) const;
  int      tools4Category(int categoryId);
  int      exportTools();
  int      maxToolNum();
  int      nextId();
  bool     existsToolNum(int toolNum);
  void     toggleSelection(int row);
  void     setCore(GuiCore* core);

private:
  static bool  createTable();
  QIcon    ui;
  QIcon    ci;
  GuiCore* core;
  friend class FalconViewDB;
  };
#endif // TOOLMODEL_H
