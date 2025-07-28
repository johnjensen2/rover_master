#include "config.h"   // for initConfig()
#include "comms.h"    // for initComms()
#include "logic.h"    // for initLogic() if needed
#include <Arduino.h>


void setup_main() {
  Serial.println("Rover Main board setup");
  initConfig(ROVER_MAIN);
  initComms(ROVER_MAIN);
  initLogic();
}
