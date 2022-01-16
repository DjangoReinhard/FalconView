#include <equalcondition.h>
#include <smallercondition.h>
#include <greatercondition.h>
#include <notcondition.h>
#include <andcondition.h>
#include <orcondition.h>
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
    qDebug() << "TEST <<<--- updateCondition to -->>" << (result ? "true" : "false") << "<<";
    this->result = result;
    };

private slots:
//  void tellStdPaths();
//  void writeSettings();
//  void readSettings();
  void testEqualCondition();
  void testSmallerCondition();
  void testGreaterCondition();
  void testAndCondition();
  void testAnd3Condition();
  void testAnd4Condition();
  void testOrCondition();
  void testBoolean();

  void init() { result = true; }

private:
  volatile bool result;
  };

#ifndef REDNOSE
void TestEngine::testEqualCondition() {
  ValueModel v("equal", 3);
  EqualCondition c(&v, 7);

  connect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = c.result(), false);

  v.setValue(7);

  QCOMPARE(result, true);
  disconnect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testSmallerCondition() {
  ValueModel v("small", 3.14);
  SmallerCondition c(&v, 2.0);

  connect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = c.result(), false);

  v.setValue(1.15);

  QCOMPARE(result, true);
  disconnect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testGreaterCondition() {
  ValueModel v("great", 97);
  GreaterCondition c(&v, 114);

  connect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = c.result(), false);

  v.setValue(120);

  QCOMPARE(result, true);
  disconnect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testAndCondition() {
  ValueModel v0("left", 13);
  ValueModel v1("right", 3);
  GreaterCondition gc(&v0, 20);
  NotCondition     nc(&v1, 3);
  AndCondition     ac(&gc, &nc);

  connect(&ac, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = ac.result(), false);

  qDebug() << "set v0 to 32";
  v0.setValue(32);

  QCOMPARE(result, false);

  qDebug() << "set v1 to 5";
  v1.setValue(5);

  QCOMPARE(result, true);
  disconnect(&ac, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testAnd3Condition() {
  ValueModel v0("left", 13);
  ValueModel v1("middle", 1);
  ValueModel v2("right", 3);
  GreaterCondition gc(&v0, 20);
  NotCondition     nc(&v1, 1);
  SmallerCondition sc(&v2, 0);
  AndCondition    ac(&gc, &nc);

  ac.addCondition(&sc);
  connect(&ac, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = ac.result(), false);

  qDebug() << "set v0 to 32";
  v0.setValue(32);

  QCOMPARE(result, false);

  qDebug() << "set v1 to 9";
  v1.setValue(9);

  QCOMPARE(result, false);

  qDebug() << "set v2 to -5";
  v2.setValue(-5);

  QCOMPARE(result, true);
  disconnect(&ac, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testAnd4Condition() {
  ValueModel v0("left", 3);
  ValueModel v1("midl", 5);
  ValueModel v2("midr", 9);
  ValueModel v3("right", 13);
  GreaterCondition g0c(&v0, 13);
  NotCondition     nc(&v1, 5);
  SmallerCondition sc(&v2, 1);
  GreaterCondition g1c(&v3, 33);
  AndCondition    ac(&g0c, &nc);

  ac.addCondition(&sc);
  ac.addCondition(&g1c);
  connect(&ac, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = ac.result(), false);

  qDebug() << "set v0 to 15";
  v0.setValue(15);

  QCOMPARE(result, false);

  qDebug() << "set v1 to 0";
  v1.setValue(0);

  QCOMPARE(result, false);

  qDebug() << "set v2 to -2";
  v2.setValue(-2);

  QCOMPARE(result, false);

  qDebug() << "set v3 to 35";
  v3.setValue(35);

  QCOMPARE(result, true);
  disconnect(&ac, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


void TestEngine::testOrCondition() {
  ValueModel v0("left", 13);
  ValueModel v1("right", 3);
  GreaterCondition gc(&v0, 20);
  NotCondition     nc(&v1, 3);
  OrCondition      oc(&gc, &nc);

  connect(&oc, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = oc.result(), false);

  qDebug() << "set v0 to 32";
  v0.setValue(32);

  QCOMPARE(result, true);

  qDebug() << "set v0 to 17";
  v0.setValue(17);

  QCOMPARE(result, false);

  qDebug() << "set v1 to 5";
  v1.setValue(5);

  QCOMPARE(result, true);
  disconnect(&oc, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }
#endif

void TestEngine::testBoolean() {
  ValueModel     v("equal", true);
  EqualCondition c(&v, false);

  connect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);

  QCOMPARE(result = c.result(), false);

  v.setValue(false);

  QCOMPARE(result, true);

  v.setValue(true);

  QCOMPARE(result, false);

  disconnect(&c, &AbstractCondition::conditionChanged, this, &TestEngine::updateCondition);
  }


//void TestEngine::tellStdPaths() {
//  QStringList sl = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);

//  for (const QString& s : sl) {
//      qDebug() << "app config location: " << s;
//      }
//  sl = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
//  for (const QString& s : sl) {
//      qDebug() << "home location: " << s;
//      }
//  }


//void TestEngine::writeSettings() {
//  QSettings cfg(QSettings::UserScope, "SRD", "FalconView");

//  cfg.setValue("whatEver", "hello world");
//  }


//void TestEngine::readSettings() {
//  QSettings cfg(QSettings::UserScope, "SRD", "FalconView");
//  QVariant we = cfg.value("whatEver");

//  QCOMPARE(we.toString(), "hello world");
//  }


QTEST_MAIN(TestEngine)
#include "testengine.moc"
