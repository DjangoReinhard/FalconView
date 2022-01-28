#ifndef GRAPHICFACTORY_H
#define GRAPHICFACTORY_H
class gp_Pnt;
class gp_Dir;
class GELine;
class GEHelix;
class GERapidMove;


class GraphicFactory
{
public:
//  GraphicElement* createArc(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, bool ccw);
  GEHelix*     createHelix(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, const gp_Dir& axis, bool ccw, int fullTurns = 0);
  GELine*      createLine(const gp_Pnt& from, const gp_Pnt& to);
  GERapidMove* createRapidMove(const gp_Pnt& from, const gp_Pnt& to);
  };
#endif // GRAPHICFACTORY_H
