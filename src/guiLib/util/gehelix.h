#ifndef GEHELIX_H
#define GEHELIX_H
#include <graphicelement.h>


class GEHelix : public GraphicElement
{
public:
  explicit GEHelix(const gp_Pnt& from, const gp_Pnt& to, const gp_Pnt& center, const gp_Dir& axis, bool ccw, int fullTurns=0, QObject *parent = nullptr);
  explicit GEHelix(const GEHelix& other);
  virtual ~GEHelix() = default;

  GEHelix& operator=(const GEHelix& other);

private:
  gp_Pnt end;
  gp_Pnt c;
  gp_Dir ca;
  bool   ccw;
  int    turns;
  };
#endif // GEHELIX_H
