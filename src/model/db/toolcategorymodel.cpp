#include <toolcategorymodel.h>
#include <dbconnection.h>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>


ToolCategoryModel::ToolCategoryModel(DBConnection& conn, QObject *parent)
 : QSqlTableModel(parent) {
  if (!conn.connect()) {
     throw new QSqlError("failed to open database!");
     }
  setTable("Category");
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  select();

  qDebug() << "cat-columns" << columnCount();
  qDebug() << "cat-rows" << rowCount();
  }


bool ToolCategoryModel::createTable() {
  QSqlQuery sql;
  bool      rv;

  rv = sql.exec("CREATE TABLE \"Category\" (id      INT NOT NULL"
                                         ", parent  INT NOT NULL"
                                         ", name    VARCHAR(50) NOT NULL"
                                         ", PRIMARY KEY(id) )");
  return rv;
  }


QVariant ToolCategoryModel::headerData(int column, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
     switch (column) {
       case 0: return tr("id");
       case 1: return tr("name");
       case 2: return tr("parent");
       }
     }
  return QVariant();
  }


int ToolCategoryModel::nextId() const {
  QString   qs = QString("SELECT max(id) FROM Category");
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query next id" << q.lastError().text();
     }
  int nid = 0;

  if (q.next()) nid = q.value(0).toInt();

  return nid + 1;
  }
