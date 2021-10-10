#include <lcproperties.h>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>


LcProperties::LcProperties(const QString& fileName)
 : curMap(nullptr) {
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
  qDebug() << "\nadd group with ID: " << groupID;
  if (!properties.contains(groupID))
     properties.insert(groupID, QMap<QString, QVariant>());
  curMap = &properties[groupID];
  }


void LcProperties::addValue(const QString& name, const QVariant& value) {
  if (!curMap) return;
  qDebug() << "\t\tadd property [" << name << "] => {" << value << "}";
  if (curMap->contains(name)) {
     QVariant v = curMap->value(name);

     if (v.typeId() == QMetaType::QStringList) {
        v.toStringList().append(value.toString());
        }
     else if (v.typeId() == QMetaType::QVariantList) {
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


QVariant LcProperties::value(const QString &groupID, const QString &name) {
  QMap<QString, QVariant>& m = properties[groupID];

  return m[name];
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
         QString name  = list.at(0);
         QString value = list.at(1);
         bool ok;
         qlonglong lv = value.toLongLong(&ok, 0);

         if (ok) {             
            qDebug() << "\tadd value as integer [" << name << "] => " << lv << "\twas: " << value;

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
               qDebug() << "\tadd value as double  [" << name << "] => " << dv << "\twas: " << value;
               QVariant v(dv);

               addValue(name, v);
               }
            else if (!value.compare("NO") || !value.compare("no")) {
               qDebug() << "\tadd boolean false [" << name << "]\twas: " << value;
               QVariant v(false);

               addValue(name, v);
               }
            else if (!value.compare("YES") || !value.compare("yes")) {
               qDebug() << "\tadd boolean true [" << name << "]\twas: " << value;
               QVariant v(true);

               addValue(name, v);
               }
            else {
               if (value.indexOf(",") > 0) {
                  qDebug() << "\ttreat value as list ... [" << name << "] => " << value;
                  QStringList l = value.split(QRegularExpression("\\s*,\\s*"));
                  QVariant v(l);

                  qDebug() << "\tlist has #" << l.size() << " entries";
                  addValue(name, v);
                  }
               else {
                  qDebug() << "\tadd value as string [" << name << "] => " << value;
                  QVariant v(value);

                  addValue(name, v);
                  }
               }
            }
        }
     }
  }


void LcProperties::dump() {
  for (QString groupID : properties.keys()) {
      const QMap<QString, QVariant>& m = properties.value(groupID);

      qDebug() << " ";
      qDebug() << "dump group <" << groupID << ">";
      for (QString name : m.keys()) {
          qDebug() << "\t[" << name << "] => " << m.value(name);
          }
      }
  }
