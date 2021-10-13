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

ToolTable& ToolTable::operator=(const ToolTable &&other) {
  mappedTools = other.mappedTools;
  tools       = other.tools;
  curTool     = other.curTool;
  fn          = other.fn;

  return *this;
  }


void ToolTable::processFile(QFile &file) {
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


void ToolTable::processLine(int lineNum, const QString &input) {
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
             number = part.mid(1).toInt(&ok);
             if (!ok) number = -1;
             break;
        case 'P':
             slot = part.mid(1).toInt(&ok);
             if (!ok) number = -1;
             break;
        case 'Z':
             length = part.mid(1).toDouble(&ok);
             if (!ok) length = 0;
             break;
        case 'D':
             diameter = part.mid(1).toDouble(&ok);
             if (!ok) diameter = 0;
             break;
        case 'I':
             frontAngle = part.mid(1).toDouble(&ok);
             if (!ok) frontAngle = -1;
             break;
        case 'J':
             backAngle = part.mid(1).toDouble(&ok);
             if (!ok) backAngle = -1;
             break;
        case 'Q':
             quadrant = part.mid(1).toInt(&ok);
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


void ToolTable::setCurrent(int slot) {
  qDebug() << "activate tool with slot #" << slot;
  for (const ToolEntry* te : tools) {
      qDebug() << "tool" << te->number() << "has line number" << te->lineNum() << "and slot" << te->slot();
      if (te->slot() == slot) {
         curTool = *te;
         break;
         }
      }
  }


const ToolEntry* ToolTable::tool(int number) const {
  if (number < 0 || number >= tools.size()) return nullptr;
  return tools[number];
  }


void ToolTable::dump() {
  qDebug() << "dump tools as list ...";
  for (const ToolEntry* te : tools) {
      te->dump();
      }
  qDebug() << "dump tools by mapped keys ...";
  for (int n : mappedTools.keys()) {
      qDebug() << "key #" << n;
      mappedTools[n]->dump();
      }
  }
