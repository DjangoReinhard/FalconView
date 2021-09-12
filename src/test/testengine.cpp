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


QTEST_MAIN(TestEngine)
#include "testengine.moc"
