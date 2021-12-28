#include <sysevent.h>
#ifdef HAVE_DATETIME
#include <QDateTime>
#else
#include <timestamp.h>
#endif


SysEvent::SysEvent(EventType et)
 : QObject(nullptr)
 , et(et)
#ifdef HAVE_DATETIME
 , ts(QDateTime::currentSecsSinceEpoch()) {
#else
 , ts(TimeStamp::rtSequence()) {
#endif
  }


SysEvent::SysEvent(const QString& what, EventType et)
 : QObject(nullptr)
 , et(et)
#ifdef HAVE_DATETIME
 , ts(QDateTime::currentSecsSinceEpoch())
#else
 , ts(TimeStamp::rtSequence())
#endif
 , msg(what) {
  }


SysEvent::SysEvent(EventType et, const QString& what, QObject *parent)
 : QObject(parent)
 , et(et)
#ifdef HAVE_DATETIME
 , ts(QDateTime::currentSecsSinceEpoch())
#else
 , ts(TimeStamp::rtSequence())
#endif
 , msg(what) {
  }


#ifdef HAVE_DATETIME
SysEvent::SysEvent(EventType et, const QString& what, const QDateTime& when)
 : QObject(nullptr)
 , et(et) 
 , ts(when.currentSecsSinceEpoch())
 , msg(what) {
  }
#endif


SysEvent::SysEvent(const SysEvent& o)
 : QObject(o.parent())
 , et(o.et)
 , ts(o.ts)
 , msg(o.msg) {
  }


SysEvent& SysEvent::operator=(const SysEvent &o) {
  setParent(o.parent());
  et  = o.et;
  ts  = o.ts;
  msg = o.msg;

  return *this;
  }


QString SysEvent::toString(EventType t) {
  switch (t) {
    case No_Error:        return tr("No_Error");
    case OperatorError:   return tr("OperatorError");
    case OperatorText:    return tr("OperatorText");
    case OperatorDisplay: return tr("OperatorDisplay");
    case SystemError:     return tr("SystemError");
    case NMLError:        return tr("NMLError");
    case NMLText:         return tr("NMLText");
    case NMLDisplay:      return tr("NMLDisplay");
    case NMLEvent:        return tr("NMLEvent");
    default:              return tr("SystemError");
    }
  }
