// pins.h
#pragma once
#include <Arduino.h>
#include <stdint.h>
#include "packet.h"  // for node ID enums like OEM, SENSOR_1, etc.

constexpr int8_t UNUSED_PIN = -1;

struct Pins {
  // Common
  int LED_STATUS = -1;

  // OEM

  int TEMP_SENSOR_PIN = -1;

  // Sensors
  int SENSOR_I2C_SDA = -1;
  int SENSOR_I2C_SCL = -1;

  int US1_TRIG = -1;
  int US1_ECHO = -1;
  int US2_TRIG = -1;
  int US2_ECHO = -1;
  int US3_TRIG = -1;
  int US3_ECHO = -1;

  int LED1 = -1;
  int LED2 = -1;

  // Rover Main
  int GPS_RX = -1;
  int GPS_TX = -1;

  int I2C_SDA = -1;
  int I2C_SCL = -1;

  int SERVO_FRONT = -1;
  int SERVO_REAR  = -1;

  int MOTOR1_RPWM = -1;
  int MOTOR1_LPWM = -1;
  int ENCODER1_A  = -1;
  int ENCODER1_B  = -1;
  int MOTOR1_R_IS = -1;
  int MOTOR1_L_IS = -1;

  int MOTOR2_RPWM = -1;
  int MOTOR2_LPWM = -1;
  int ENCODER2_A  = -1;
  int ENCODER2_B  = -1;
  int MOTOR2_R_IS = -1;
  int MOTOR2_L_IS = -1;

  int LORA_CS   = -1;
  int LORA_SCK  = -1;
  int LORA_MISO = -1;
  int LORA_MOSI = -1;
  int LORA_RST  = -1;
  int LORA_IRQ  = -1;

  int CAN_TX = -1;
  int CAN_RX = -1;

  int D1_OVERRIDE_RX = -1;
  int D1_OVERRIDE_TX = -1;

  // Controller
  int JOY1_X_PIN = -1;
  int JOY1_Y_PIN = -1;
  int JOY2_X_PIN = -1;
  int JOY2_Y_PIN = -1;
  int JOY1_BTN_PIN = -1;
  int JOY2_BTN_PIN = -1;
  
  bool loadedFromFlash = false;  // Optional debug flag
};

// Pin access functions
Pins getDefaultPins(uint8_t nodeID);
Pins getPinsForNode(uint8_t nodeID);
void overridePin(uint8_t nodeID, const String &pinName, int value);