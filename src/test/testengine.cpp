#include <axismask.h>
#include <equalcondition.h>
#include <smallercondition.h>
#include <greatercondition.h>
#include <valuemodel.h>
#include <QObject>
#include <QDebug>
#include <QStandardPaths>
#include <QSettings>
#include <QtTest/QTest>


class TestEngine : public QObject
{
  Q_OBJECT
public slots:
  void updateCondition(bool result) {
//    qDebug() << "TEST --- updateCondition to " << (result ? "true" : "false");
    this->result = result;
    };

private slots:
  void test3Axis();
  void test5Axis();
  void test9Axis();
  void tellStdPaths();
  void writeSettings();
  void readSettings();
  void testEqualCondition();
  void testSmallerCondition();
  void testGreaterCondition();

  void init() { result = true; }

private:
  volatile bool result;
  };


void TestEngine::testEqualCondition() {
  ValueModel v("equal", 3);
  EqualCondition c(&v, 7);

  connect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = c.result(), false);

  v.setValue(7);

  QCOMPARE(result, true);
  this->disconnect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testSmallerCondition() {
  ValueModel v("small", 3.14);
  SmallerCondition c(&v, 2.0);

  connect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = c.result(), false);

  v.setValue(1.15);

  QCOMPARE(result, true);
  this->disconnect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testGreaterCondition() {
  ValueModel v("great", 97);
  GreaterCondition c(&v, 114);

  connect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = c.result(), false);

  v.setValue(120);

  QCOMPARE(result, true);
  this->disconnect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::test3Axis() {
  AxisMask am(0x07);

  QCOMPARE(am.activeAxis(), 3);
  }


void TestEngine::test5Axis() {
  AxisMask am(0x01F);

  QCOMPARE(am.activeAxis(), 5);
  }


void TestEngine::test9Axis() {
  AxisMask am(0x01FF);

  QCOMPARE(am.activeAxis(), 9);
  }


void TestEngine::tellStdPaths() {
  QStringList sl = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);

  for (QString s : sl) {
      qDebug() << "app config location: " << s;
      }
  sl = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
  for (QString s : sl) {
      qDebug() << "home location: " << s;
      }
  }


void TestEngine::writeSettings() {
  QSettings cfg(QSettings::UserScope, "SRD", "QtUi");

  cfg.setValue("whatEver", "ich bin ein Nasenbär");
  }


void TestEngine::readSettings() {
  QSettings cfg(QSettings::UserScope, "SRD", "QtUi");
  QVariant we = cfg.value("whatEver");

  QCOMPARE(we.toString(), "ich bin ein Nasenbär");
  }


QTEST_MAIN(TestEngine)
#include "testengine.moc"
