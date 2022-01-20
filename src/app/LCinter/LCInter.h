#ifndef LCINTER_H
#define LCINTER_H
#include <QObject>
#include <QString>
class InterpBase;
class CanonIF;
class LcProperties;
class LCInterfaceP;
class ToolTable;
class QProcess;
class QTextStream;
class EMC_STAT;
class EMC_TOOL_STAT;


/**
 * @brief The outer shell to linuxCNC interpreter
 */
class LCInterface : public QObject
{
  Q_OBJECT
public:
  explicit LCInterface(CanonIF& cif, LcProperties& lcProperties, ToolTable& toolTable);
  virtual ~LCInterface();

  std::pair<QVector3D, QVector3D> machineLimits() const;
  void parseInline(const QString& fileName);
  void parseExt(const QString& fileName);
  void setupToolTable();

protected:
  void maybeNewLine();
  void maybeNewLine(int seqNum);
  int  readExec(const QString& line);

private:
  LCInterfaceP*  p;
  };
#endif
