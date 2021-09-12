#ifndef TOOLTABLE_H
#define TOOLTABLE_H
#include <toolentry.h>
#include <QMap>
class QString;
class QFile;


class ToolTable
{
public:
  ToolTable(const QString& fileName = QString());
  ToolTable(QFile& file);
  ToolTable(const ToolTable&& other);

  ToolTable& operator = (const ToolTable&& other);
  ToolEntry tool(int num);
  void      dump();

protected:
  void processFile(QFile& file);
  void processLine(const QString& line);
  void addTool(const ToolEntry& tool);

private:
  QMap<int, ToolEntry> tools;
  };
#endif // TOOLTABLE_H
