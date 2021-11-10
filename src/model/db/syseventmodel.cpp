#include <syseventmodel.h>
#include <dbconnection.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


SysEventModel::SysEventModel(DBConnection& conn, QObject *parent)
 : QSqlTableModel(parent) {
  if (!conn.connect()) {
     throw new QSqlError("failed to open database!");
     }
  setTable("SysEvent");
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  select();

  qDebug() << "sys-event-columns" << columnCount();
  qDebug() << "sys-event-rows" << rowCount();
  }


bool SysEventModel::createTable() {
  QSqlQuery sql;
  bool      rv;

  rv = sql.exec("CREATE TABLE \"SysEvents\" (id   INT NOT NULL"
                                          ", when INT NOT NULL"
                                          ", type INT NOT NULL"
                                          ", what VARCHAR(254) NOT NULL"
                                          ", PRIMARY KEY(id) )");
  return rv;
  }


QVariant SysEventModel::headerData(int c, Qt::Orientation o, int r) const {
  if (o == Qt::Horizontal && r == Qt::DisplayRole) {
     switch (c) {
       case 0: return tr("id");
       case 1: return tr("when");
       case 2: return tr("type");
       case 3: return tr("what");
       }
     }
  return QVariant();
  }

