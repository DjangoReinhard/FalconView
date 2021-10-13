#ifndef LINECODES_H
#define LINECODES_H
#include <interp_base.hh>


class LineCodes
{
public:
  LineCodes();

  void reset();

  double settings[ACTIVE_SETTINGS];
  int    gCodes[ACTIVE_G_CODES];
  int    mCodes[ACTIVE_M_CODES];
  };

#endif // LINECODES_H
