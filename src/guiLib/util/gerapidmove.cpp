#include <gerapidmove.h>


GERapidMove::GERapidMove(const gp_Pnt& from, const gp_Pnt& to, QObject *parent)
 : GELine(GERapid, from, to, parent) {
  }


GERapidMove::GERapidMove(const GERapidMove& other)
  : GELine(other) {
  }


GERapidMove& GERapidMove::operator=(const GERapidMove &other) {
  if (&other == this) return *this;

  GELine::operator=(other);

  return *this;
  }
