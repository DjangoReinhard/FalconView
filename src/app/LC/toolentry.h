#ifndef TOOLENTRY_H
#define TOOLENTRY_H
#include <QString>
#include <QPixmap>
class QTextStream;
class PToolEntry;
struct CANON_TOOL_TABLE;


/**
 * @brief The ToolEntry class
 * entry of linuxcnc tooltable file
 */
class ToolEntry
{
public:
  ToolEntry(const ToolEntry* p = nullptr);
  ToolEntry(int num, double length, double x, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description, int slot, int lineNum);
  ToolEntry(const ToolEntry& other);
  ToolEntry(ToolEntry&& other);
 ~ToolEntry();

  ToolEntry& operator = (const ToolEntry& other);

  int              number() const;
  QString          description() const;
  QString          toolType() const;
  double           length() const;
  double           xOffset() const;
  double           diameter() const;
  double           frontAngle() const;
  double           backAngle() const;
  int              quadrant() const;
  QPixmap          icon() const;
  int              slot() const;
  int              lineNum() const;
  void             toCanon(CANON_TOOL_TABLE*) const;
  QString          toLine() const;
  void             dump() const;

  void setLength(double l);
  void setXOffset(double o);
  void setDiameter(double d);
  void setQuadrant(int q);
  void setFrontAngle(double a);
  void setBackAngle(double a);
  void setSlot(int slot);
  void setDescription(const QString& s);
  void setToolType(const QString& tt);
  void setPixmap(const QPixmap& icon);

private:
  PToolEntry* p;
  };
#endif // TOOLENTRY_H
