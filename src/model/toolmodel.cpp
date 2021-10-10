#include <toolmodel.h>
#include <dbconnection.h>
#include <QSqlRecord>
#include <QSqlField>
#include <QSqlError>
#include <QDebug>


ToolModel::ToolModel(QObject *parent)
 : QSqlTableModel(parent) {
  if (!DBConnection("toolTable").connect()) {
     throw new QSqlError("failed to open database!");
     }
  setTable("Tools");
  select();
  }


/*
    "  id         INT PRIMARY KEY"
    ", num        INT NOT NULL"                // 1 Index
    ", lenTool    NUMERIC(7,3) NOT NULL "      // 2
    ", name       VARCHAR(50) NOT NULL "       // 3 Name
    ", type       INT NOT NULL "               // 4 ToolProfile
    ", flutes     INT NOT NULL "               // 5 Flutes
    ", radCut     NUMERIC(7,3) "               // 6 RadialDepthOfCut
    ", lenCut     NUMERIC(7,3) "               // 7 AxialDepthOfCut
    ", angCut     NUMERIC(7,3) "               // 8 VeeAngle
    ", lenFlute   NUMERIC(7,3) "               // 9 FluteLength
    ", diaFlute   NUMERIC(7,3) "               // 10 Diameter
    ", diaColl    NUMERIC(7,3) "               // 11
    ", lenColl    NUMERIC(7,3) "               // 12
    ", diaShank   NUMERIC(7,3) "               // 13 ShankDiameter
    ", lenFree    NUMERIC(7,3) "               // 14 Length
    ", angSlope   NUMERIC(7,3) "               // 15
    ", diaTip     NUMERIC(7,3) "               // 16
    ", partCode   VARCHAR(50) "                // 17 -
    ", material   VARCHAR(20) "                // 18
    ", coating    VARCHAR(20) "                // 19 -
    ", load       NUMERIC(7,3) "               // 20 ToothLoad
    ", angHelix   NUMERIC(7,3) "               // 21 HelixAngle
    ", angMaxRamp NUMERIC(7,3) "               // 22 MaxRampAngle
    ", comment    VARCHAR(254) "               // 23 -
 */
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
