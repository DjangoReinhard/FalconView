#ifndef SYSEVENT_H
#define SYSEVENT_H
#include <QObject>


class SysEvent : public QObject
{
  Q_OBJECT
public:
  enum EventType {
    OperatorError
  , OperatorText
  , OperatorDisplay
  , NMLError
  , NMLText
  , NMLDisplay
    };

  explicit SysEvent(EventType et, const QString& what, QObject *parent = nullptr);
  explicit SysEvent(const SysEvent& o);

  SysEvent& operator=(const SysEvent& o);

private:
  EventType et;
  long      ts;
  QString   msg;
  };
#endif // SYSEVENT_H
