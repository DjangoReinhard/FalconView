#include <sysevent.h>
#include <timestamp.h>


SysEvent::SysEvent(EventType et, const QString& what, QObject *parent)
 : QObject(parent)
 , et(et)
 , ts(TimeStamp::rtSequence())
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
