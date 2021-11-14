#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QDebug>
#include <tooltable.h>
#include <toolentry.h>


ToolTable::ToolTable(const QString& fileName)
 : fn(fileName) {
  QFile file(fileName);

  if (file.exists()) processFile(file);
  }


ToolTable::ToolTable(QFile& file) {
  if (file.exists()) processFile(file);
  }


ToolTable::ToolTable(const ToolTable&& other)
 : mappedTools(other.mappedTools)
 , tools(other.tools)
 , curTool(other.curTool)
 , fn(other.fn) {
  }

ToolTable::~ToolTable() {
  //TODO:
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
     QTextStream in(&file);
     QString line    = in.readLine();
     int     lineNum = 0;

     while (!line.isNull()) {
           processLine(++lineNum, line);
           line = in.readLine();
           }
     }
  }


void ToolTable::save() {
  for (auto t : qAsConst(tools)) {
      qDebug() << t;
      }
  }


void ToolTable::processLine(int lineNum, const QString& input) {
  QString line = input.trimmed();
  QString desc;

  if (line.indexOf(";") > 0) {
     QStringList parts = line.split(QRegularExpression("\\s*;\\s*"));

     if (parts.size() > 1) {
        desc = parts[1];
        line = parts[0];
        }
     }
  QStringList parts = line.split(QRegularExpression("\\s+"));
  int    number     = 0;
  int    slot       = 0;
  int    quadrant   = 0;
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
             slot = part.mid(1).toInt(&ok);
             if (!ok) number = -1;
             break;
        case 'Z':
             length = part.midRef(1).toDouble(&ok);
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
                              , diameter
                              , quadrant
                              , frontAngle
                              , backAngle
                              , desc
                              , slot
                              , lineNum);
  tools.append(te);
  mappedTools.insert(number, te);
  }


int ToolTable::rowCount(const QModelIndex& p) const {
  return p.isValid() ? 0 : tools.size();
  }


int ToolTable::columnCount(const QModelIndex &p) const {
  return p.isValid() ? 0 : 7;
  }


QVariant ToolTable::data(const QModelIndex& n, int role) const {
  if (!n.isValid()) return QVariant();
  if (n.row() >= tools.size() || n.row() < 0) return QVariant();
  if (role == Qt::DisplayRole) {
     const ToolEntry* t = tools.at(n.row());

     switch (n.column()) {
       case 0:  return t->number();
       case 1:  return t->length();
       case 2:  return t->diameter();
       case 3:  return t->quadrant();
       case 4:  return t->frontAngle();
       case 5:  return t->backAngle();
       case 6:  return t->description();
       default: break;
       }
     }
  return QVariant();
  }


QVariant ToolTable::headerData(int column, Qt::Orientation orientation, int role) const {
  if (role != Qt::DisplayRole) return QVariant();
  if (orientation == Qt::Horizontal) {
     switch (column) {
       case 0:  return tr("Num");
       case 1:  return tr("Len");
       case 2:  return tr("Dia");
       case 3:  return tr("Quad");
       case 4:  return tr("FA");
       case 5:  return tr("BA");
       case 6:  return tr("Description");
       default: break;
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

     switch (index.column()) {
       case 0:  break; // no support for changing tool number!
       case 1:  t->setLength(value.toDouble()); break;
       case 2:  t->setDiameter(value.toDouble()); break;
       case 3:  t->setQuadrant(value.toInt()); break;
       case 4:  t->setFrontAngle(value.toDouble()); break;
       case 5:  t->setBackAngle(value.toDouble()); break;
       case 6:  t->setDescription(value.toString()); break;
       default: return false;
       }
     emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

     return true;
     }
  return false;
  }


void ToolTable::setCurrent(int slot) {
  qDebug() << "activate tool with slot #" << slot;
  for (const ToolEntry* te : qAsConst(tools)) {
      qDebug() << "tool" << te->number() << "has line number" << te->lineNum() << "and slot" << te->slot();
      if (te->slot() == slot) {
         curTool = *te;
         break;
         }
      }
  }


>>>>>>> Work
const ToolEntry* ToolTable::tool(int number) const {
  if (number < 0 || number >= tools.size()) return nullptr;
  return tools[number];
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
