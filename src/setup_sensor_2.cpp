#include <Arduino.h>
#include "pins.h"
#include "config.h"
#include "comms.h"
#include "logic.h"

void setup_pims_sensor_2() {
  Serial.println("Sensor 2 pin setup");

  Pins pins = getPinsForNode(SENSOR_2);

  pinMode(pins.US1_TRIG, OUTPUT);
  pinMode(pins.US1_ECHO, INPUT);

  pinMode(pins.US2_TRIG, OUTPUT);
  pinMode(pins.US2_ECHO, INPUT);

  pinMode(pins.US3_TRIG, OUTPUT);
  pinMode(pins.US3_ECHO, INPUT);

  pinMode(pins.LED1, OUTPUT);
  pinMode(pins.LED2, OUTPUT);

  Serial.println("Sensor 2 pins initialized");
}

void setup_sensor_2() {
  setup_pims_sensor_2();

  Serial.println("Sensor 2 board setup");

  initConfig(SENSOR_2);
  initComms(SENSOR_2);
  initLogic();

  Serial.println("Sensor 2 setup complete");
}
