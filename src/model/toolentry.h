#ifndef TOOLENTRY_H
#define TOOLENTRY_H
#include <QString>


class ToolEntry
{
public:
  ToolEntry();
  ToolEntry(int num, double length, double diameter, int quadrant, double frontAngle, double backAngle, const QString& description);
  ToolEntry(const ToolEntry& other);

  ToolEntry& operator = (const ToolEntry& other);

  int     number()      { return num;  }
  QString description() { return desc; }
  double  length()      { return len;  }
  double  diameter()    { return diam; }
  double  frontAngle()  { return fa;   }
  double  backAngle()   { return ba;   }
  int     quadrant()    { return quad; }
  void    dump() const;

private:
  int     num;
  QString desc;
  double  len;
  double  diam;
  double  fa;
  double  ba;
  int     quad;
  };
#endif // TOOLENTRY_H
