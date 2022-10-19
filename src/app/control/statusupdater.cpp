#include <statusupdater.h>
#include <LCStatus.h>
#include <positioncalculator.h>
#include <gcodeinfo.h>
#include <emc.hh>
#include <canon.hh>
#include <QDebug>


StatusUpdater::StatusUpdater(PositionCalculator& posCalc, GCodeInfo& gcodeInfo, QObject *parent)
 : QObject(parent)
 , pc(posCalc)
 , gi(gcodeInfo) {
  createModels();
  }


void StatusUpdater::createModels() {
//  qDebug() << "\tSR::createModels() ... START";

  vm.setValue("errorActive", false);
  vm.setValue("showAllButCenter", true);
  vm.setValue("singleStep", false);
  vm.setValue("taskMode",     -1);
  vm.setValue("taskState",    -1);
  vm.setValue("execState",    -1);
  vm.setValue("interpState",  -1);
  vm.setValue("axisMask",      0);
  vm.setValue("units",        -1);
  vm.setValue("feedrate",      1);
  vm.setValue("rapidrate",     1);
  vm.setValue("maxVelocity",   2);
  vm.setValue("curVelocity",   2);
  vm.setValue("spindle0Speed", 0);
  vm.setValue("spindle0Scale", 1);
  vm.setValue("spindle0Dir",   0);
  vm.setValue("spindle0Increasing",     false);
  vm.setValue("spindle0Enable",         true);
  vm.setValue("spindle0OverrideEnable", true);
  vm.setValue("pocketPrepared", 13);
  vm.setValue("toolInSpindle",  7);

  // signals:
  vm.setValue("enabledFeedOverride", true);
  vm.setValue("enabledAdaptiveFeed", true);
  vm.setValue("spindle0Homed", false);
  vm.setValue("enabledJoint0", false);
  vm.setValue("enabledJoint1", false);
  vm.setValue("enabledJoint2", false);
  vm.setValue("enabledJoint3", false);
  vm.setValue("enabledJoint4", false);
  vm.setValue("enabledJoint5", false);
  vm.setValue("enabledJoint6", false);
  vm.setValue("enabledJoint7", false);
  vm.setValue("enabledJoint8", false);
  vm.setValue("homedJoint0", false);
  vm.setValue("homedJoint1", false);
  vm.setValue("homedJoint2", false);
  vm.setValue("homedJoint3", false);
  vm.setValue("homedJoint4", false);
  vm.setValue("homedJoint5", false);
  vm.setValue("homedJoint6", false);
  vm.setValue("homedJoint7", false);
  vm.setValue("homedJoint8", false);
  vm.setValue("allHomed",  false);
  vm.setValue("coolMist",  false);
  vm.setValue("coolFlood", false);
  vm.setValue("estop",     true);

//  qDebug() << "\tSR::createModels() ... END";
  }


void StatusUpdater::update(volatile const LCStatus& status) {
  vm.setValue("taskMode",    static_cast<EMC_TASK_MODE_ENUM>(status.taskMode));
  vm.setValue("taskState",   static_cast<EMC_TASK_STATE_ENUM>(status.taskState));
  vm.setValue("execState",   static_cast<EMC_TASK_EXEC_ENUM>(status.execState));
  vm.setValue("interpState", static_cast<EMC_TASK_INTERP_ENUM>(status.interpState));

  qDebug() << "SR:   taskState:" << vm.getValue("taskState");
  qDebug() << "SR:   execState:" << vm.getValue("execState");
  qDebug() << "SR: interpState:" << vm.getValue("interpState");

  vm.setValue("axisMask", (int)status.axisMask);
  vm.setValue("units",    static_cast<CANON_UNITS>(status.progUnits));

  pc.update(status.trajPosition
          , status.trajActPos
          , status.dtg
          , static_cast<CANON_UNITS>(status.progUnits)
          , status.G5xOffset
          , status.G92Offset
          , status.xyRotation
          , status.toolOffset);

  vm.setValue("feedrate",    status.feedScale);
  vm.setValue("rapidrate",   status.rapidScale);
  vm.setValue("maxVelocity", status.maxVelocity);
  vm.setValue("cmdVelocity", status.nomVelocity);
  vm.setValue("curVelocity", status.actVelocity);
  vm.setValue("curRapid",    status.scaledMaxVel);
  vm.setValue("curSpeed",    status.sp0ActSpeed);
//  qDebug() << "feedrate: " << vm.getValue("feedrate")
//           << "\trapid rate: " << vm.getValue("rapidrate");

  gi.update(status.activeGCodes
          , status.activeMCodes
          , status.taskFile
          , status.motionLine);

  vm.setValue("spindle0Speed",          status.sp0NomSpeed);
  vm.setValue("spindle0Scale",          status.sp0Scale);
  vm.setValue("spindle0Dir",            status.sp0Dir);
  vm.setValue("spindle0Increasing",     status.sp0Increasing);
  vm.setValue("spindle0Enable",         status.sp0Enabled);
  vm.setValue("spindle0OverrideEnable", status.sp0OvrEnabled);

  vm.setValue("pocketPrepared", static_cast<bool>(status.atmReady));
  vm.setValue("toolInSpindle",  static_cast<bool>(status.toolInSpindle));
//  qDebug() << "tool #"   << vm.getValue("toolInSpindle")
//           << "\tnext #" << vm.getValue("pocketPrepared");

  // signals:
  vm.setValue("enabledFeedOverride", static_cast<bool>(status.ovrEnabled));
  vm.setValue("enabledAdaptiveFeed", static_cast<bool>(status.afEnabled));
  vm.setValue("spindle0Homed", static_cast<bool>(status.sp0Homed));
  vm.setValue("enabledJoint0", static_cast<bool>(status.j0Enabled));
  vm.setValue("enabledJoint1", static_cast<bool>(status.j1Enabled));
  vm.setValue("enabledJoint2", static_cast<bool>(status.j2Enabled));
  vm.setValue("enabledJoint3", static_cast<bool>(status.j3Enabled));
  vm.setValue("enabledJoint4", static_cast<bool>(status.j4Enabled));
  vm.setValue("enabledJoint5", static_cast<bool>(status.j5Enabled));
  vm.setValue("enabledJoint6", static_cast<bool>(status.j6Enabled));
  vm.setValue("enabledJoint7", static_cast<bool>(status.j7Enabled));
  vm.setValue("enabledJoint8", static_cast<bool>(status.j8Enabled));
  vm.setValue("homedJoint0", static_cast<bool>(status.j0Homed));
  vm.setValue("homedJoint1", static_cast<bool>(status.j1Homed));
  vm.setValue("homedJoint2", static_cast<bool>(status.j2Homed));
  vm.setValue("homedJoint3", static_cast<bool>(status.j3Homed));
  vm.setValue("homedJoint4", static_cast<bool>(status.j4Homed));
  vm.setValue("homedJoint5", static_cast<bool>(status.j5Homed));
  vm.setValue("homedJoint6", static_cast<bool>(status.j6Homed));
  vm.setValue("homedJoint7", static_cast<bool>(status.j7Homed));
  vm.setValue("homedJoint8", static_cast<bool>(status.j8Homed));
  vm.setValue("coolMist",  static_cast<bool>(status.mist));
  vm.setValue("coolFlood", static_cast<bool>(status.flood));
  vm.setValue("estop",     static_cast<bool>(status.eStop));
  }
