#ifndef TOOLTABLE_H
#define TOOLTABLE_H
#include <toolentry.h>
#include <QAbstractTableModel>
#include <QListIterator>
#include <QString>
#include <QList>
#include <QMap>
class QFile;
class QModelIndex;

/**
 * @brief The ToolTable class
 * parse and hold tooltable of linuxcnc
 */
class ToolTable : public QAbstractTableModel
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
  void             save();
  void             setCurrent(int lineNum);
  QList<ToolEntry*>::Iterator begin()            { return tools.begin(); }
  QList<ToolEntry*>::Iterator end()              { return tools.end();   }
  QList<ToolEntry*>::ConstIterator begin() const { return tools.begin(); }
  QList<ToolEntry*>::ConstIterator end() const   { return tools.end();   }

  // for AbstractTableModel
  int rowCount(const QModelIndex &parent) const override;
  int columnCount(const QModelIndex &parent) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
//  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
//  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());


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
