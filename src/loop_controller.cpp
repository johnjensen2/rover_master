#include "logic.h"
#include "packet.h"
#include "comms.h"
#include "pins.h"
#include <Arduino.h>
#include "joystick_calibration.h"

// Variables to detect tap vs hold
unsigned long joy1PressTime = 0;
unsigned long joy2PressTime = 0;
bool joy1Held = false;
bool joy2Held = false;

bool dualSteeringMode = false;
bool dualThrottleMode = false;
bool screenControlMode = false;

// Define press thresholds
const unsigned long SHORT_PRESS_DURATION = 200;  // ms
const unsigned long LONG_PRESS_DURATION = 2000;
const unsigned long SCREEN_MODE_DURATION = 5000;

void loop_controller(uint8_t thisNodeID) {
  Pins pins = getPinsForNode(thisNodeID);

int raw1X = analogRead(pins.JOY1_X_PIN);
int raw1Y = analogRead(pins.JOY1_Y_PIN);
int raw2X = analogRead(pins.JOY2_X_PIN);
int raw2Y = analogRead(pins.JOY2_Y_PIN);

int joy1X = applyCalibration(raw1X, joy1.centerX, joy1.minX, joy1.maxX);
int joy1Y = applyCalibration(raw1Y, joy1.centerY, joy1.minY, joy1.maxY);
int joy2X = applyCalibration(raw2X, joy2.centerX, joy2.minX, joy2.maxX);
int joy2Y = applyCalibration(raw2Y, joy2.centerY, joy2.minY, joy2.maxY);


  bool joy1Pressed = digitalRead(pins.JOY1_BTN_PIN) == LOW;
  bool joy2Pressed = digitalRead(pins.JOY2_BTN_PIN) == LOW;

  unsigned long now = millis();

  // Handle Left Stick (JOY1) Button
  if (joy1Pressed && joy1PressTime == 0) {
    joy1PressTime = now;
  } else if (!joy1Pressed && joy1PressTime > 0) {
    unsigned long pressDuration = now - joy1PressTime;
    joy1PressTime = 0;

    if (pressDuration < SHORT_PRESS_DURATION) {
      Serial.println("[JOY1] Quick tap → center front axle");
      RoverPacket pkt;
      pkt.senderID = thisNodeID;
      pkt.targetID = ROVER_MAIN;
      pkt.msgType = PACKET_TYPE_CONTROL;
      pkt.msgSubtype = 1; // e.g. FRONT_CENTER
      pkt.data1 = 0;       // could be angle/command
      sendPacketToNode(ROVER_MAIN, pkt);
    }
  }

  // Handle Right Stick (JOY2) Button
  if (joy2Pressed && joy2PressTime == 0) {
    joy2PressTime = now;
  } else if (!joy2Pressed && joy2PressTime > 0) {
    unsigned long pressDuration = now - joy2PressTime;
    joy2PressTime = 0;

    if (pressDuration < SHORT_PRESS_DURATION) {
      Serial.println("[JOY2] Quick tap → center rear axle");
      RoverPacket pkt;
      pkt.senderID = thisNodeID;
      pkt.targetID = ROVER_MAIN;
      pkt.msgType = PACKET_TYPE_CONTROL;
      pkt.msgSubtype = 2; // e.g. REAR_CENTER
      pkt.data1 = 0;
      sendPacketToNode(ROVER_MAIN, pkt);
    }
  }

  // (You still have the long press logic for mode switching here)

  // Normal control packet
  RoverPacket pkt;
  pkt.senderID = thisNodeID;
  pkt.targetID = ROVER_MAIN;
  pkt.msgType = PACKET_TYPE_CONTROL;
  pkt.msgSubtype = 0x00;
  pkt.data1 = joy1X;
  pkt.data2 = joy1Y;
  pkt.data3 = joy2X;  // Can encode both X/Y into one or expand the struct if needed
  pkt.type = (dualSteeringMode << 1) | dualThrottleMode;
  sendPacketToNode(ROVER_MAIN, pkt);
}
