#ifndef TOOLENTRY_H
#define TOOLENTRY_H
#include <QString>
#include <emctool.h>
#ifdef toLine
#undef toLine
#endif


/**
 * @brief The ToolEntry class
 * entry of linuxcnc tooltable file
 */
class ToolEntry
{
public:
  ToolEntry();
  ToolEntry(int num, double length, double x, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description, int slot, int lineNum);
  ToolEntry(const ToolEntry& other);

  ToolEntry& operator = (const ToolEntry& other);

  int              number() const      { return canon.toolno;  }
  QString          description() const { return desc; }
  double           length() const      { return canon.offset.tran.z; }
  double           xOffset() const     { return canon.offset.tran.x; }
  double           diameter() const    { return canon.diameter; }
  double           frontAngle() const  { return canon.frontangle;  }
  double           backAngle() const   { return canon.backangle;   }
  int              quadrant() const    { return canon.orientation; }
  int              slot() const        { return canon.pocketno; }
  int              lineNum() const     { return serial; }
  CANON_TOOL_TABLE toCanon() const     { return canon; }
  void             dump() const;

  void setLength(double l);
  void setXOffset(double o);
  void setDiameter(double d);
  void setQuadrant(int q);
  void setFrontAngle(double a);
  void setBackAngle(double a);
  void setDescription(const QString& s);

private:
  QString          desc;
  int              serial;
  bool             dirty;
  CANON_TOOL_TABLE canon;
  };
#endif // TOOLENTRY_H
