#ifndef GCODEINFO_H
#define GCODEINFO_H
#include <valuemanager.h>
class QString;


class GCodeInfo
{
public:
  GCodeInfo();

  void update(int* activeGCodes
            , int* activeMCodes
            , const QString& fileName
            , int  curLine);

protected:
  ValueManager vm;
  };
#endif // GCODEINFO_H
