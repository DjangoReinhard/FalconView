#include <dbconnection.h>
#include <QSqlDatabase>
#include <QFileInfo>


DBConnection::DBConnection(const QString& dbName, const QString& dbType)
 : name(dbName)
 , type(dbType) {
  if (!dbName.contains('/')) {
     QFileInfo dbPath(QString("../FalconView/db/") + dbName);

     name = dbPath.absoluteFilePath();
     }
  }


DBConnection::DBConnection(const DBConnection& other)
 : name(other.name)
 , type(other.type) {
  }


bool DBConnection::connect() {
  if (QSqlDatabase::database().isValid()) {
     if (QSqlDatabase::database().isOpen()) return true;
     else                                   return QSqlDatabase::database().open();
     }
  QSqlDatabase db = QSqlDatabase::addDatabase(type);

  db.setDatabaseName(name);
  db.setHostName("localhost");

  return db.open();
  }
