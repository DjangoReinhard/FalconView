#include "lcproperties.h"
#include <QFile>
#include <QTextStream>
#include <QMetaType>
#include <QRegularExpression>
#include <QDebug>


LcProperties::LcProperties(const QString& fileName)
 : curMap(nullptr)
 , fn(fileName) {
  QFile file(fileName);

  if (file.exists()) processFile(file);
  }


LcProperties::LcProperties(const LcProperties&& other)
 : properties(other.properties)
 , curMap(other.curMap) {
  }


LcProperties& LcProperties::operator=(const LcProperties&& other) {
  properties = other.properties;
  curMap     = other.curMap;

  return *this;
  }


void LcProperties::addGroup(const QString &groupID) {
//  qDebug() << "\nadd group with ID: " << groupID;
  if (!properties.contains(groupID))
     properties.insert(groupID, QMap<QString, QVariant>());
  curMap = &properties[groupID];
  }


void LcProperties::addValue(const QString& name, const QVariant& value) {
  if (!curMap) return;
//  qDebug() << "\t\tadd property [" << name << "] => {" << value << "}";
  if (curMap->contains(name)) {
     QVariant v = curMap->value(name);

#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
     if (v.typeId() == QMetaType::QStringList) {
#else
     if (v.type() == QVariant::StringList) {
#endif
        v.toStringList().append(value.toString());
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
     else if (v.typeId() == QMetaType::QVariantList) {
#else
     else if (v.type() == QVariant::List) {
#endif
        v.toList().append(value);
        }
     else {
        qDebug() << "OUPS: possibly overwrite existing value [" << v << "] with new value {" << value << "}";
        curMap->insert(name, value);
        }
     }
  else {
     curMap->insert(name, value);
     }
  }


/*
 * gui settings:
 *    "DISPLAY", "MAX_FEED_OVERRIDE"
 *    "DISPLAY", "MAX_SPINDLE_OVERRIDE"
 *    "DISPLAY", "MIN_SPINDLE_OVERRIDE"
 *
 *    "RS274NGC", "PARAMETER_FILE"
 *    "RS274NGC", "RS274NGC_STARTUP_CODE"
 *    "RS274NGC", "SUBROUTINE_PATH"
 *
 *    "TRAJ", "ANGULAR_UNITS"
 *    "TRAJ", "LINEAR_UNITS"
 *    "TRAJ", "POSITION_FILE"
 */
QVariant LcProperties::value(const QString &groupID, const QString &name) const {
  return properties[groupID][name];
  }


QString LcProperties::parameterFileName() const {
  return getPath("RS274NGC", "PARAMETER_FILE");
  }


QString LcProperties::toolTableFileName() const {
  return getPath("EMCIO", "TOOL_TABLE");
  }


QString LcProperties::toolImageDir() const {
  return getPath("DISPLAY", "TOOL_IMAGE_DIR");
  }


QString LcProperties::getPath(const QString &groupID, const QString &name) const {
  QString rawValue = value(groupID, name).toString();

  if (rawValue.startsWith("/")) return rawValue;
  if (rawValue.startsWith("~")) rawValue.replace("~", QDir::homePath());
  else rawValue = baseDir() + "/" + rawValue;
  QFileInfo fi(rawValue);

  return fi.absoluteFilePath();
  }


void LcProperties::processFile(QFile& file) {
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     QTextStream in(&file);
     QString line = in.readLine();

     while (!line.isNull()) {
           processLine(line);
           line = in.readLine();
           }
     file.close();
     }
  }


void LcProperties::processLine(const QString &input) {
  QString line = input.trimmed();

  if (line.startsWith("#")) return;
  if (line.startsWith("[")) {
     int end = line.indexOf("]");
     QString groupID = line.mid(1, end - 1);

     addGroup(groupID);
     }
  else {
     QStringList list;

     list = line.split(QRegularExpression("\\s*=\\s*"));
     if (list.size() >= 2) {
         QString name  = list.takeFirst();
         QString value = list.join(" = ");
         bool ok;
         qlonglong lv = value.toLongLong(&ok, 0);

         if (ok) {
//            qDebug() << "\tadd value as integer [" << name << "] => " << lv << "\twas: " << value;

            if (lv > INT_MIN && lv < INT_MAX) {
               QVariant v(static_cast<int>(lv));

               addValue(name, v);
               }
            else {
               QVariant v(lv);

               addValue(name, v);
               }
            }
         else {
            double dv = value.toDouble(&ok);

            if (ok) {
//               qDebug() << "\tadd value as double  [" << name << "] => " << dv << "\twas: " << value;
               QVariant v(dv);

               addValue(name, v);
               }
            else if (!value.compare("NO") || !value.compare("no")) {
//               qDebug() << "\tadd boolean false [" << name << "]\twas: " << value;
               QVariant v(false);

               addValue(name, v);
               }
            else if (!value.compare("YES") || !value.compare("yes")) {
//               qDebug() << "\tadd boolean true [" << name << "]\twas: " << value;
               QVariant v(true);

               addValue(name, v);
               }
            else {
               if (value.indexOf(",") > 0) {
//                  qDebug() << "\ttreat value as list ... [" << name << "] => " << value;
                  QStringList l = value.split(QRegularExpression("\\s*,\\s*"));
                  QVariant v(l);

//                  qDebug() << "\tlist has #" << l.size() << " entries";
                  addValue(name, v);
                  }
               else {
//                  qDebug() << "\tadd value as string [" << name << "] => " << value;
                  QVariant v(value);

                  addValue(name, v);
                  }
               }
            }
        }
     }
  }


void LcProperties::dump() {
#ifdef REDNOSE
  for (const QString& groupID : properties.keys()) {
      const QMap<QString, QVariant>& m = properties.value(groupID);

      qDebug() << " ";
      qDebug() << "dump group <" << groupID << ">";
      for (const QString& name : m.keys()) {
          qDebug() << "\t[" << name << "] => " << m.value(name);
          }
      }
#else
  for (auto g = properties.keyValueBegin(); g != properties.keyValueEnd(); g++) {
      qDebug() << " ";
      qDebug() << "dump group <" << g->first << ">";
      for (auto e = g->second.keyValueBegin(); e != g->second.keyValueEnd(); e++) {
        qDebug() << "\t[" << e->first << "] => " << e->second;
        }
      }
#endif
  }
