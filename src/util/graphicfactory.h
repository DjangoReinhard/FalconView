#ifndef GRAPHICFACTORY_H
#define GRAPHICFACTORY_H
#include <AIS_Shape.hxx>


class GraphicFactory
{
public:
  Handle(AIS_Shape) createArc(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, bool ccw);
  Handle(AIS_Shape) createHelix(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, const gp_Dir& axis, bool ccw, int fullTurns = 0);
  Handle(AIS_Shape) createLine(const gp_Pnt& from, const gp_Pnt& to);
  };
#endif // GRAPHICFACTORY_H
