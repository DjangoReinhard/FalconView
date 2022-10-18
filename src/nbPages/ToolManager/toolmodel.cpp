/* 
 * **************************************************************************
 * 
 *  file:       toolmodel.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    19.1.2022 by Django Reinhard
 *  copyright:  (c) 2022 Django Reinhard -  all rights reserved
 * 
 *  This program is free software: you can redistribute it and/or modify 
 *  it under the terms of the GNU General Public License as published by 
 *  the Free Software Foundation, either version 2 of the License, or 
 *  (at your option) any later version. 
 *   
 *  This program is distributed in the hope that it will be useful, 
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of 
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the 
 *  GNU General Public License for more details. 
 *   
 *  You should have received a copy of the GNU General Public License 
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * 
 * **************************************************************************
 */
#include "toolmodel.h"
#include <dbconnection.h>
#include <guicore.h>
//#include <tooltable.h>
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
                                      ", selected   INT(1) default 0"
                                      ", num        INT NOT NULL"            // 1 Index
                                      ", lenTool    NUMERIC(7,3) NOT NULL "  // 2
                                      ", name       VARCHAR(50) NOT NULL "   // 3 Name
                                      ", type       INT(2) NOT NULL "        // 4 ToolProfile
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

  if (idx.column() == 1) {
     if (role == Qt::CheckStateRole) {
        short c = QSqlTableModel::data(idx, Qt::DisplayRole).toInt();

//        qDebug() << "row #" << idx.row() << "c=>" << c << (c ? "selected" : "NOT selected");
        return c != 0;
        }
     else return QVariant();
     }
  return QSqlTableModel::data(idx, role);
  }


void ToolModel::toggleSelection(int row) {
  if (row >= 0 && row < rowCount()) {
     QModelIndex idx = createIndex(row, 1);
     int         c   = data(idx, Qt::CheckStateRole).toBool();

     qDebug() << "toggleSelection(" << row << ") - old value =>" << (c ? 0 : 1);
     setData(index(row, 1), c ? 0 : 1);
     submitAll();
     }
  }


QVariant ToolModel::headerData(int column, Qt::Orientation orientation, int role) const {
  if (orientation == Qt::Horizontal && role == Qt::DisplayRole) {
     switch (column) {
       case 0: return tr("id");
       case 1: return tr("X");
       case 2: return tr("TN");
       case 3: return tr("TL");
       case 4: return tr("Name");
       case 5: return tr("TC");
       case 6: return tr("NF");
       case 7: return tr("FR");
       case 8: return tr("AC");
       case 9: return tr("AV");
       case 10: return tr("FL");
       case 11: return tr("FD");
       case 12: return tr("CD");
       case 13: return tr("CL");
       case 14: return tr("SD");
       case 15: return tr("Len");
       case 16: return tr("AS");
       case 17: return tr("TD");
       case 18: return tr("code");
       case 19: return tr("material");
       case 20: return tr("coating");
       case 21: return tr("ldTooth");
       case 22: return tr("angHelix");
       case 23: return tr("angMxRamp");
       case 24: return tr("comment");
       }
     }
  return QVariant();
  }


QVariant ToolModel::promptData(int column, int role) const {
  if (role == Qt::DisplayRole) {
     switch (column) {
       case 0: return tr("id");
       case 1: return tr("Sel");
       case 2: return tr("Num");
       case 3: return tr("Length");
       case 4: return tr("Name");
       case 5: return tr("Type");
       case 6: return tr("Flutes");
       case 7: return tr("radial Depth of Cut");
       case 8: return tr("axial Depth of Cut");
       case 9: return tr("Vee Angle");
       case 10: return tr("length of Flutes");
       case 11: return tr("diameter of Flutes");
       case 12: return tr("diameter of Collet");
       case 13: return tr("length of Collet");
       case 14: return tr("diameter of Shank");
       case 15: return tr("free Length");
       case 16: return tr("slope angle");
       case 17: return tr("diameter of Tip");
       case 18: return tr("partcode");
       case 19: return tr("material");
       case 20: return tr("coating");
       case 21: return tr("tooth load");
       case 22: return tr("angle of Helix");
       case 23: return tr("angle max. Ramp");
       case 24: return tr("comment");
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


int ToolModel::exportTools() {
//  QString   qs = QString("SELECT tools.*, category.name FROM Tools, Category WHERE tools.selected = 1 AND Category.id = tools.type");
//  QSqlQuery q(qs);

//  if (!q.exec()) {
//     qDebug() << "failed to query selected tools" << q.lastError().text();
//     return 0;
//     }
  int count = 0;

//  if (core->move2Backup(core->toolTable().fileName())) {
//     QFile toolTable(core->toolTable().fileName());

//     if (toolTable.open(QIODevice::WriteOnly | QIODevice::Text)) {
//        QTextStream out(&toolTable);
//        QSqlRecord  r;
//        QString     s;

//        while (q.next()) {
//              r = q.record();
//              s = r.value("comment").toString();

//              if (s.isEmpty()) s = r.value("name").toString();
//              qDebug() << "Tool #" << r.value("Tools.num").toInt()
//                       << "Slot #" << (count + 1)
//                       << "with Len: " << r.value("Tools.lenTool").toDouble()
//                       << "and diameter: " << r.value("diaFlute").toDouble()
//                       << ", desc:" << s
//                       << "and category:" << r.value("Category.name").toString();
//              out << "T" << r.value("Tools.num").toInt()
//                  << " P" << (count + 1)
//                  << " Z" << r.value("Tools.lenTool").toDouble()
//                  << " D" << r.value("diaFlute").toDouble()
//                  << " ; " << s
//                  << " | " << r.value("Category.name").toString()
//                  << "\n";
//              ++count;
//              }
//        toolTable.flush();
//        toolTable.close();
//        revertAll();
//        qDebug() << "exported " << count << "tools";
//        QSqlQuery sql("update tools set selected = 0");

//        if (!sql.exec()) {
//           qDebug() << "failed to query selected tools" << q.lastError().text();
//           }
//        submitAll();
//        }
//     }
  return count;
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


void ToolModel::setCore(GuiCore *core) {
  this->core = core;
  }
