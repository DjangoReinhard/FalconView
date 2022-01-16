#include <toolentry.h>
#include <QDebug>
#include <cstring>
#include <emctool.h>
#ifdef toLine
#undef toLine
#endif


class PToolEntry
{
public:
  PToolEntry();
  PToolEntry(int num, double length, double x, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description, int slot, int lineNum);
  PToolEntry(const PToolEntry* other);

  PToolEntry& operator=(const PToolEntry& other);

private:
  QString          desc;
  QString          tt;
  QPixmap          pm;
  int              serial;
  bool             dirty;
  CANON_TOOL_TABLE canon;
  friend class ToolEntry;
  };


PToolEntry::PToolEntry()
 : serial(-1)
 , dirty(false) {
  memset(&canon, 0, sizeof(canon));
  }


PToolEntry::PToolEntry(int number, double length, double x, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description, int slot, int lineNum)
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


PToolEntry::PToolEntry(const PToolEntry* other)
 : desc(other->desc)
 , tt(other->tt)
 , pm(other->pm)
 , serial(other->serial)
 , dirty(other->dirty) {
  memcpy(&canon, &other->canon, sizeof(canon));
  }


PToolEntry& PToolEntry::operator=(const PToolEntry &other) {
  desc   = other.desc;
  tt     = other.tt;
  pm     = other.pm;
  serial = other.serial;
  dirty  = other.dirty;
  canon  = other.canon;

  return *this;
  }

ToolEntry::ToolEntry(const ToolEntry* other)
 : p(new PToolEntry()) {
  if (other) *this = *other;
  }


ToolEntry::ToolEntry(int number, double length, double x, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description, int slot, int lineNum) 
 : p(new PToolEntry(number, length, x, diameter, quadrant, frontAngle, backAngle, description, slot, lineNum)) {
  }


ToolEntry::ToolEntry(const ToolEntry& other)
 : p(new PToolEntry(other.p)) {
  }


ToolEntry::~ToolEntry() {
  delete p;
  }


ToolEntry& ToolEntry::operator=(const ToolEntry &other) {
  p = new PToolEntry(other.p);

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

int              ToolEntry::number() const      { return p->canon.toolno;  }
QString          ToolEntry::description() const { return p->desc; }
QString          ToolEntry::toolType() const    { return p->tt; }
double           ToolEntry::length() const      { return p->canon.offset.tran.z; }
double           ToolEntry::xOffset() const     { return p->canon.offset.tran.x; }
double           ToolEntry::diameter() const    { return p->canon.diameter; }
double           ToolEntry::frontAngle() const  { return p->canon.frontangle;  }
double           ToolEntry::backAngle() const   { return p->canon.backangle;   }
int              ToolEntry::quadrant() const    { return p->canon.orientation; }
QPixmap          ToolEntry::icon() const        { return p->pm; }
int              ToolEntry::slot() const        { return p->canon.pocketno; }
int              ToolEntry::lineNum() const     { return p->serial; }


void ToolEntry::setLength(double l) {
  p->canon.offset.tran.z = l;
  p->dirty = true;
  }


void ToolEntry::setXOffset(double o) {
  p->canon.offset.tran.x = o;
  p->dirty = true;
  }


void ToolEntry::setDiameter(double d) {
  p->canon.diameter = d;
  p->dirty = true;
  }


void ToolEntry::setQuadrant(int q) {
  p->canon.orientation = q;
  p->dirty = true;
  }


void ToolEntry::setPixmap(const QPixmap& pm) {
  p->pm = pm;
  }


void ToolEntry::setFrontAngle(double a) {
  p->canon.frontangle = a;
  p->dirty = true;
  }


void ToolEntry::setBackAngle(double a) {
  p->canon.backangle = a;
  p->dirty = true;
  }


void ToolEntry::setDescription(const QString &s) {
  p->desc = s;
  p->dirty = true;
  }


void ToolEntry::setToolType(const QString &tt) {
  p->tt = tt;
  p->dirty = true;
  }


void ToolEntry::setSlot(int slot) {
  p->canon.pocketno = slot;
  }


void ToolEntry::toCanon(CANON_TOOL_TABLE *pCTT) const {
  if (!pCTT) return;
  memcpy(pCTT, &p->canon, sizeof(CANON_TOOL_TABLE));
  }


QString ToolEntry::toLine() const {
  QString rv;

  rv += QString("T%1").arg(p->canon.toolno);
  rv += QString(" P%1").arg(p->canon.pocketno);
  if (p->canon.offset.tran.x) rv += QString(" X%1").arg(p->canon.offset.tran.x, 0, 'f', 3);
  if (p->canon.offset.tran.y) rv += QString(" Y%1").arg(p->canon.offset.tran.y, 0, 'f', 3);
  rv += QString(" Z%1").arg(p->canon.offset.tran.z, 0, 'f', 3);
  rv += QString(" D%1").arg(p->canon.diameter, 0, 'f', 3);
  if (p->canon.offset.a) rv += QString(" A%1").arg(p->canon.offset.a, 0, 'f', 3);
  if (p->canon.offset.b) rv += QString(" B%1").arg(p->canon.offset.b, 0, 'f', 3);
  if (p->canon.offset.c) rv += QString(" C%1").arg(p->canon.offset.c, 0, 'f', 3);
  if (p->canon.offset.u) rv += QString(" U%1").arg(p->canon.offset.u, 0, 'f', 3);
  if (p->canon.offset.v) rv += QString(" V%1").arg(p->canon.offset.v, 0, 'f', 3);
  if (p->canon.offset.w) rv += QString(" W%1").arg(p->canon.offset.w, 0, 'f', 3);
  if (p->canon.frontangle) rv += QString(" I%1").arg(p->canon.frontangle, 0, 'f', 3);
  if (p->canon.backangle) rv += QString(" J%1").arg(p->canon.backangle, 0, 'f', 3);
  if (p->canon.orientation) rv += QString(" Q%1").arg(p->canon.orientation);
  rv += " ;";
  rv += p->desc;
  rv += " | ";
  rv += p->tt;
  rv += "\n";

  return rv;
  }
