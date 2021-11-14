#ifndef ERRORREADER_H
#define ERRORREADER_H
#include <QObject>
#include <sysevent.h>
class NML;


class ErrorReader : public QObject
{
  Q_OBJECT
public:
  explicit ErrorReader(QObject *parent = nullptr);

  SysEvent fetchMessage();

private:
  NML* ec;
  };
#endif // ERRORREADER_H
