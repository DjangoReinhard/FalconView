#include <QtTest/QTest>
#include <QSqlDatabase>
#include <QDomDocument>
#include <QVariant>
#include <QtSql>
#include <QDebug>


class TestDB : public QObject
{
  Q_OBJECT
public:

protected:
  void dumpFields(const QSqlRecord& rec);

private slots:
  void countEntries();
  void listTools();
  void listCategories();
  void listSysEvents();
  void cleanupTestCase() {
    QSqlDatabase::database().close();
    }
  void init() {
    }
  void initTestCase() {
    qDebug() << "init TestEngine ...";
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

    db.setDatabaseName("../FalconView/db/FalconView");
    db.setHostName("localhost");

    QCOMPARE(db.open(), true);
    }

private:
  QMap<QString, int> toolCategories;
  };


void TestDB::countEntries() {
  QSqlTableModel tm;

  tm.setTable("Tools");
  tm.select();
  int mx = tm.rowCount();

  QVERIFY(mx == 41);
  qDebug() << "found #" << mx << " tool entries";

  tm.setTable("Category");
  tm.select();
  mx = tm.rowCount();

  QVERIFY(mx == 9);
  qDebug() << "found #" << mx << " tool categories";
  }


void TestDB::listTools() {
  QSqlTableModel tm;

  tm.setTable("Tools");
  tm.select();
  int mx = tm.rowCount();

  QVERIFY(mx > 0);

  for (int i=0; i < mx; ++i) {
      QSqlRecord rec = tm.record(i);
      int fc = rec.count();

      qDebug() << "\ntool #" << i;
      for (int j=0; j < fc; ++j) {
          QSqlField fld = rec.field(j);

          qDebug() << fld.name() << "\t=> " << fld.value();
          }
      }
  }

void TestDB::listCategories() {
  QSqlTableModel tm;

  tm.setTable("Category");
  tm.select();
  int mx = tm.rowCount();

  QVERIFY(mx > 0);

  for (int i=0; i < mx; ++i) {
      QSqlRecord rec = tm.record(i);
      int fc = rec.count();

      qDebug() << "\ncategory #" << i;
      for (int j=0; j < fc; ++j) {
          QSqlField fld = rec.field(j);

          qDebug() << fld.name() << "\t=> " << fld.value();
          }
      }
  }


void TestDB::listSysEvents() {
  QSqlTableModel tm;

  tm.setTable("SysEvents");
  tm.select();
  int mx = tm.rowCount();

  QVERIFY(mx > 0);

  for (int i=0; i < mx; ++i) {
      QSqlRecord rec = tm.record(i);
      int fc = rec.count();

      qDebug() << "\nsys-event #" << i;
      for (int j=0; j < fc; ++j) {
          QSqlField fld = rec.field(j);

          qDebug() << fld.name() << "\t=> " << fld.value();
          }
      }
  }

void TestDB::dumpFields(const QSqlRecord &rec) {
  for (int i=0; i < rec.count(); ++i) {
      QSqlField fld = rec.field(i);

      qDebug() << "field: " << fld.name();
      }
  }


QTEST_MAIN(TestDB)
#include "testDB.moc"
