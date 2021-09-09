#include <axismask.h>
#include <QObject>
#include <QStandardPaths>
#include <QSettings>
#include <QtTest/QTest>


class TestAxisMask : public QObject
{
  Q_OBJECT
public:

private slots:
  void have3Axis();
  void have5Axis();
  void have9Axis();
  void tellStdPaths();
  void writeSettings();
  void readSettings();
  };


void TestAxisMask::have3Axis() {
  AxisMask am(0x07);

  QCOMPARE(am.activeAxis(), 3);
  }


void TestAxisMask::have5Axis() {
  AxisMask am(0x01F);

  QCOMPARE(am.activeAxis(), 5);
  }


void TestAxisMask::have9Axis() {
  AxisMask am(0x01FF);

  QCOMPARE(am.activeAxis(), 9);
  }


void TestAxisMask::tellStdPaths() {
  QStringList sl = QStandardPaths::standardLocations(QStandardPaths::AppConfigLocation);

  for (QString s : sl) {
      qDebug() << "app config location: " << s;
      }
  sl = QStandardPaths::standardLocations(QStandardPaths::HomeLocation);
  for (QString s : sl) {
      qDebug() << "home location: " << s;
      }
  }


void TestAxisMask::writeSettings() {
  QSettings cfg(QSettings::UserScope, "SRD", "QtUi");

  cfg.setValue("whatEver", "ich bin ein Nasenbär");
  }


void TestAxisMask::readSettings() {
  QSettings cfg(QSettings::UserScope, "SRD", "QtUi");
  QVariant we = cfg.value("whatEver");

  QCOMPARE(we.toString(), "ich bin ein Nasenbär");
  }


QTEST_MAIN(TestAxisMask)
#include "testaxismask.moc"
