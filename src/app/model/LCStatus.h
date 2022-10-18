#ifndef LCSTATUS_H
#define LCSTATUS_H
class EMC_STAT;
class EmcPose;


struct LCStatus
{
public:
  volatile char      afEnabled;
  volatile char      atmReady;
  volatile char      eStop;
  volatile char      execState;
  volatile char      flood;
  volatile char      interpState;
  volatile char      j0Enabled;
  volatile char      j0Homed;
  volatile char      j1Enabled;
  volatile char      j1Homed;
  volatile char      j2Enabled;
  volatile char      j2Homed;
  volatile char      j3Enabled;
  volatile char      j3Homed;
  volatile char      j4Enabled;
  volatile char      j4Homed;
  volatile char      j5Enabled;
  volatile char      j5Homed;
  volatile char      j6Enabled;
  volatile char      j6Homed;
  volatile char      j7Enabled;
  volatile char      j7Homed;
  volatile char      j8Enabled;
  volatile char      j8Homed;
  volatile char      mist;
  volatile char      ovrEnabled;
  volatile char      progUnits;
  volatile char      sp0Dir;
  volatile char      sp0Enabled;
  volatile char      sp0FOEnabled;
  volatile char      sp0Homed;
  volatile char      sp0Increasing;
  volatile char      sp0OvrEnabled;
  volatile char      taskFile[255];
  volatile char      taskMode;
  volatile char      taskState;
  volatile char      toolInSpindle;
  volatile int       axisMask;
  volatile long      motionLine;
  volatile double    actVelocity;
  volatile double    feedScale;
  volatile double    maxVelocity;
  volatile double    nomVelocity;
  volatile double    rapidScale;
  volatile double    scaledMaxVel;
  volatile double    sp0ActSpeed;
  volatile double    sp0NomSpeed;
  volatile double    sp0Scale;
  volatile double    xyRotation;
  volatile double    G5xOffset[9];
  volatile double    G92Offset[9];
  volatile double    dtg[9];
  volatile double    toolOffset[9];
  volatile double    trajActPos[9];
  volatile double    trajPosition[9];
  volatile int       activeGCodes[17];
  volatile int       activeMCodes[10];

  explicit  LCStatus(const EMC_STAT* status = nullptr);
  LCStatus& operator=(const EMC_STAT* status);

private:
  void copyPose(double* dst, const EmcPose& src);
  };
#endif // LCSTATUS_H
