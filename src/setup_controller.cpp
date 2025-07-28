#include <Arduino.h>
#include "pins.h"
#include "config.h"
#include "comms.h"
#include "logic.h"

void setup_pims_controller() {
  Serial.println("Controller pin setup");

  Pins pins = getPinsForNode(CONTROLLER);

  // Joystick 1
  pinMode(pins.JOY1_X_PIN, INPUT);
  pinMode(pins.JOY1_Y_PIN, INPUT);

  // Joystick 2
  pinMode(pins.JOY2_X_PIN, INPUT);
  pinMode(pins.JOY2_Y_PIN, INPUT);

  Serial.println("Controller pins initialized");
}

void setup_controller() {
  setup_pims_controller();

  Serial.println("Controller board setup");

  initConfig(CONTROLLER);
  initComms(CONTROLLER);
  initLogic();

  Serial.println("Controller setup complete");
}
