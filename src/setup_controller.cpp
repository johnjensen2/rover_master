#include <Arduino.h>
#include "pins.h"
#include "config.h"
#include "comms.h"
#include "logic.h"
#include "joystick_calibration.h"

JoystickCalibration joy1, joy2;

void setup_pims_controller() {
  Serial.println("Controller pin setup");

  Pins pins = getPinsForNode(CONTROLLER);

  // Joystick 1
  pinMode(pins.JOY1_X_PIN, INPUT);
  pinMode(pins.JOY1_Y_PIN, INPUT);

  // Joystick 2
  pinMode(pins.JOY2_X_PIN, INPUT);
  pinMode(pins.JOY2_Y_PIN, INPUT);

bool valid1 = loadCalibration("joy1", joy1);
bool valid2 = loadCalibration("joy2", joy2);

if (!valid1) {
  Serial.println("Joystick 1 not calibrated, starting calibration...");
  calibrateJoystick("joy1", pins.JOY1_X_PIN, pins.JOY1_Y_PIN, joy1);
}

if (!valid2) {
  Serial.println("Joystick 2 not calibrated, starting calibration...");
  calibrateJoystick("joy2", pins.JOY2_X_PIN, pins.JOY2_Y_PIN, joy2);
}
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
