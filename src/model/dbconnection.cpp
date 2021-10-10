#include <dbconnection.h>
#include <QSqlDatabase>


DBConnection::DBConnection(const QString& dbName, const QString& dbType)
 : name(dbName)
 , type(dbType) {
  }


bool DBConnection::connect() {
  if (QSqlDatabase::database().isValid()) {
     if (QSqlDatabase::database().isOpen()) return true;
     else                                   return QSqlDatabase::database().open();
     }
  QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

  db.setDatabaseName(name);
  db.setHostName("localhost");

  return db.open();
  }
