#include <toolentry.h>
#include <QDebug>


ToolEntry::ToolEntry()
 : desc("")
 , serial(-1) {
  canon.toolno      = 0;
  canon.pocketno    = 0;
  canon.diameter    = 0;
  canon.frontangle  = 0;
  canon.backangle   = 0;
  canon.orientation = 1;
  }


ToolEntry::ToolEntry(int number, double length, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description, int slot, int lineNum)
 : desc(description)
 , serial(lineNum) {
  canon.offset.tran.z = length;
  canon.toolno        = number;
  canon.pocketno      = slot;
  canon.diameter      = diameter;
  canon.frontangle    = frontAngle;
  canon.backangle     = backAngle;
  canon.orientation   = quadrant;
  }


ToolEntry::ToolEntry(const ToolEntry& other)
 : desc(other.desc)
 , serial(other.serial) {
  canon.toolno        = other.canon.toolno;
  canon.pocketno      = other.canon.pocketno;
  canon.offset.tran.z = other.canon.offset.tran.z;
  canon.diameter      = other.canon.diameter;
  canon.frontangle    = other.canon.frontangle;
  canon.backangle     = other.canon.backangle;
  canon.orientation   = other.canon.orientation;
  }


ToolEntry& ToolEntry::operator=(const ToolEntry &other) {
  desc                = other.desc;
  canon.toolno        = other.canon.toolno;
  canon.pocketno      = other.canon.pocketno;
  canon.offset.tran.z = other.canon.offset.tran.z;
  canon.diameter      = other.canon.diameter;
  canon.frontangle    = other.canon.frontangle;
  canon.backangle     = other.canon.backangle;
  canon.orientation   = other.canon.orientation;
  serial              = other.serial;

  return *this;
  }


void ToolEntry::dump() const {
  qDebug() << "\nTool Entry  #" << number();
  qDebug() <<   "description: " << description();
  qDebug() <<   "     length: " << length();
  qDebug() <<   "   diameter: " << diameter();
  qDebug() <<   "   quadrant: " << quadrant();
  qDebug() <<   "front angle: " << frontAngle();
  qDebug() <<   " back angle: " << backAngle();
  qDebug() <<   "       slot: " << slot();
  qDebug() <<   "     serial: " << lineNum();
  }
