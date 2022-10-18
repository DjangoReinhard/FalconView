#ifndef ABSTRACTCOMMANDWRITER_H
#define ABSTRACTCOMMANDWRITER_H
#include <QObject>
class RCS_CMD_MSG;


class AbstractCommandWriter : public QObject
{
  Q_OBJECT
public:
  explicit AbstractCommandWriter(QObject *parent = nullptr);
  virtual ~AbstractCommandWriter() = default;

  virtual bool isActive() const = 0;
  virtual int  sendCommand(RCS_CMD_MSG& msg) = 0;
  };
#endif // ABSTRACTCOMMANDWRITER_H
