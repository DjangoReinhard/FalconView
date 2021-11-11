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


const int    CommandWriter::EMC_COMMAND_TIMEOUT = 5.0;  // how long to wait until timeout
const double CommandWriter::EMC_COMMAND_DELAY   = 0.01; // seconds to sleep between checks
