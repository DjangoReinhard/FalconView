#include <graphicelement.h>


GraphicElement::GraphicElement(GEType type, const gp_Pnt& from, QObject *parent)
 : QObject(parent)
 , gtype(type)
 , start(from) {
  }


GraphicElement::GraphicElement(const GraphicElement& other)
 : QObject(other.parent())
 , gtype(other.gtype)
 , start(other.start) {
  }


gp_Pnt GraphicElement::from() const {
  return start;
  }


gp_Pnt GraphicElement::from() {
  return start;
  }


bool GraphicElement::isNull() const {
  return elem.IsNull();
  }


GraphicElement& GraphicElement::operator=(const GraphicElement &other) {
  if (&other == this) return *this;

  gtype = other.type();
  setParent(other.parent());
  start = other.start;

  return *this;
  }


void GraphicElement::setColor(Quantity_Color c) {
  if (!elem.IsNull()) elem->SetColor(c);
  }


void GraphicElement::setShape(Handle(AIS_Shape) shape) {
  elem = shape;
  elem->SetWidth(2);
  }


Handle(AIS_Shape) GraphicElement::shape() const {
  return elem;
  }


Handle(AIS_Shape) GraphicElement::shape() {
  return elem;
  }


GraphicElement::GEType GraphicElement::type() const {
  return gtype;
  }
