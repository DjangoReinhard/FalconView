#include <toolmodel.h>
#include <dbconnection.h>
#include <QFileIconProvider>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>


ToolModel::ToolModel(DBConnection& conn, QObject *parent)
 : QSqlTableModel(parent)
 , ui(":/res/CB_unchecked.png")
 , ci(":/res/CB_checked.png") {
  if (!conn.connect()) {
     throw new QSqlError("failed to open database!");
     }
  setTable("Tools");
  this->setEditStrategy(QSqlTableModel::OnManualSubmit);
  select();
  }


bool ToolModel::createTable() {
  QSqlQuery sql;
  bool      rv;

  rv = sql.exec("CREATE TABLE \"Tools\" (id         INT PRIMARY KEY"
                                      ", num        INT NOT NULL"            // 1 Index
                                      ", lenTool    NUMERIC(7,3) NOT NULL "  // 2
                                      ", name       VARCHAR(50) NOT NULL "   // 3 Name
                                      ", type       INT NOT NULL "           // 4 ToolProfile
                                      ", flutes     INT NOT NULL "           // 5 Flutes
                                      ", radCut     NUMERIC(7,3) "           // 6 RadialDepthOfCut
                                      ", lenCut     NUMERIC(7,3) "           // 7 AxialDepthOfCut
                                      ", angCut     NUMERIC(7,3) "           // 8 VeeAngle
                                      ", lenFlute   NUMERIC(7,3) "           // 9 FluteLength
                                      ", diaFlute   NUMERIC(7,3) "           // 10 Diameter
                                      ", diaColl    NUMERIC(7,3) "           // 11
                                      ", lenColl    NUMERIC(7,3) "           // 12
                                      ", diaShank   NUMERIC(7,3) "           // 13 ShankDiameter
                                      ", lenFree    NUMERIC(7,3) "           // 14 Length
                                      ", angSlope   NUMERIC(7,3) "           // 15
                                      ", diaTip     NUMERIC(7,3) "           // 16
                                      ", partCode   VARCHAR(50) "            // 17 -
                                      ", material   VARCHAR(20) "            // 18
                                      ", coating    VARCHAR(20) "            // 19 -
                                      ", load       NUMERIC(7,3) "           // 20 ToothLoad
                                      ", angHelix   NUMERIC(7,3) "           // 21 HelixAngle
                                      ", angMaxRamp NUMERIC(7,3) "           // 22 MaxRampAngle
                                      ", comment    VARCHAR(254) "           // 23 -
                                      " )");
  return rv;
  }


QVariant ToolModel::data(const QModelIndex& idx, int role) const {
//  qDebug() << "ToolModel::data(" << idx << ", role: " << role << ")";

//  if (role == Qt::DecorationRole && !idx.column()) {
//     return ci;
//     }
  return QSqlTableModel::data(idx, role);
  }


QVariant ToolModel::headerData(int column, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
     switch (column) {
       case 0: return tr("id");
       case 1: return tr("Num");
       case 2: return tr("Len");
       case 3: return tr("Name");
       case 4: return tr("Type");
       case 5: return tr("Flutes");
       case 6: return tr("radCut");
       case 7: return tr("axCut");
       case 8: return tr("angVee");
       case 9: return tr("lenFlutes");
       case 10: return tr("diaFlutes");
       case 11: return tr("diaCol");
       case 12: return tr("lenCol");
       case 13: return tr("diaShank");
       case 14: return tr("lenFree");
       case 15: return tr("angSlope");
       case 16: return tr("diaTip");
       case 17: return tr("code");
       case 18: return tr("material");
       case 19: return tr("coating");
       case 20: return tr("ldTooth");
       case 21: return tr("angHelix");
       case 22: return tr("angMxRamp");
       case 23: return tr("comment");
       }
     }
  return QVariant();
  }


QVariant ToolModel::promptData(int column, int role) const {
  if (role == Qt::DisplayRole) {
     switch (column) {
       case 0: return tr("id");
       case 1: return tr("Num");
       case 2: return tr("Length");
       case 3: return tr("Name");
       case 4: return tr("Type");
       case 5: return tr("Flutes");
       case 6: return tr("radial Depth of Cut");
       case 7: return tr("axial Depth of Cut");
       case 8: return tr("Vee Angle");
       case 9: return tr("length of Flutes");
       case 10: return tr("diameter of Flutes");
       case 11: return tr("diameter of Collet");
       case 12: return tr("length of Collet");
       case 13: return tr("diameter of Shank");
       case 14: return tr("free Length");
       case 15: return tr("slope angle");
       case 16: return tr("diameter of Tip");
       case 17: return tr("partcode");
       case 18: return tr("material");
       case 19: return tr("coating");
       case 20: return tr("tooth load");
       case 21: return tr("angle of Helix");
       case 22: return tr("angle max. Ramp");
       case 23: return tr("comment");
       }
     }
  return QVariant();
  }


int ToolModel::tools4Category(int categoryId) {
  QString   qs = QString("SELECT count(id) FROM Tools WHERE type=%1").arg(categoryId);
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query tools 4 cat" << categoryId << q.lastError().text();
     return -1;
     }
  int count = 0;

  if (q.next()) count = q.value(0).toInt();
  revertAll();

  return count;
  }


int ToolModel::maxToolNum() {
  QString   qs = QString("SELECT max(num) FROM Tools");
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query max toolnum" << q.lastError().text();
     return -1;
     }
  int tNum = 0;

  if (q.next()) tNum = q.value(0).toInt();
  revertAll();

  return tNum;
  }



int ToolModel::nextId() {
  QString   qs = QString("SELECT max(id) FROM Tools");
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query max id" << q.lastError().text();
     return -1;
     }
  int tNum = 0;

  if (q.next()) tNum = q.value(0).toInt();
  revertAll();

  return tNum + 1;
  }


bool ToolModel::existsToolNum(int toolNum) {
  QString   qs = QString("SELECT count(id) FROM Tools WHERE num=%1").arg(toolNum);
  QSqlQuery q(qs);

  if (!q.exec()) {
     qDebug() << "failed to query existance of toolNum" << q.lastError().text();
     return true;   // signals error
     }
  int count = 0;

  if (q.next()) count = q.value(0).toInt();
  revertAll();

  return count > 0;
  }
