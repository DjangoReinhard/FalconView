#ifndef FALCONVIEWDB_H
#define FALCONVIEWDB_H
#include <dbhelper.h>
#include <QVariant>
class QSqlTableModel;
class QSqlField;


class FalconViewDB : public DBHelper
{
public:
  FalconViewDB(const QString& name);

  virtual DBConnection* createDatabase(const QString& path);
  virtual void          createSampleData(DBConnection& conn);

protected:
  QString        xml2Sql(const QString& name) const;
  QVariant::Type colType4(const QString& columnName) const;
  void           createCategory(QSqlTableModel& model, QSqlField &fId, QSqlField &fProfile, QSqlField &fName, const QString &category);

private:
  QMap<QString, int> toolCategories;
  };
#endif // FALCONVIEWDB_H
