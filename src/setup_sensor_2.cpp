#include "config.h"   // for initConfig()
#include "comms.h"    // for initComms()
#include "logic.h"    // for initLogic() if needed
#include <Arduino.h>


void setup_sensor_2() {
  Serial.println("Sensor board setup");
  initConfig(SENSOR_2);
  initComms(SENSOR_2);
  initLogic();
}
