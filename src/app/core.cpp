#include <core.h>
#include <core_p.h>
#include <QTime>
#include <QString>
#include <core.h>
#include <lcproperties.h>
#include <tooltable.h>
#include <LCInter.h>
#include <canonif.h>
#include <configmgr.h>
#include <occtviewer.h>
#include <cassert>


Core::Core(const QString& iniFileName, const QString& appName, const QString& group) {
  if (!kernel)
     kernel = new Kernel(iniFileName, appName, group);
  }


void Core::parseGCFile(const QString &fileName) {
  QFile gcFile(fileName);

  if (gcFile.exists()) {
     core()->parseGCode(gcFile);
     }
  }


LcProperties& Core::lcProperties() {
  return core()->lcProps;
  }


OcctQtViewer* Core::view3D() {
  return core()->view3D;
  }


Kernel* Core::core() {
  assert(kernel != nullptr);
  return kernel;
  }


Kernel::Kernel(const QString& iniFileName, const QString& appName, const QString& group)
 : cfg(appName, group)
 , lcProps(iniFileName)
 , tt(lcProps.toolTableFileName())
 , lcIF(lcProps, tt)
 , view3D(new OcctQtViewer()) {
  CanonIF ci(lcProps, tt);

  lcIF.setupToolTable();
  ci.setTraverseColor(QColor(Qt::cyan));
  ci.setFeedColor(QColor(Qt::white));
  ci.setLimitsColor(QColor(150, 255, 150));
  }


void Kernel::parseGCode(QFile &file) {
  QTime start = QTime::currentTime();

  lcIF.parseInline(file.fileName());

  QTime end  = QTime::currentTime();
  long delta = end.msecsSinceStartOfDay() - start.msecsSinceStartOfDay();

  qDebug() << "parsing of " << file.fileName() << " took: " << delta << "ms";
  }


Kernel* Core::kernel = nullptr;
