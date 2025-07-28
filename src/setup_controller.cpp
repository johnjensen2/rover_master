#include "config.h"   // for initConfig()
#include "comms.h"    // for initComms()
#include "logic.h"    // for initLogic() if needed
#include <Arduino.h>


void setup_controller() {
  Serial.println("Controller board setup");
  initConfig(CONTROLLER);
  initComms(CONTROLLER);
  initLogic();
}
