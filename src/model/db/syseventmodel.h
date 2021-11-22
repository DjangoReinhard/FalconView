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

  QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
  void append(const SysEvent* e);

private:
  static bool  createTable();
  friend class FalconViewDB;
  };
#endif // SYSEVENTMODEL_H
