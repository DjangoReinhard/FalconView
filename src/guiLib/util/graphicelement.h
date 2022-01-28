#ifndef GRAPHICELEMENT_H
#define GRAPHICELEMENT_H
#include <QObject>
#include <gp_Pnt.hxx>
#include <AIS_Shape.hxx>
class Quantity_Color;


class GraphicElement : public QObject
{
  Q_OBJECT
public:
  enum GEType {
    GELine
  , GEHelix
  , GERapid
  , GEBorder
    };
  GraphicElement& operator =(const GraphicElement& other);

  gp_Pnt from() const;
  gp_Pnt from();
  bool isNull() const;
  GEType type() const;
  void setColor(Quantity_Color c);
  void setShape(Handle(AIS_Shape) shape);
  Handle(AIS_Shape) shape() const;
  Handle(AIS_Shape) shape();


protected:
  explicit GraphicElement(GEType type, const gp_Pnt& from, QObject *parent = nullptr);
  explicit GraphicElement(const GraphicElement& other);
  virtual ~GraphicElement() = default;

private:
  GEType            gtype;
  Handle(AIS_Shape) elem;
  gp_Pnt            start;
  };
#endif // GRAPHICELEMENT_H
