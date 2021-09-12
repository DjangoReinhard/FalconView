#include <toolentry.h>
#include <QDebug>


ToolEntry::ToolEntry()
 : num(-1)
 , desc("")
 , len(999)
 , diam(0)
 , fa(0)
 , ba(0)
 , quad(0) {
  }


ToolEntry::ToolEntry(int number, double length, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description)
 : num(number)
 , desc(description)
 , len(length)
 , diam(diameter)
 , fa(frontAngle)
 , ba(backAngle)
 , quad(quadrant) {
  }


ToolEntry::ToolEntry(const ToolEntry& other)
 : num(other.num)
 , desc(other.desc)
 , len(other.len)
 , diam(other.diam)
 , fa(other.fa)
 , ba(other.ba)
 , quad(other.quad) {
  }


ToolEntry& ToolEntry::operator=(const ToolEntry &other) {
  num   = other.num;
  desc  = other.desc;
  len   = other.len;
  diam  = other.diam;
  fa    = other.fa;
  ba    = other.ba;
  quad  = other.quad;

  return *this;
  }


void ToolEntry::dump() const {
  qDebug() << "\nTool Entry  #" << num;
  qDebug() <<   "description: " << desc;
  qDebug() <<   "     length: " << len;
  qDebug() <<   "   diameter: " << diam;
  qDebug() <<   "   quadrant: " << quad;
  qDebug() <<   "front angle: " << fa;
  qDebug() <<   " back angle: " << ba;
  }
