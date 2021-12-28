#ifndef TOOL_H
#define TOOL_H
#include <QObject>
class ToolCategory;

class Tool : public QObject
{
  Q_OBJECT
public:
  explicit Tool(QObject *parent = nullptr);

private:
  ToolCategory* parent;
  };
#endif // TOOL_H
