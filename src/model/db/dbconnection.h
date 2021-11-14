#ifndef DBCONNECTION_H
#define DBCONNECTION_H
#include <QString>


class DBConnection
{
public:
  DBConnection(const QString& dbName, const QString& dbType = "QSQLITE");
  DBConnection(const DBConnection& conn);

  bool connect();
  const QString& dbName() const { return name; }
  const QString& dbType() const { return type; }

private:
  QString name;
  QString type;
  };

#endif // DBCONNECTION_H
