#include <Arduino.h>
#include "pins.h"
#include "config.h"
#include "comms.h"
#include "logic.h"

void setup_pims_rover_main() {
  Serial.println("Rover Main pin setup");

  Pins pins = getPinsForNode(ROVER_MAIN);

  // GPS Serial2 Pins (no pinMode needed, hardware serial)

  // I2C Pins (usually managed by Wire library, but you can set here if needed)
  pinMode(pins.I2C_SDA, INPUT_PULLUP);
  pinMode(pins.I2C_SCL, INPUT_PULLUP);

  // Steering Servos PWM pins
  pinMode(pins.SERVO_FRONT, OUTPUT);
  pinMode(pins.SERVO_REAR, OUTPUT);

  // Motor 1 PWM pins
  pinMode(pins.MOTOR1_RPWM, OUTPUT);
  pinMode(pins.MOTOR1_LPWM, OUTPUT);

  // Motor 1 Encoder pins
  pinMode(pins.ENCODER1_A, INPUT);
  pinMode(pins.ENCODER1_B, INPUT);

  // Motor 1 Current sense pins
  pinMode(pins.MOTOR1_R_IS, INPUT);
  pinMode(pins.MOTOR1_L_IS, INPUT);

  // Motor 2 PWM pins
  pinMode(pins.MOTOR2_RPWM, OUTPUT);
  pinMode(pins.MOTOR2_LPWM, OUTPUT);

  // Motor 2 Encoder pins
  pinMode(pins.ENCODER2_A, INPUT);
  pinMode(pins.ENCODER2_B, INPUT);

  // Motor 2 Current sense pins
  pinMode(pins.MOTOR2_R_IS, INPUT);
  pinMode(pins.MOTOR2_L_IS, INPUT);

  // LoRa SPI Pins
  pinMode(pins.LORA_CS, OUTPUT);
  pinMode(pins.LORA_RST, OUTPUT);
  // SPI pins (SCK, MISO, MOSI) are controlled by SPI peripheral, no pinMode needed usually

  // CAN bus pins
  pinMode(pins.CAN_TX, OUTPUT);
  pinMode(pins.CAN_RX, INPUT);

  // D1 Mini Override UART pins (usually hardware serial, pinMode optional)
  pinMode(pins.D1_OVERRIDE_RX, INPUT);
  pinMode(pins.D1_OVERRIDE_TX, OUTPUT);

  Serial.println("Rover Main pins initialized");
}

void setup_main() {
  setup_pims_rover_main();

  Serial.println("Rover Main board setup");

  initConfig(ROVER_MAIN);
  initComms(ROVER_MAIN);
  initLogic();

  Serial.println("Rover Main setup complete");
}
