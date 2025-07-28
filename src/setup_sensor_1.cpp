#include "config.h"   // for initConfig()
#include "comms.h"    // for initComms()
#include "logic.h"    // for initLogic() if needed
#include <Arduino.h>


void setup_sensor_1() {
  Serial.println("Sensor board setup");
  initConfig(SENSOR_1);
  initComms(SENSOR_1);
  initLogic();
}
