#include <Arduino.h>
#include "packet.h"
#include "comms.h"
#include "config.h"
#include "logic.h"
#include "secrets.h"
#include "wifi.h"
#include "ota.h"
#include <WiFi.h>
#include "led.h"
#include "pins.h"
#include "setup_sensor_1.h"
#include "setup_sensor_2.h"
#include "setup_rover_main.h"
#include "setup_controller.h"
#include "setup_oem.h"

#include "loop_sensor_1.h"
#include "loop_sensor_2.h"
#include "loop_rover_main.h"
#include "loop_controller.h"
#include "loop_oem.h"

uint8_t THIS_NODE_ID;

void setup() {
  Serial.begin(115200);
  delay(100);

  THIS_NODE_ID = loadNodeID();

  // If not a known node type, fall back to OEM
  if (THIS_NODE_ID < SENSOR_1 || THIS_NODE_ID > CONTROLLER) {
    THIS_NODE_ID = OEM;
  }
  Pins pins = getPinsForNode(THIS_NODE_ID);
 // Set THIS_NODE_ID according to board (or pass in build flags)
 // Identify this board's logical role by build flag
  #if defined(BOARD_SENSOR)
    THIS_NODE_ID = SENSOR_1;
  #elif defined(BOARD_ROVER_MAIN)
    THIS_NODE_ID = SENSOR_2;
  #elif defined(BOARD_ROVER_MAIN)
    THIS_NODE_ID = ROVER_MAIN;
  #elif defined(BOARD_CONTROLLER)
    THIS_NODE_ID = CONTROLLER;
  #else
    THIS_NODE_ID = OEM;
  #endif

  initLED(THIS_NODE_ID);  // Show color based on node ID

  initConfig(THIS_NODE_ID);   // Load calibration data from flash
  initComms(THIS_NODE_ID);    // Setup ESP-NOW
  initLogic();                // Setup sensors or control

  char hostname[20];
  snprintf(hostname, sizeof(hostname), "rover-node-%u", THIS_NODE_ID);
  initOTA(hostname);
  
  connectToWiFi(hostname);   // <--- connect WiFi using secrets.h
  if (WiFi.status() == WL_CONNECTED) {
    initOTA(hostname);
  }

// Call the matching setup
switch(THIS_NODE_ID) {
    case SENSOR_1: setup_sensor_1(); break;
    case SENSOR_2: setup_sensor_2(); break;
    case ROVER_MAIN: setup_main(); break;
    case CONTROLLER: setup_controller(); break;
    case OEM: setup_oem(); break;
    default: setup_oem(); break;
  }

  Serial.println("System Ready.");


}

void loop() {
  serialCommandLoop();

  if (isEmergencyStopped()) {
    // skip or override normal logic
  } else {
   
    switch(THIS_NODE_ID) {
    case SENSOR_1: loop_sensor_1(); break;
    case SENSOR_2: loop_sensor_2(); break;
    case ROVER_MAIN: loop_rover_main(); break;
    case CONTROLLER: loop_controller(); break;
    case OEM: loop_oem(); break;
    default: loop_oem(); break;
    }
  handleLogic();  // Main behavior loop
  }

  handleOTA();
  delay(10);
}
