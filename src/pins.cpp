#include "pins.h"
#include <Preferences.h>

static Preferences prefs;

// Provide fallback/default pins for each node type
Pins getDefaultPins(uint8_t nodeID) {
  Pins p = {};  // Zero-init struct

  switch (nodeID) {
    case OEM:
      p.TEMP_SENSOR_PIN = 5;
      p.LED_STATUS = 46;
      break;

    case SENSOR_1:
    case SENSOR_2:
      p.SENSOR_I2C_SDA = 45;
      p.SENSOR_I2C_SCL = 46;
      p.US1_TRIG = 1;  p.US1_ECHO = 2;
      p.US2_TRIG = 3;  p.US2_ECHO = 4;
      p.US3_TRIG = 5;  p.US3_ECHO = 6;
      p.LED1 = 7;
      p.LED2 = 10;
      break;

    case ROVER_MAIN:
      p.GPS_RX = 17; p.GPS_TX = 18;
      p.I2C_SDA = 35; p.I2C_SCL = 36;
      p.SERVO_FRONT = 3; p.SERVO_REAR = 4;
      p.MOTOR1_RPWM = 33; p.MOTOR1_LPWM = 35;
      p.ENCODER1_A = 39; p.ENCODER1_B = 40;
      p.MOTOR1_R_IS = 20; p.MOTOR1_L_IS = 21;
      p.MOTOR2_RPWM = 1; p.MOTOR2_LPWM = 2;
      p.ENCODER2_A = 41; p.ENCODER2_B = 42;
      p.MOTOR2_R_IS = 19; p.MOTOR2_L_IS = 38;
      p.LORA_CS = 5; p.LORA_SCK = 12; p.LORA_MISO = 13;
      p.LORA_MOSI = 14; p.LORA_RST = 15; p.LORA_IRQ = 16;
      p.CAN_TX = 10; p.CAN_RX = 11;
      p.D1_OVERRIDE_RX = 43; p.D1_OVERRIDE_TX = 44;
      break;

    case CONTROLLER:
      p.JOY1_X_PIN = 34; p.JOY1_Y_PIN = 35;
      p.JOY2_X_PIN = 32; p.JOY2_Y_PIN = 33;
      p.JOY1_BTN_PIN = 36;  // Button for joystick 1
      p.JOY2_BTN_PIN = 37;  // Button for joystick 2
      break;

    default:
      p.LED_STATUS = 46;
      break;
  }

  return p;
}

// Attempt to load any user-overridden pins from NVS
Pins getPinsForNode(uint8_t nodeID) {
  Pins p = getDefaultPins(nodeID);

  prefs.begin("pins", true);  // read-only
  char key[20];

  uint16_t* fields = reinterpret_cast<uint16_t*>(&p);
  const size_t count = sizeof(Pins) / sizeof(uint16_t);

  for (size_t i = 0; i < count; ++i) {
    snprintf(key, sizeof(key), "%u_%02u", nodeID, (uint8_t)i);
    if (prefs.isKey(key)) {
      fields[i] = prefs.getUShort(key, fields[i]);
    }
  }

  prefs.end();
  return p;
}

// Optional: save one pin override
void overridePin(uint8_t nodeID, uint8_t index, uint16_t value) {
  prefs.begin("pins", false);
  char key[20];
  snprintf(key, sizeof(key), "%u_%02u", nodeID, index);
  prefs.putUShort(key, value);
  prefs.end();
}
