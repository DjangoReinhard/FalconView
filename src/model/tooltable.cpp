#include <tooltable.h>
#include <toolentry.h>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>


ToolTable::ToolTable(const QString& fileName) {
  QFile file(fileName);

  if (file.exists()) processFile(file);
  }


ToolTable::ToolTable(QFile& file) {
  if (file.exists()) processFile(file);
  }


ToolTable::ToolTable(const ToolTable&& other) {
  tools = other.tools;
  }


ToolTable& ToolTable::operator=(const ToolTable &&other) {
  tools = other.tools;

  return *this;
  }


void ToolTable::processFile(QFile &file) {
  if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
     QTextStream in(&file);
     QString line = in.readLine();

     while (!line.isNull()) {
           processLine(line);
           line = in.readLine();
           }
     }
  }


void ToolTable::processLine(const QString &input) {
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
  tools.insert(number, ToolEntry(number
                               , length
                               , diameter
                               , quadrant
                               , frontAngle
                               , backAngle
                               , desc));
  }


ToolEntry ToolTable::tool(int number) {
  return tools[number];
  }


void ToolTable::dump() {
  for (const ToolEntry& te : tools) {
      te.dump();
      }
  }
