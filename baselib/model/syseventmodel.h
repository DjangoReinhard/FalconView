#ifndef SYSEVENTMODEL_H
#define SYSEVENTMODEL_H
#include <QSqlTableModel>
class DBConnection;
class FalconViewDB;
class SysEvent;


class SysEventModel : public QSqlTableModel
{
  Q_OBJECT
public:
  explicit SysEventModel(DBConnection& conn, QObject *parent = nullptr);

  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  void append(const SysEvent* e);

protected:
  int nextId();

private:
  static bool  createTable();
  friend class FalconViewDB;
  };
#endif // SYSEVENTMODEL_H
