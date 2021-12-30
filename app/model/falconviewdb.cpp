#include <falconviewdb.h>
#include <dbconnection.h>
#include <timestamp.h>
#include <syseventmodel.h>
//#include <toolcategorymodel.h>
//#include <toolmodel.h>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QSqlDatabase>
#include <QSqlRecord>
#include <QSqlField>
#include <QRegularExpression>
#include <QDomDocument>
#include <QVariant>
#include <QFile>
#include <QString>
#include <QSqlError>
#include <QDebug>
#include <configacc.h>


bool FalconViewDB::connect(const QString& name) {
  conn = new DBConnection(name, "QSQLITE");

  return conn->connect();
  }


DBConnection* FalconViewDB::createDatabase(const QString&) {
  for (;;) {
      if (!conn->connect()) break;
//      if (!ToolCategoryModel::createTable()) break;
//      if (!ToolModel::createTable()) break;
      if (!SysEventModel::createTable()) break;

      return conn;
      }
  QSqlError err = QSqlDatabase::database().driver()->lastError();

  qDebug() << "sysEvent-table failed with error: " << err.text();
  qDebug() << "                        db-error: " << err.databaseText();
  qDebug() << "                    driver-error: " << err.driverText();

  throw err;
  }


void FalconViewDB::createSampleData(DBConnection& conn) {
  createToolSampleData(conn);
  createSysEventSamples(conn);
  }


void FalconViewDB::createSysEventSamples(DBConnection&) {
  QSqlTableModel  tmSysEvents;
  QSqlRecord      recSysEvent;
  int             n = 0;

  tmSysEvents.setTable("SysEvents");
  recSysEvent = tmSysEvents.record();

  do {
     recSysEvent.setValue("id", ++n);
     recSysEvent.setValue("sewhen", QVariant((qlonglong)TimeStamp::rtSequence()));
     recSysEvent.setValue("setype", QVariant(0));
     recSysEvent.setValue("what", QString("Testdata for system event list (%1)").arg(n));
     if (!tmSysEvents.insertRecord(-1, recSysEvent)) {
        QSqlError err = QSqlDatabase::database().driver()->lastError();

        qDebug() << "sysevent creation failed with error: " << err.text();
        qDebug() << "                           db-error: " << err.databaseText();
        qDebug() << "                       driver-error: " << err.driverText();

        return;
        }
     recSysEvent = tmSysEvents.record();
     } while (n < 10);
  }


QString FalconViewDB::xml2Sql(const QString& name) const {
  if (!name.compare("ToolProfile"))           return "type";
  else if (!name.compare("Index"))            return "num";
  else if (!name.compare("Name"))             return "name";
  else if (!name.compare("toolLength"))       return "lenTool";
  else if (!name.compare("colletDiameter"))   return "diaColl";
  else if (!name.compare("colletLength"))     return "lenColl";
  else if (!name.compare("ShankDiameter"))    return "diaShank";
  else if (!name.compare("Length"))           return "lenFree";
  else if (!name.compare("slopeAngle"))       return "angSlope";
  else if (!name.compare("Flutes"))           return "flutes";
  else if (!name.compare("Diameter"))         return "diaFlute";
  else if (!name.compare("FluteLength"))      return "lenFlute";
  else if (!name.compare("RadialDepthOfCut")) return "radCut";
  else if (!name.compare("AxialDepthOfCut"))  return "lenCut";
  else if (!name.compare("VeeAngle"))         return "angCut";
  else if (!name.compare("tipDiameter"))      return "diaTip";
  else if (!name.compare("ToothLoad"))        return "load";
  else if (!name.compare("HelixAngle"))       return "angHelix";
  else if (!name.compare("MaxRampAngle"))     return "angMaxRamp";
  else if (!name.compare("material"))         return "material";
  else if (!name.compare("coating"))          return "coating";
  else if (!name.compare("partCode"))         return "partCode";
  else if (!name.compare("ToothLoad"))        return "load";
  else if (!name.compare("HelixAngle"))       return "angHelix";
  else if (!name.compare("MaxRampAngle"))     return "angMaxRamp";
  return QString();
  }


QVariant::Type FalconViewDB::colType4(const QString &columnName) const {
  if (!columnName.compare("type"))            return static_cast<QVariant::Type>(QMetaType::Int);
  else if (!columnName.compare("id"))         return static_cast<QVariant::Type>(QMetaType::Int);
  else if (!columnName.compare("num"))        return static_cast<QVariant::Type>(QMetaType::Int);
  else if (!columnName.compare("lenTool"))    return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("diaColl"))    return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("lenColl"))    return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("diaShank"))   return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("lenTool"))    return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("lenFree"))    return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("angSlope"))   return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("flutes"))     return static_cast<QVariant::Type>(QMetaType::Int);
  else if (!columnName.compare("diaFlute"))   return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("lenFlute"))   return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("radCut"))     return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("lenCut"))     return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("angCut"))     return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("diaTip"))     return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("load"))       return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("toolthLoad")) return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("angHelix"))   return static_cast<QVariant::Type>(QMetaType::Double);
  else if (!columnName.compare("angMaxRamp")) return static_cast<QVariant::Type>(QMetaType::Double);
  qDebug() << "unsupported/unknown field" << columnName << " default to QString";

  return static_cast<QVariant::Type>(QMetaType::QString);
  }


void FalconViewDB::createCategory(QSqlTableModel& model, QSqlField &fId, QSqlField &fProfile, QSqlField &fName, const QString &category) {
  QSqlRecord rec;
  bool ok = true;

  if (category.indexOf(" - ") > 0) {
     QStringList parts = category.split(QRegularExpression("\\s+-\\s+"));

     fId.setValue(toolCategories.size() + 1);
     if (toolCategories.contains(parts[1])) {
        fProfile.setValue(toolCategories[parts[1]]);
        }
     else {
        fProfile.setValue(toolCategories.size() + 1);
        fName.setValue(parts[1]);
        rec.append(fId);
        rec.append(fProfile);
        rec.append(fName);
        ok = model.insertRecord(-1, rec);
        if (!ok) {
           QSqlError err = QSqlDatabase::database().driver()->lastError();

           qDebug() << "failed with error: " << err.text();
           qDebug() << "         db-error: " << err.databaseText();
           qDebug() << "     driver-error: " << err.driverText();

           return;
           }
        toolCategories[parts[1]] = fId.value().toInt();
        rec.clear();
        fProfile.setValue(toolCategories[parts[1]]);
        fId.setValue(toolCategories.size() + 1);
        }
     fName.setValue(parts[0]);
     }
  else {
     fId.setValue(toolCategories.size() + 1);
     fProfile.setValue(fId.value());
     fName.setValue(category);
  }
  rec.append(fId);
  rec.append(fProfile);
  rec.append(fName);
  ok = model.insertRecord(-1, rec);

  if (!ok) {
     QSqlError err = QSqlDatabase::database().driver()->lastError();

     qDebug() << "create category failed with error: " << err.text();
     qDebug() << "                         db-error: " << err.databaseText();
     qDebug() << "                     driver-error: " << err.driverText();

     return;
     }
  }


void FalconViewDB::createToolSampleData(DBConnection&) {
  QDomDocument doc;
  QFile file(":/res/Tools_backup.xml");
  QSqlTableModel tmTool;
  QSqlTableModel tmCat;

  tmTool.setTable("Tools");
  tmCat.setTable("Category");
  if (!file.open(QIODevice::ReadOnly)) return;

  doc.setContent(&file);
  file.close();

  QDomNodeList tools = doc.elementsByTagName("ToolDefinition");
  QSqlRecord recTool;

  for (int i=0; i < tools.count(); ++i) {
      QDomNode tool = tools.item(i);

      qDebug() << "\n";
      qDebug() << "check entry #" << i;
      if (tool.isElement()) {
         QDomElement e = tool.toElement();

         for (QDomNode n = e.firstChild(); !n.isNull(); n = n.nextSibling()) {
             if (n.isElement()) {
                QDomElement se = n.toElement();
                QString colName = xml2Sql(se.tagName());


                if (!colName.size()) continue;
                QSqlField fld(colName, colType4(colName)); // rec.field(colName));

                qDebug() << "\tcolumn field: " << fld.name()
                         << "\t" << fld.type() << "\t" << (fld.isReadOnly() ? "RO" : "RW")
                         << "\twas: " << se.tagName();
                fld.setReadOnly(false);
                if (!colName.compare("diaColl")) {
                    fld.setValue(QVariant(57.0));
                    recTool.append(fld);
                    continue;
                    }
                if (!colName.compare("lenColl")) {
                   fld.setValue(QVariant(70.5));
                   recTool.append(fld);
                   continue;
                   }
                for (QDomNode n1 = se.firstChild(); !n1.isNull(); n1 = n1.nextSibling()) {

                    if (n1.isElement()) qDebug() << "\tElement";
                    if (n1.isEntity())  qDebug() << "\tEntity";
                    if (n1.isAttr())    qDebug() << "\tAttribute";
                    if (n1.isText()) {
                       const QString& rawData = n1.toText().data();
                       QVariant value = rawData;

                       if (fld.type() == QVariant::Int)         value = rawData.toInt();
                       else if (fld.type() == QVariant::Double) value = rawData.toDouble();
                       qDebug() << "\tcolumn value: " << value;

                       if (!colName.compare("type")) {
                          if (toolCategories.contains(rawData)) {
                             value = toolCategories[rawData];
                             }
                          else {
                             QSqlField fId("id", static_cast<QVariant::Type>(QMetaType::Int));
                             QSqlField fTP("parent", static_cast<QVariant::Type>(QMetaType::Int));
                             QSqlField fName("name", static_cast<QVariant::Type>(QMetaType::QString));

                             createCategory(tmCat, fId, fTP, fName, rawData);
                             toolCategories[fName.value().toString()] = fId.value().toInt();
                             value = fId.value();
                             }
                          }
                       fld.setValue(value);
                       }
                    recTool.append(fld);
                    }
                }
             if (n.isEntity())  qDebug() << "Entity";
             if (n.isAttr())    qDebug() << "Attribute";
             if (n.isText())    qDebug() << "Text";
             }
         }
      if (tool.isEntity())  qDebug() << "Entity";
      if (tool.isAttr())    qDebug() << "Attribute";
      if (tool.isText())    qDebug() << "Text";
      QSqlField fld = recTool.field("lenTool"); //, colType4("lenTool"));
      double len = recTool.field("lenFree").value().toDouble()
                 + recTool.field("lenColl").value().toDouble();

      qDebug() << "lenTool: " << fld.value() << "\t" << (fld.isReadOnly() ? "RO" : "RW") << " nv: " << len;

      recTool.setValue("lenTool", len);
      fld = QSqlField("id", colType4("id"));
      fld.setValue(tmTool.rowCount() + 1);
      recTool.append(fld);
//      dumpFields(recTool);
      bool ok = tmTool.insertRecord(-1, recTool);

      if (!ok) {
         QSqlError err = QSqlDatabase::database().driver()->lastError();

         qDebug() << "tool creation failed with error: " << err.text();
         qDebug() << "                       db-error: " << err.databaseText();
         qDebug() << "                   driver-error: " << err.driverText();

         return;
         }
      recTool.clear();
      }
  }
