#ifndef DBHELPER_H
#define DBHELPER_H
class DBConnection;
class QString;


class DBHelper
{
public:
  virtual DBConnection* createDatabase(const QString& path)  = 0;
  virtual void          createSampleData(DBConnection& conn) = 0;
  DBConnection*         dbConnection() { return conn; }

protected:
  DBConnection* conn;
  };
#endif // DBHELPER_H
