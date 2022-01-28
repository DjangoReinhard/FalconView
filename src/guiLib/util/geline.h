#ifndef GELINE_H
#define GELINE_H
#include "graphicelement.h"


class GELine : public GraphicElement
{
public:
  explicit GELine(const gp_Pnt& from, const gp_Pnt& to, QObject *parent = nullptr);
  explicit GELine(const GELine& other);
  virtual ~GELine() = default;

  GELine& operator=(const GELine& other);

  gp_Pnt to() const;
  gp_Pnt to();

protected:
  explicit GELine(GEType type, const gp_Pnt& from, const gp_Pnt& to, QObject *parent = nullptr);

private:
  gp_Pnt end;
  };
#endif // GELINE_H
