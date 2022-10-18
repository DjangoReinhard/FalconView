#include "LCStatus.h"
#include <emc_nml.hh>
#include <string.h>


LCStatus::LCStatus(const EMC_STAT* status) {
  if (status) *this = status;
  }


LCStatus& LCStatus::operator=(const EMC_STAT* status) {
  eStop         = status->io.aux.estop;
  flood         = status->io.coolant.flood;
  mist          = status->io.coolant.mist;
  atmReady      = status->io.tool.pocketPrepped;
  toolInSpindle = status->io.tool.toolInSpindle;
  j0Enabled     = status->motion.joint[0].enabled;
  j0Homed       = status->motion.joint[0].homed ? true : false;
  j1Enabled     = status->motion.joint[1].enabled;
  j1Homed       = status->motion.joint[1].homed ? true : false;
  j2Enabled     = status->motion.joint[2].enabled;
  j2Homed       = status->motion.joint[2].homed ? true : false;
  j3Enabled     = status->motion.joint[3].enabled;
  j3Homed       = status->motion.joint[3].homed ? true : false;
  j4Enabled     = status->motion.joint[4].enabled;
  j4Homed       = status->motion.joint[4].homed ? true : false;
  j5Enabled     = status->motion.joint[5].enabled;
  j5Homed       = status->motion.joint[5].homed ? true : false;
  j6Enabled     = status->motion.joint[6].enabled;
  j6Homed       = status->motion.joint[6].homed ? true : false;
  j7Enabled     = status->motion.joint[7].enabled;
  j7Homed       = status->motion.joint[7].homed ? true : false;
  j8Enabled     = status->motion.joint[8].enabled;
  j8Homed       = status->motion.joint[8].homed ? true : false;
  sp0Dir        = status->motion.spindle[0].direction;
  sp0Enabled    = status->motion.spindle[0].enabled;
  sp0Homed      = status->motion.spindle[0].homed;
  sp0Increasing = status->motion.spindle[0].increasing;
  sp0OvrEnabled = status->motion.spindle[0].spindle_override_enabled;
  afEnabled     = status->motion.traj.adaptive_feed_enabled;
  ovrEnabled    = status->motion.traj.feed_override_enabled;
  execState     = status->task.execState;
  interpState   = status->task.interpState;
  taskMode      = status->task.mode;
  progUnits     = status->task.programUnits;
  taskState     = status->task.state;
  axisMask      = status->motion.traj.axis_mask;
  motionLine    = status->task.motionLine;
  sp0NomSpeed   = status->motion.spindle[0].speed;
  sp0ActSpeed   = status->motion.spindle[0].speed * status->motion.spindle[0].spindle_scale;
  sp0Scale      = status->motion.spindle[0].spindle_scale;
  nomVelocity   = status->motion.traj.current_vel * 60;
  actVelocity   = status->motion.traj.current_vel * 60 * status->motion.traj.scale;
  maxVelocity   = status->motion.traj.maxVelocity * 60;
  scaledMaxVel  = status->motion.traj.maxVelocity * 60 * status->motion.traj.rapid_scale;
  rapidScale    = status->motion.traj.rapid_scale;
  feedScale     = status->motion.traj.scale;
  xyRotation    = status->task.rotation_xy;
  char* tmp = const_cast<char*>(taskFile);

  strncpy(tmp, status->task.file, 255);
  double* dTmp = const_cast<double*>(dtg);

  copyPose(dTmp, status->motion.traj.dtg);
  dTmp = const_cast<double*>(trajPosition);
  copyPose(dTmp, status->motion.traj.position);
  dTmp = const_cast<double*>(trajActPos);
  copyPose(dTmp,   status->motion.traj.actualPosition);
  dTmp = const_cast<double*>(G5xOffset);
  copyPose(dTmp,    status->task.g5x_offset);
  dTmp = const_cast<double*>(G92Offset);
  copyPose(dTmp,    status->task.g92_offset);
  dTmp = const_cast<double*>(toolOffset);
  copyPose(dTmp,   status->task.toolOffset);
  int* iTmp = const_cast<int*>(activeGCodes);

  memcpy(iTmp, status->task.activeGCodes, sizeof(int) * 17);
  iTmp = const_cast<int*>(activeMCodes);
  memcpy(iTmp, status->task.activeMCodes, sizeof(int) * 10);

  return *this;
  }


void LCStatus::copyPose(double* dst, const EmcPose& src) {
  dst[0] = src.tran.x;
  dst[1] = src.tran.y;
  dst[2] = src.tran.z;
  dst[3] = src.a;
  dst[4] = src.b;
  dst[5] = src.c;
  dst[6] = src.u;
  dst[7] = src.v;
  dst[8] = src.w;
  }
