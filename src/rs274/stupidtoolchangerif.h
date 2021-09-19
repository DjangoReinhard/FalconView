#ifndef STUPIDTOOLCHANGERIF_H
#define STUPIDTOOLCHANGERIF_H
#include <QDebug>


/**
 * @brief The StupidToolChangerIF class - dumb model of a tool changer as required by lc
 */
class StupidToolChangerIF
{
public:
  StupidToolChangerIF();

  int  slot4ToolInSpindle() const  {
       qDebug() << "CHANGER: return slot of tool in spindle #" << actualSlot;

       return actualSlot;
       }
  int  nextTool() const      {
       qDebug() << "CHANGER: return tool number of next tool #" << nextToolNum;

       return nextToolNum;
       }
  void selectNextTool(int toolNum) {
       qDebug() << "CHANGER: SET tool number of next tool #" << toolNum;
       nextToolNum = toolNum;
       }
  void setCurrentTool(int slot)    {
       qDebug() << "CHANGER: SET slot for tool in spindle #" << slot;
       actualSlot = slot;
       }

private:
  int   actualSlot;
  int   nextToolNum;
  };
#endif // STUPIDTOOLCHANGERIF_H
