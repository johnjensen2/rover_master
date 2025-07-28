#include "config.h"
#include "comms.h"
#include "logic.h"
#include <Arduino.h>

void setup_oem() {
  Serial.println("OEM default setup - unassigned role");
  // Could start minimal services or wait for role assignment command via comms
  initConfig(OEM);
  initComms(OEM);
  // maybe skip initLogic, or do generic logic
}
