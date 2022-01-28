#ifndef GERAPIDMOVE_H
#define GERAPIDMOVE_H
#include <geline.h>


class GERapidMove : public GELine
{
public:
  explicit GERapidMove(const gp_Pnt& from, const gp_Pnt& to, QObject *parent = nullptr);
  explicit GERapidMove(const GERapidMove& other);
  virtual ~GERapidMove() = default;

  GERapidMove& operator=(const GERapidMove& other);
  };
#endif // GERAPIDMOVE_H
