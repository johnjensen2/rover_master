#include "logic.h"
#include "config.h"

void initLogic() {
  // Initialize sensors, motors, etc.
}

void handleLogic() {
  // Main loop work (e.g. read sensors, send packet)
}

void handleIncomingPacket(const RoverPacket &pkt) {
  if (pkt.msgType == MSG_COMMAND) {
    switch (pkt.msgSubtype) {
      case CMD_CALIBRATE_X:
        setCalibrationX(pkt.data1);
        break;
      case CMD_SAVE_CONFIG:
        saveCalibration();
        break;
      case CMD_RESET_DEFAULT:
        resetCalibration();
        break;
    }
  }
}
