#ifndef LCINTER_H
#define LCINTER_H
#include <QObject>
#include <QString>
#include <linecodes.h>
class InterpBase;
class LcProperties;
class ToolTable;
class QProcess;
class QTextStream;
class EMC_STAT;
class EMC_TOOL_STAT;

#define USE_INTERNAL_INTERPRETER


class LCInterface : public QObject
{
  Q_OBJECT
public:
  explicit LCInterface(LcProperties& lcProperties, ToolTable& toolTable);
  virtual ~LCInterface();

  void parseInline(const QString& fileName);
  void parseExt(const QString& fileName);

  void setupToolTable();

protected:
  void maybeNewLine();
  void maybeNewLine(int seqNum);
  int  readExec(const QString& line);

protected slots:
//  void processLine(long sequence, long lineNum, const QString& line);
//  void errorString(const QString& msg);

private:
  InterpBase*    pInter;
  LcProperties&  lcProperties;
  ToolTable&     toolTable;
  int            lastSeqNum;
  int            errInter;
  LineCodes      lineCodes;
  QProcess*      child;
  EMC_STAT*      emcStatus;
  EMC_TOOL_STAT* toolStatus;
  double         xLast;
  double         yLast;
  double         zLast;
  };
#endif
