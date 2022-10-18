/* 
 * **************************************************************************
 * 
 *  file:       tooltable.cpp
 *  project:    FalconView
 *  subproject: main application
 *  purpose:    ui frontend for linuxCNC                          
 *  created:    20.1.2022 by Django Reinhard
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
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QPixmap>
#include <QIcon>
#include <QDebug>
#include <core.h>
#include "tooltable.h"
#include "toolentry.h"


ToolTable::ToolTable(LcProperties& lcProps, const QString& fileName)
 : lcProperties(lcProps)
 , fn(fileName)
 , latheMode(false) {
  QFile file(fileName);

  if (file.exists()) processFile(file);
  }


ToolTable::ToolTable(LcProperties& lcProps, QFile& file)
 : lcProperties(lcProps) {
  if (file.exists()) processFile(file);
  }


ToolTable::ToolTable(const ToolTable&& other)
 : mappedTools(other.mappedTools)
 , tools(other.tools)
 , lcProperties(other.lcProperties)
 , curTool(other.curTool)
 , fn(other.fn) {
  }


ToolTable::~ToolTable() {
  }


ToolTable& ToolTable::operator=(const ToolTable&& other) {
  mappedTools = other.mappedTools;
  tools       = other.tools;
  curTool     = other.curTool;
  fn          = other.fn;

  return *this;
  }


void ToolTable::processFile(QFile& file) {
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     if (fn.isEmpty()) fn = file.fileName();
     qDebug() << "ToolTable::processFile(" << file.fileName() << ")";
     QTextStream in(&file);
     QString line    = in.readLine();
     int     lineNum = 0;

     toolImageDir = Core().fileName4("toolImages");
     qDebug() << "tool-image-dir: " << toolImageDir;
     while (!line.isNull()) {
           processLine(++lineNum, line);
           line = in.readLine();
           }
     file.close();
     }
  }


bool ToolTable::save() {
  qDebug() << "ToolTable::save() - >" << fn << "<";
  if (Core().move2Backup(fn)) {
     QFile file(fn);

     if (file.open(QFile::WriteOnly | QFile::Truncate)) {
        for (auto t : qAsConst(tools)) {
            qDebug() << t->number() << "at #" << t->lineNum();
            if (!file.write(t->toLine().toStdString().c_str())) return false;
            }
        file.flush();
        file.close();

        return true;
        }
     }
  return false;
  }


void ToolTable::setDirty(bool dirty) {
  this->dirty = dirty;
  }


void ToolTable::processLine(int lineNum, const QString& input) {
  QString line = input.trimmed();
  QString cat;
  QString desc;
  QPixmap pm;

  if (line.indexOf(";") > 0) {
     QStringList parts = line.split(QRegularExpression("\\s*;\\s*"));

     if (parts.size() > 1) {
        desc = parts[1];
        line = parts[0];

        if (!desc.isEmpty()) {
           parts = desc.split("|");

           if (parts.size() > 1) {
              desc = parts[0];
              cat  = parts[1].trimmed();
              QFileInfo img(toolImageDir.absoluteFilePath() + "/" + cat + ".jpg");

              for (;;) {
                  if (!img.exists()) {
                     img = QFileInfo(toolImageDir.absoluteFilePath() + "/" + cat + ".png");
                     if (!img.exists()) break;
                     }
                  pm = QPixmap(img.absoluteFilePath());
                  pm = pm.scaled(150,150, Qt::KeepAspectRatio);
                  break;
                  }
              }
           }
        }
     }
  QStringList parts = line.split(QRegularExpression("\\s+"));
  int    number     = 0;
  int    slot       = 0;
  int    quadrant   = 0;
  double x          = 0;
  double length     = 0;
  double diameter   = 0;
  double frontAngle = 0;
  double backAngle  = 0;
  bool   ok;

  for (QString part : parts) {
      switch (part[0].toLatin1()) {
        case 'T':
             number = part.midRef(1).toInt(&ok);
             if (!ok) number = -1;
             break;
        case 'P':
             slot = part.midRef(1).toInt(&ok);
             if (!ok) number = -1;
             break;
        case 'Z':
             length = part.midRef(1).toDouble(&ok);
             if (!ok) length = 0;
             break;
        case 'X':
             x = part.midRef(1).toDouble(&ok);
             if (!ok) length = 0;
             break;
        case 'D':
             diameter = part.midRef(1).toDouble(&ok);
             if (!ok) diameter = 0;
             break;
        case 'I':
             frontAngle = part.midRef(1).toDouble(&ok);
             if (!ok) frontAngle = -1;
             break;
        case 'J':
             backAngle = part.midRef(1).toDouble(&ok);
             if (!ok) backAngle = -1;
             break;
        case 'Q':
             quadrant = part.midRef(1).toInt(&ok);
             if (!ok) quadrant = -1;
             break;
        }
      }
  ToolEntry* te = new ToolEntry(number
                              , length
                              , x
                              , diameter
                              , quadrant
                              , frontAngle
                              , backAngle
                              , desc
                              , slot
                              , lineNum);
  te->setPixmap(pm);
  te->setToolType(cat);
  tools.append(te);
  mappedTools.insert(number, te);
//  te->dump();
  }


int ToolTable::rowCount(const QModelIndex& p) const {
  return p.isValid() ? 0 : tools.size();
  }


int ToolTable::columnCount(const QModelIndex &p) const {
  return p.isValid() ? 0 : latheMode ? 10 : 6;
  }


QVariant ToolTable::data(const QModelIndex& n, int role) const {
  if (!n.isValid()) return QVariant();
  if (n.row() >= tools.size() || n.row() < 0) return QVariant();
  const ToolEntry* t = tools.at(n.row());

  if (role == Qt::DisplayRole) {
     if (latheMode) {
        switch (n.column()) {
          case 0:  return t->slot();
          case 1:  return t->number();
          case 2:  return t->length();
          case 3:  return t->xOffset();
          case 4:  return t->diameter();
          case 5:  return t->quadrant();
          case 6:  return t->frontAngle();
          case 7:  return t->backAngle();
          case 9:  return t->description();
          default: break;
          }
        }
     else {
        switch (n.column()) {
          case 0:  return t->slot();
          case 1:  return t->number();
          case 2:  return t->length();
          case 3:  return t->diameter();
          case 5:  return t->description();
          default: break;
          }
        }
     }
  else if (role == Qt::DecorationRole) {
     if ((latheMode && n.column() == 8)
      || (!latheMode && n.column() == 4)) {
        return t->icon().scaled(58, 58, Qt::KeepAspectRatio);
        }
     }
  else if (role == Qt::TextAlignmentRole) {
    if (latheMode) {
       switch (n.column()) {
         case 0:
         case 1:
         case 5:
         case 6:
         case 7:
              return int(Qt::AlignRight | Qt::AlignVCenter);
         default:
              return int(Qt::AlignLeft | Qt::AlignVCenter);
         }
       }
    }
  return QVariant();
  }


QVariant ToolTable::headerData(int column, Qt::Orientation orientation, int role) const {
  if (role != Qt::DisplayRole) return QVariant();
  if (orientation == Qt::Horizontal) {
     if (latheMode) {
        switch (column) {
          case 0:  return tr("Slot");
          case 1:  return tr("Tool");
          case 2:  return tr("Z");
          case 3:  return tr("X");
          case 4:  return tr("Dia");
          case 5:  return tr("TO");
          case 6:  return tr("FA");
          case 7:  return tr("BA");
          case 8:  return tr("S");
          case 9:  return tr("Description");
          default: break;
          }
        }
     else {
        switch (column) {
          case 0:  return tr("Slot");
          case 1:  return tr("Tool");
          case 2:  return tr("Len");
          case 3:  return tr("Dia");
          case 4:  return tr("S");
          case 5:  return tr("Description");
          default: break;
          }
        }
     }
  return QVariant();
  }


Qt::ItemFlags ToolTable::flags(const QModelIndex& n) const {
  if (!n.isValid()) return Qt::ItemIsEnabled;
  return QAbstractTableModel::flags(n) | Qt::ItemIsEditable;
  }


bool ToolTable::setData(const QModelIndex &index, const QVariant &value, int role) {
  if (index.isValid() && role == Qt::EditRole) {
     const int row = index.row();
     ToolEntry* t = tools.value(row);

     qDebug() << "\t\tToolTable::setData() ...";
     Core().showAllButCenter(false);
     if (latheMode) {
        switch (index.column()) {
          case 0:  t->setSlot(value.toInt()); break;
          case 1:  break; // no support for changing tool number!
          case 2:  t->setLength(value.toDouble()); break;
          case 3:  t->setXOffset(value.toDouble()); break;
          case 4:  t->setDiameter(value.toDouble()); break;
          case 5:  t->setQuadrant(value.toInt()); break;
          case 6:  t->setFrontAngle(value.toDouble()); break;
          case 7:  t->setBackAngle(value.toDouble()); break;
          case 9:  t->setDescription(value.toString()); break;
          default: return false;
          }
        }
     else {
        switch (index.column()) {
          case 0:  t->setSlot(value.toInt()); break;
          case 1:  break; // no support for changing tool number!
          case 2:  t->setLength(value.toDouble()); break;
          case 3:  t->setDiameter(value.toDouble()); break;
          case 5:  t->setDescription(value.toString()); break;
          default: return false;
          }
        }
     if (index.column() != 1)
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
     return true;
     }
  return false;
  }


void ToolTable::setCurrent(int slot) {
//  qDebug() << "activate tool with slot #" << slot;
  for (const ToolEntry* te : qAsConst(tools)) {
//      qDebug() << "tool" << te->number() << "has line number" << te->lineNum() << "and slot" << te->slot();
      if (te->slot() == slot) {
         curTool = *te;
         break;
         }
      }
  }


int ToolTable::entries() const {
  return tools.count();
  }


const ToolEntry* ToolTable::tool(int number) const {
  if (!mappedTools.contains(number)) return nullptr;
  return mappedTools[number];
  }


const ToolEntry* ToolTable::tool4Slot(int number) const {
  if (number < 0 || number >= tools.size()) return nullptr;
  return tools.at(number);
  }


void ToolTable::dump() {
  qDebug() << "--->>> dump tools as list ...";
  for (const ToolEntry* te : qAsConst(tools)) {
      te->dump();
      }
  qDebug() << "--->>> dump tools by mapped keys ...";
  for (auto e = mappedTools.keyValueBegin()
     ; e != mappedTools.keyValueEnd()
     ; e++) {
      qDebug() << "key #" << e->first;
      e->second->dump();
      }
  }
