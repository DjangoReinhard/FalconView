#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QString>


class DBConnection
{
public:
  DBConnection(const QString& dbName, const QString& dbType = "QSQLITE");

  bool connect();

private:
  QString name;
  QString type;
  };

#endif // DBCONNECTION_H
