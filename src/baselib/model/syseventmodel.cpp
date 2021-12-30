#include <syseventmodel.h>
#include <dbconnection.h>
#include <sysevent.h>
#include <core.h>
#include <QDateTime>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


SysEventModel::SysEventModel(DBConnection& conn, QObject *parent)
 : QSqlTableModel(parent) {
  if (!conn.connect()) throw new QSqlError("failed to open database!");
  setTable("SysEvents");
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  select();
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


QVariant SysEventModel::data(const QModelIndex& idx, int role) const {
  if (role == Qt::DisplayRole) {
     switch (idx.column()) {
       case 1: { // when
            long t = QSqlTableModel::data(idx, role).toInt();

#ifdef HAVE_DATETIME
            return QDateTime::fromSecsSinceEpoch(t);
#else
            return QTime::fromMSecsSinceStartOfDay(t);
#endif
            } break;
       case 2: { // type
            SysEvent::EventType t = static_cast<SysEvent::EventType>(QSqlTableModel::data(idx, role).toInt());

            return SysEvent::toString(t);
            } break;
       default: break;
       }
     }
  return QSqlTableModel::data(idx, role);
  }


int SysEventModel::nextId() {
  QString   qs = QString("SELECT max(id) FROM SysEvents");
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query max id" << q.lastError().text();
     return -1;
     }
  int tNum = 0;

  if (q.next()) tNum = q.value(0).toInt();
  revertAll();

  return tNum + 1;
  }


void SysEventModel::append(const SysEvent *e) {
  QSqlRecord r = record();

  if (!e) return;

  r.setValue("id", nextId());
  r.setValue("sewhen", (qlonglong)e->when());
  r.setValue("setype", e->type());
  r.setValue("what", e->what());

  qDebug() << "SEmodel:" << r;

  if (!insertRecord(-1, r))
     Core().riseError(this->lastError().text());
  if (!submitAll())
     Core().riseError(this->lastError().text());
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

