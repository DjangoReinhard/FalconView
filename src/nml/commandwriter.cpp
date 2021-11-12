#include <commandwriter.h>
#include <stat_msg.hh>
#include <cmd_msg.hh>
#include <emc_nml.hh>
#include <stdio.h>
#include <cstring>
#include <sys/time.h>


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

  ji.joint_or_axis = axis;
  ji.incr          = stepSize;
  ji.vel           = speed;
  ji.jjogmode      = 0;
  sendCommand(ji);
  }


void CommandWriter::jogStart(int axis, double speed) {
  EMC_JOG_CONT jc;

  jc.joint_or_axis = axis;
  jc.vel           = speed;
  jc.jjogmode      = 0;
  sendCommand(jc);
  }


void CommandWriter::jogStop(int axis) {
  EMC_JOG_STOP js;

  js.joint_or_axis = axis;
  js.jjogmode      = 0;
  sendCommand(js);
  }


void CommandWriter::homeAxis(int jointNum) {
  EMC_JOINT_HOME jh;

  jh.joint = jointNum;
  sendCommand(jh);
  }


void CommandWriter::loadTaskPlan(const QString& gcodeFile) {
  EMC_TASK_PLAN_CLOSE pc;
  EMC_TASK_PLAN_OPEN  po;

  sendCommand(pc);
  strcpy(po.file, gcodeFile.toStdString().c_str());
  sendCommand(po);
  }


void CommandWriter::loadToolTable(const QString& toolTableFile) {
  EMC_TOOL_LOAD_TOOL_TABLE ltt;

  strcpy(ltt.file, toolTableFile.toStdString().c_str());
  sendCommand(ltt);
  }


void CommandWriter::sendMDICommand(const QString& command) {
  EMC_TASK_PLAN_EXECUTE pe;

  strcpy(pe.command, command.toStdString().c_str());
  sendCommand(pe);
  }


#define LOCAL_AUTO_RUN      (0)
#define LOCAL_AUTO_PAUSE    (1)
#define LOCAL_AUTO_RESUME   (2)
#define LOCAL_AUTO_STEP     (3)
#define LOCAL_AUTO_REVERSE  (4)
#define LOCAL_AUTO_FORWARD  (5)

void CommandWriter::setAuto(int autoMode, int line) {
  int rv = 0;

  switch (autoMode) {
    case 0: {
         EMC_TASK_PLAN_RUN pr;

         pr.line = line;
//         fprintf(stderr, "cmdWriter.setAuto(run) - line: %d\n", line);
         rv = sendCommand(pr);
         } break;
    case 1: {
         EMC_TASK_PLAN_PAUSE pp;

//         fputs("cmdWriter.setAuto(pause)\n", stderr);
         rv = sendCommand(pp);
         } break;
    case 2: {
         EMC_TASK_PLAN_RESUME pr;

//         fputs("cmdWriter.setAuto(resume)\n", stderr);
         rv = sendCommand(pr);
         } break;
    case 3: {
         EMC_TASK_PLAN_STEP ps;

//         fputs("cmdWriter.setAuto(step)\n", stderr);
         rv = sendCommand(ps);
         } break;
    case 4: {
         EMC_TASK_PLAN_REVERSE pr;

//         fputs("cmdWriter.setAuto(reverse)\n", stderr);
         rv = sendCommand(pr);
         } break;
    case 5: {
         EMC_TASK_PLAN_FORWARD pf;

//         fputs("cmdWriter.setAuto(forward)\n", stderr);
         rv = sendCommand(pf);
         } break;
    }
//  if (rv) fputs("changing interpreters auto mode FAILED!", stderr);
  }


void CommandWriter::enableBlockDelete(bool enable) {
  EMC_TASK_PLAN_SET_BLOCK_DELETE bd;

  if (enable) bd.state = 1;
  else        bd.state = 0;
  sendCommand(bd);
  }


void CommandWriter::setFeedOverride(double rate) {
  EMC_TRAJ_SET_SCALE ss;

  ss.scale = rate;
  sendCommand(ss);
  }


void CommandWriter::enableFlood(bool enable) {
  if (enable) {
     EMC_COOLANT_FLOOD_ON fo;

     sendCommand(fo);
     }
  else {
     EMC_COOLANT_FLOOD_OFF fo;

     sendCommand(fo);
     }
  }


void CommandWriter::enableMist(bool enable) {
  if (enable) {
     EMC_COOLANT_MIST_ON mo;

     sendCommand(mo);
     }
  else {
     EMC_COOLANT_MIST_OFF mo;

     sendCommand(mo);
     }
  }


void CommandWriter::enableOptionalStop(bool enable) {
  EMC_TASK_PLAN_SET_OPTIONAL_STOP os;

  os.state = enable;
  sendCommand(os);
  }


void CommandWriter::setRapidOverride(double rate) {
  EMC_TRAJ_SET_RAPID_SCALE rs;

  rs.scale = rate;
  sendCommand(rs);
  }


void CommandWriter::setSpindle(bool enable, int speed, int direction) {
  if (enable) {
     EMC_SPINDLE_ON so;

     so.speed = direction * speed;
     so.spindle = 0;
     sendCommand(so);
     }
  else {
     EMC_SPINDLE_OFF so;

     so.spindle = 0;
     sendCommand(so);
     }
  }


void CommandWriter::enableSpindleOverride(double rate) {
  EMC_TRAJ_SET_SPINDLE_SCALE ss;

  ss.spindle = 0;
  ss.scale = rate;
  sendCommand(ss);
  }


void CommandWriter::setTaskMode(int mode) {
  EMC_TASK_SET_MODE sm;

  sm.mode = (EMC_TASK_MODE_ENUM)mode;
  sendCommand(sm);
  }


void CommandWriter::setTaskState(int state) {
  EMC_TASK_SET_STATE ss;

  ss.state = (EMC_TASK_STATE_ENUM)state;
  sendCommand(ss);
  }


void CommandWriter::abortTask() {
  EMC_TASK_ABORT ta;

  sendCommand(ta);
  }


const int    CommandWriter::EMC_COMMAND_TIMEOUT = 5.0;  // how long to wait until timeout
const double CommandWriter::EMC_COMMAND_DELAY   = 0.01; // seconds to sleep between checks
