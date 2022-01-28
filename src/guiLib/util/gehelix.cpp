#include <gehelix.h>

GEHelix::GEHelix(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, const gp_Dir& axis, bool ccw, int fullTurns, QObject *parent)
 : GraphicElement(GraphicElement::GEHelix, from, parent)
 , end(to)
 , c(center)
 , ca(axis)
 , ccw(ccw)
 , turns(fullTurns) {
  }


GEHelix::GEHelix(const GEHelix& other)
 : GraphicElement(other)
 , end(other.end)
 , c(other.c)
 , ca(other.ca)
 , ccw(other.ccw)
 , turns(other.turns) {
  }


GEHelix& GEHelix::operator=(const GEHelix &other) {
  if (&other == this) return *this;

  end   = other.end;
  c     = other.c;
  ca    = other.ca;
  ccw   = other.ccw;
  turns = other.turns;

  return *this;
  }

