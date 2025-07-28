#include "config.h"   // for initConfig()
#include "comms.h"    // for initComms()
#include "logic.h"    // for initLogic() if needed
#include <Arduino.h>
#include "pins.h"


void setup_pims_sensor_1() {
  Serial.println("Sensor 1 pin setup");

  Pins pins = getPinsForNode(SENSOR_1);

  pinMode(pins.US1_TRIG, OUTPUT);
  pinMode(pins.US1_ECHO, INPUT);

  pinMode(pins.US2_TRIG, OUTPUT);
  pinMode(pins.US2_ECHO, INPUT);

  pinMode(pins.US3_TRIG, OUTPUT);
  pinMode(pins.US3_ECHO, INPUT);

  pinMode(pins.LED1, OUTPUT);
  pinMode(pins.LED2, OUTPUT);

  Serial.println("Sensor 1 pins initialized");
}

void setup_sensor_1() {
  setup_pims_sensor_1();   // Set up pins only

  Serial.println("Sensor 1 board setup");

  initConfig(SENSOR_1);
  initComms(SENSOR_1);
  initLogic();

  Serial.println("Sensor 1 setup complete");
}

