#include <commandwriter.h>
#include <valuemanager.h>
#include <valuemodel.h>
#include <sysevent.h>
#include <stat_msg.hh>
#include <cmd_msg.hh>
#include <emc_nml.hh>
#include <config.h>
#include <stdio.h>
#include <cstring>
#include <sys/time.h>
#include <QDebug>


CommandWriter::CommandWriter(QObject *parent)
 : QObject(parent) {
  cCmd = new RCS_CMD_CHANNEL(emcFormat, "emcCommand", "xemc", EMC2_DEFAULT_NMLFILE);
  if (!cCmd || !cCmd->valid()) {
     delete cCmd;
     cCmd = NULL;
     }
  cStat = new RCS_STAT_CHANNEL(emcFormat, "emcStatus", "xemc", EMC2_DEFAULT_NMLFILE);
  if (!cStat || !cStat->valid()) {
     delete cCmd;
     delete cStat;
     cCmd  = NULL;
     cStat = NULL;
     }
  else {
     status = static_cast<EMC_STAT*>(cStat->get_address());
     }
  }


bool CommandWriter::isActive() {
  return cCmd && cCmd->valid() && cStat && cStat->valid();
  }


int CommandWriter::sendCommand(RCS_CMD_MSG& msg) {
  if (!cCmd  || !cCmd->valid())  return -1;
  if (!cStat || !cStat->valid()) return -2;
  if (cCmd->write(&msg))         return -3;
  double end = 0;

  while (end < EMC_COMMAND_TIMEOUT) {
        cStat->peek();
        end += EMC_COMMAND_DELAY;

        if ((status->echo_serial_number - msg.serial_number) >= 0) return 0;
        sleep(EMC_COMMAND_DELAY);
        }
  return 0;
  }


void CommandWriter::sleep(double seconds) {
  struct timeval tv;

  tv.tv_sec  = seconds;
  tv.tv_usec = seconds * 1000000;
  select (0, NULL, NULL, NULL, &tv);
  }


void CommandWriter::jogStep(int axis, double stepSize, double speed) {
  EMC_JOG_INCR ji;

  qDebug() << "CW::jogStep" << axis << ", " << stepSize << ", " << speed;
  ji.joint_or_axis = axis;
  ji.incr          = stepSize;
  ji.vel           = speed;
  ji.jjogmode      = 0;  
  if (!sendCommand(ji)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("jogStep(%1, %2, %3)")
                                                .arg(axis)
                                                .arg(stepSize)
                                                .arg(speed));
  }


void CommandWriter::jogStart(int axis, double speed) {
  EMC_JOG_CONT jc;

  qDebug() << "CW::jogStart" << axis << ", " << speed;
  jc.joint_or_axis = axis;
  jc.vel           = speed;
  jc.jjogmode      = 0;
  if (!sendCommand(jc)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("jogStart(%1, %2)")
                                                .arg(axis)
                                                .arg(speed));
  }


void CommandWriter::jogStop(int axis) {
  EMC_JOG_STOP js;

  qDebug() << "CW::jogStop" << axis;
  js.joint_or_axis = axis;
  js.jjogmode      = 0;
  if (!sendCommand(js)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("jogStop(%1)")
                                                .arg(axis));
  }


void CommandWriter::homeAxis(int jointNum) {
  EMC_JOINT_HOME jh;

  qDebug() << "CW::homeAxis" << jointNum;
  jh.joint = jointNum;
  if (!sendCommand(jh)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("homeAxis(%1)")
                                                .arg(jointNum));
  }


void CommandWriter::loadTaskPlan(const QString& gcodeFile) {
  EMC_TASK_PLAN_CLOSE pc;
  EMC_TASK_PLAN_OPEN  po;

  qDebug() << "CW::loadTaskPlan" << gcodeFile;
  sendCommand(pc);
  strncpy(po.file, gcodeFile.toStdString().c_str(), LINELEN);
  if (!sendCommand(po)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("loadTaskPlan(%1)")
                                                .arg(gcodeFile));
  }


void CommandWriter::loadToolTable(const QString& toolTableFile) {
  EMC_TOOL_LOAD_TOOL_TABLE ltt;

  qDebug() << "CW::loadToolTable" << toolTableFile;
  strncpy(ltt.file, toolTableFile.toStdString().c_str(), LINELEN);
  if (!sendCommand(ltt)) emit systemEvent(SysEvent::EventType::NMLEvent
                                        , QString("loadToolTable(%1)")
                                                 .arg(toolTableFile));
  }


void CommandWriter::sendMDICommand(const QString& command) {
  EMC_TASK_PLAN_EXECUTE pe;

  qDebug() << "CW::sendMDICommand" << command;
  strncpy(pe.command, command.toStdString().c_str(), LINELEN);
  if (!sendCommand(pe)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("send MDI >%1<")
                                                .arg(command));
  }


#define LOCAL_AUTO_RUN      (0)
#define LOCAL_AUTO_PAUSE    (1)
#define LOCAL_AUTO_RESUME   (2)
#define LOCAL_AUTO_STEP     (3)
#define LOCAL_AUTO_REVERSE  (4)
#define LOCAL_AUTO_FORWARD  (5)

void CommandWriter::setAuto(int autoMode, int line) {
  QString msg;
  int     rv = 0;

  switch (autoMode) {
    case 0: {
         EMC_TASK_PLAN_RUN pr;

         qDebug() << "CW::taskPlan run (line #" << line << ")";
         pr.line = line;
         msg = QString("setAuto(run) - line: %d").arg(line);
         rv = sendCommand(pr);
         } break;
    case 1: {
         EMC_TASK_PLAN_PAUSE pp;

         qDebug() << "CW::taskPlan pause";
         msg = "setAuto(pause)";
         rv = sendCommand(pp);
         } break;
    case 2: {
         EMC_TASK_PLAN_RESUME pr;

         qDebug() << "CW::taskPlan resume";
         msg = "setAuto(resume)";
         rv = sendCommand(pr);
         } break;
    case 3: {
         EMC_TASK_PLAN_STEP ps;

         qDebug() << "CW::taskPlan step";
         msg = "setAuto(step)";
         rv = sendCommand(ps);
         } break;
    case 4: {
         EMC_TASK_PLAN_REVERSE pr;

         qDebug() << "CW::taskPlan reverse";
         msg = "setAuto(reverse)";
         rv = sendCommand(pr);
         } break;
    case 5: {
         EMC_TASK_PLAN_FORWARD pf;

         qDebug() << "CW::taskPlan forward";
         msg = "setAuto(forward)";
         rv = sendCommand(pf);
         } break;
    }
  if (!rv) emit systemEvent(SysEvent::EventType::NMLEvent, msg);
  }


void CommandWriter::enableBlockDelete(bool enable) {
  EMC_TASK_PLAN_SET_BLOCK_DELETE bd;

  qDebug() << "CW: enable block delete" << (enable ? "ON" : "OFF");
  if (enable) bd.state = 1;
  else        bd.state = 0;
  if (!sendCommand(bd)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("enable block delete >%1<")
                                                .arg(enable ? "ON" : "OFF"));
  }


void CommandWriter::setFeedOverride(double rate) {
  EMC_TRAJ_SET_SCALE ss;

  qDebug() << "CW: setFeedOverride" << rate;
  ss.scale = rate;
  if (!sendCommand(ss)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("feed override >%1<")
                                                .arg(rate));
  }


void CommandWriter::enableFlood(bool enable) {
  qDebug() << "CW::enableFlood" << (enable ? "ON" : "OFF");
  int rv;

  if (enable) {
     EMC_COOLANT_FLOOD_ON fo;

     rv = sendCommand(fo);
     }
  else {
     EMC_COOLANT_FLOOD_OFF fo;

     rv = sendCommand(fo);
     }
  if (!rv) emit systemEvent(SysEvent::EventType::NMLEvent
                          , QString("enable flood >%1<")
                                   .arg(enable ? "ON" : "OFF"));
  }


void CommandWriter::enableMist(bool enable) {
  qDebug() << "CW::enableMist" << (enable ? "ON" : "OFF");
  int rv;

  if (enable) {
     EMC_COOLANT_MIST_ON mo;

     rv = sendCommand(mo);
     }
  else {
     EMC_COOLANT_MIST_OFF mo;

     rv = sendCommand(mo);
     }
  if (!rv) emit systemEvent(SysEvent::EventType::NMLEvent
                          , QString("enable mist >%1<")
                                   .arg(enable ? "ON" : "OFF"));
  }


void CommandWriter::enableOptionalStop(bool enable) {
  qDebug() << "CW::enableOptionalStop" << (enable ? "ON" : "OFF");
  EMC_TASK_PLAN_SET_OPTIONAL_STOP os;

  os.state = enable;
  if (!sendCommand(os)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("enable optional stop >%1<")
                                                .arg(enable ? "ON" : "OFF"));
  }


void CommandWriter::setRapidOverride(double rate) {
  EMC_TRAJ_SET_RAPID_SCALE rs;

  qDebug() << "CW: set rapid override" << rate;
  rs.scale = rate;
  if (!sendCommand(rs)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("rapid override >%1<")
                                                .arg(rate));
  }


void CommandWriter::setSpindle(bool enable, int speed, int direction) {
  int rv;

  if (enable) {
     EMC_SPINDLE_ON so;

     qDebug() << "CW::setSpindle(" << (enable ? "ON": "OFF") << ", " << speed << ", " << direction;
     so.speed = direction * speed;
     so.spindle = 0;
     rv = sendCommand(so);
     }
  else {
     EMC_SPINDLE_OFF so;

     qDebug() << "CW::setSpindle() off";
     so.spindle = 0;
     rv = sendCommand(so);
     }
  if (!rv) emit systemEvent(SysEvent::EventType::NMLEvent
                          , QString("spindle >%1<, %2, %3")
                                   .arg(enable ? "ON" : "OFF")
                                   .arg(speed)
                                   .arg(direction));
  }


void CommandWriter::setSpindleOverride(double rate) {
  EMC_TRAJ_SET_SPINDLE_SCALE ss;

  qDebug() << "CW::setSpindleOverride" << rate;
  ss.spindle = 0;
  ss.scale = rate;
  if (!sendCommand(ss)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("spindle override >%1<")
                                                .arg(rate));
  }


void CommandWriter::setTaskMode(int mode) {
  EMC_TASK_SET_MODE sm;

  qDebug() << "CW::set task mode" << mode;
  sm.mode = static_cast<EMC_TASK_MODE_ENUM>(mode);
  if (!sendCommand(sm)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("set task mode >%1<")
                                                .arg(mode));
  }


void CommandWriter::setTaskState(int state) {
  EMC_TASK_SET_STATE ss;

  qDebug() << "CW:: set task state" << state;
  ss.state = static_cast<EMC_TASK_STATE_ENUM>(state);
  if (!sendCommand(ss)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("set task state >%1<")
                                                .arg(state));
  }


void CommandWriter::abortTask() {
  EMC_TASK_ABORT ta;

  qDebug() << "CW: abort task";
  if (!sendCommand(ta)) emit systemEvent(SysEvent::EventType::NMLEvent
                                       , QString("abort task"));
  }


void CommandWriter::taskPlanSynch() {
  EMC_TASK_PLAN_SYNCH synch;

  qDebug() << "abort task";
  if (!sendCommand(synch)) emit systemEvent(SysEvent::EventType::NMLEvent
                                            , QString("task plan synch"));
  }

const int    CommandWriter::EMC_COMMAND_TIMEOUT = 5.0;  // how long to wait until timeout
const double CommandWriter::EMC_COMMAND_DELAY   = 0.01; // seconds to sleep between checks
