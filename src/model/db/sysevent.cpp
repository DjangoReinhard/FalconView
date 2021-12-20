#include <sysevent.h>
#include <timestamp.h>
#include <QTime>


SysEvent::SysEvent(EventType et)
 : QObject(nullptr)
 , et(et)
 , ts(TimeStamp::rtSequence()) {
  }


SysEvent::SysEvent(const QString& what, EventType et)
 : QObject(nullptr)
 , et(et)
 , ts(TimeStamp::rtSequence())
 , msg(what) {
  }


SysEvent::SysEvent(EventType et, const QString& what, QObject *parent)
 : QObject(parent)
 , et(et)
 , ts(TimeStamp::rtSequence())
 , msg(what) {
  }


SysEvent::SysEvent(EventType et, const QString& what, const QTime& when)
 : QObject(nullptr)
 , et(et)
 , ts(when.msecsSinceStartOfDay())
 , msg(what) {
  }


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
