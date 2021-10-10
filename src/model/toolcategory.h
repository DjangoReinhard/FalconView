#ifndef TOOLCATEGORY_H
#define TOOLCATEGORY_H
#include <QObject>
#include <QVariant>
#include <QVector>
//#include <tool.h>
class ToolCategory;


class ToolCategory : public QObject
{
  Q_OBJECT
public:
  ToolCategory(int id, const QString& name, ToolCategory* parent = nullptr);

  void          appendChild(ToolCategory* child);
  ToolCategory* child(int row);
  ToolCategory* parent();
  int           columnCount()    const;
  int           childCount()     const;
  QVariant      data(int column) const;
  int           row()            const;
  void          dump();

private:
//  QMap<QString, int> pool;
  QVector<ToolCategory*> children;
//  QMap<int, Tool>        tools;
  int     id;
  QString name;
  };

#endif // TOOLCATEGORY_H
