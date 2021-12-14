#include <toolentry.h>
#include <QDebug>
#include <cstring>


ToolEntry::ToolEntry()
 : desc("")
 , serial(-1)
 , dirty(false) {
  memset(&canon, 0, sizeof(canon));
  }


ToolEntry::ToolEntry(int number, double length, double x, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description, int slot, int lineNum)
 : desc(description)
 , serial(lineNum)
 , dirty(false) {
  memset(&canon, 0, sizeof(canon));
  canon.offset.tran.z = length;
  canon.offset.tran.x = x;
  canon.toolno        = number;
  canon.pocketno      = slot;
  canon.diameter      = diameter;
  canon.frontangle    = frontAngle;
  canon.backangle     = backAngle;
  canon.orientation   = quadrant;
  }


ToolEntry::ToolEntry(const ToolEntry& other)
 : desc(other.desc)
 , serial(other.serial)
 , dirty(other.dirty) {
  memcpy(&canon, &other.canon, sizeof(canon));
  }


ToolEntry& ToolEntry::operator=(const ToolEntry &other) {
  desc                = other.desc;
  memcpy(&canon, &other.canon, sizeof(canon));
  serial              = other.serial;
  dirty               = other.dirty;

  return *this;
  }


void ToolEntry::dump() const {
  qDebug() << "\nTool Entry  #" << number();
  qDebug() <<   "description: " << description();
  qDebug() <<   "  length(Z): " << length();
  qDebug() <<   "     X-offs: " << xOffset();
  qDebug() <<   "   diameter: " << diameter();
  qDebug() <<   "   quadrant: " << quadrant();
  qDebug() <<   "front angle: " << frontAngle();
  qDebug() <<   " back angle: " << backAngle();
  qDebug() <<   "       slot: " << slot();
  qDebug() <<   "     serial: " << lineNum();
  }


void ToolEntry::setLength(double l) {
  canon.offset.tran.z = l;
  dirty = true;
  }


void ToolEntry::setXOffset(double o) {
  canon.offset.tran.x = o;
  dirty = true;
  }


void ToolEntry::setDiameter(double d) {
  canon.diameter = d;
  dirty = true;
  }


void ToolEntry::setQuadrant(int q) {
  canon.orientation = q;
  dirty = true;
  }


void ToolEntry::setPixmap(const QPixmap& pm) {
  this->pm = pm;
  }


void ToolEntry::setFrontAngle(double a) {
  canon.frontangle = a;
  dirty = true;
  }


void ToolEntry::setBackAngle(double a) {
  canon.backangle = a;
  dirty = true;
  }


void ToolEntry::setDescription(const QString &s) {
  desc = s;
  dirty = true;
  }


QString ToolEntry::toLine() const {
  QString rv;

  rv += QString("T%1").arg(canon.toolno);
  rv += QString(" P%1").arg(canon.pocketno);
  if (canon.offset.tran.x) rv += QString(" X%1").arg(canon.offset.tran.x, 0, 'f', 3);
  if (canon.offset.tran.y) rv += QString(" Y%1").arg(canon.offset.tran.y, 0, 'f', 3);
  rv += QString(" Z%1").arg(canon.offset.tran.z, 0, 'f', 3);
  rv += QString(" D%1").arg(canon.diameter, 0, 'f', 3);
  if (canon.offset.a) rv += QString(" A%1").arg(canon.offset.a, 0, 'f', 3);
  if (canon.offset.b) rv += QString(" B%1").arg(canon.offset.b, 0, 'f', 3);
  if (canon.offset.c) rv += QString(" C%1").arg(canon.offset.c, 0, 'f', 3);
  if (canon.offset.u) rv += QString(" U%1").arg(canon.offset.u, 0, 'f', 3);
  if (canon.offset.v) rv += QString(" V%1").arg(canon.offset.v, 0, 'f', 3);
  if (canon.offset.w) rv += QString(" W%1").arg(canon.offset.w, 0, 'f', 3);
  if (canon.frontangle) rv += QString(" I%1").arg(canon.frontangle, 0, 'f', 3);
  if (canon.backangle) rv += QString(" J%1").arg(canon.backangle, 0, 'f', 3);
  if (canon.orientation) rv += QString(" Q%1").arg(canon.orientation);
  rv += " ;";
  rv += desc;
  rv += "\n";

  return rv;
  }
