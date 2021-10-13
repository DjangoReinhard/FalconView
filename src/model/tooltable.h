#ifndef TOOLTABLE_H
#define TOOLTABLE_H
#include <toolentry.h>
#include <QListIterator>
#include <QString>
#include <QList>
#include <QMap>
class QFile;


/**
 * @brief The ToolTable class
 * parse and hold tooltable of linuxcnc
 */
class ToolTable
{
public:
  ToolTable(const QString& fileName = QString());
  ToolTable(QFile& file);
  ToolTable(const ToolTable&& other);
 ~ToolTable();

  ToolTable&       operator = (const ToolTable&& other);
  const ToolEntry& current() const  { return curTool; }
  const ToolEntry* tool(int num) const;
  QString          fileName() const { return fn; }
  void             dump();
  void             setCurrent(int lineNum);
  QList<ToolEntry*>::Iterator begin()            { return tools.begin(); }
  QList<ToolEntry*>::Iterator end()              { return tools.end();   }
  QList<ToolEntry*>::ConstIterator begin() const { return tools.begin(); }
  QList<ToolEntry*>::ConstIterator end() const   { return tools.end();   }

protected:
  void processFile(QFile& file);
  void processLine(int lineNum, const QString& line);
  void addTool(const ToolEntry& tool);

private:
  QMap<int, ToolEntry*> mappedTools;
  QList<ToolEntry*>     tools;
  ToolEntry             curTool;
  QString               fn;
  };
#endif // TOOLTABLE_H
