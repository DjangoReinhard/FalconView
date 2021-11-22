#include <syseventmodel.h>
#include <dbconnection.h>
#include <sysevent.h>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


SysEventModel::SysEventModel(DBConnection& conn, QObject *parent)
 : QSqlTableModel(parent) {
  if (!conn.connect()) {
     throw new QSqlError("failed to open database!");
     }
  setTable("SysEvents");
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  select();

//  qDebug() << "sys-event-columns" << columnCount();
//  qDebug() << "sys-event-rows" << rowCount();
  }


bool SysEventModel::createTable() {
  QSqlQuery sql;
  bool      rv;

  rv = sql.exec("CREATE TABLE \"SysEvents\" (id   INT NOT NULL"
                                          ", sewhen INT NOT NULL"
                                          ", setype INT NOT NULL"
                                          ", what VARCHAR(254) NOT NULL"
                                          ", PRIMARY KEY(id) )");
  return rv;
  }


void SysEventModel::append(const SysEvent *e) {
  QSqlRecord r = record();

  if (!e) return;
  r.setValue("id", this->rowCount());
  r.setValue("sewhen", (qlonglong)e->when());
  r.setValue("setype", e->type());
  r.setValue("what", e->what());

  insertRecord(-1, r);
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

