#include <linecodes.h>
#include <string.h>


LineCodes::LineCodes() {
  reset();
}


void LineCodes::reset() {
  memset(settings, 0, sizeof(double) * ACTIVE_SETTINGS);
  memset(gCodes, 0, sizeof(int) * ACTIVE_G_CODES);
  memset(mCodes, 0, sizeof(int) * ACTIVE_M_CODES);
  }

