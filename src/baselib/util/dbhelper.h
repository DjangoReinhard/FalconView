#ifndef DBHELPER_H
#define DBHELPER_H
#include <QString>
class DBConnection;


class DBHelper
{
public:
  virtual bool          connect(const QString& path)         = 0;
  virtual DBConnection* createDatabase(const QString& path)  = 0;
  virtual void          createSampleData(DBConnection& conn) = 0;
  DBConnection*         dbConnection() { return conn; }

protected:
  DBConnection* conn;
  };
#endif // DBHELPER_H
