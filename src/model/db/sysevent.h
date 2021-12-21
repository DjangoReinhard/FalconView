#ifndef SYSEVENT_H
#define SYSEVENT_H
#include <QObject>

#define HAVE_DATETIME

class SysEvent : public QObject
{
  Q_OBJECT
public:
  enum EventType {
    No_Error
  , OperatorError
  , OperatorText
  , OperatorDisplay
  , SystemError
  , NMLError
  , NMLText
  , NMLDisplay
  , NMLEvent
    };
  static QString toString(EventType t);

  explicit SysEvent(EventType et = No_Error);
  explicit SysEvent(const QString& what, EventType et = SystemError);
  explicit SysEvent(EventType et, const QString& what, QObject *parent = nullptr);
#ifdef HAVE_DATETIME
  explicit SysEvent(EventType et, const QString& what, const QDateTime& when);
#endif
  explicit SysEvent(const SysEvent& o);

  SysEvent& operator=(const SysEvent& o);

  EventType      type() const { return et; }
  long           when() const { return ts; }
  const QString& what() const { return msg; }

private:
  EventType et;
  long      ts;
  QString   msg;
  };
#endif // SYSEVENT_H
