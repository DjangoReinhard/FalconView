#include <geline.h>


GELine::GELine(GEType type, const gp_Pnt& from, const gp_Pnt& to, QObject *parent)
 : GraphicElement(type, from, parent)
 , end(to) {
  }


GELine::GELine(const gp_Pnt& from, const gp_Pnt& to, QObject *parent)
 : GraphicElement(GraphicElement::GELine, from, parent)
 , end(to) {
  }


GELine::GELine(const GELine& other)
 : GraphicElement(other)
 , end(other.end) {
  }


GELine& GELine::operator=(const GELine &other) {
  if (&other == this) return *this;

  GraphicElement::operator=(other);
  end = other.end;

  return *this;
  }


gp_Pnt GELine::to() const {
  return end;
  }


gp_Pnt GELine::to() {
  return end;
  }
