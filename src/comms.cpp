#include <esp_now.h>
#include <WiFi.h>
#include "comms.h"
#include "logic.h"  // for dispatch
#include <Arduino.h>

static uint8_t thisNodeID;

static bool emergencyStop = false;


bool isEmergencyStopped() {
  return emergencyStop;
}

void resetEmergencyStop() {
  emergencyStop = false;
}


void initComms(uint8_t nodeID) {
  thisNodeID = nodeID;

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  if (esp_now_init() != ESP_OK) {
    Serial.println("ESP-NOW init failed!");
    return;
  }

  esp_now_register_recv_cb([](const uint8_t *mac, const uint8_t *data, int len) {
    if (len == sizeof(RoverPacket)) {
      RoverPacket pkt;
      memcpy(&pkt, data, sizeof(RoverPacket));
      onPacketReceived(mac, pkt);
    }
  });
}

bool sendPacket(const uint8_t *mac, const RoverPacket &pkt) {
  return esp_now_send(mac, (uint8_t *)&pkt, sizeof(pkt)) == ESP_OK;
}

void onPacketReceived(const uint8_t *mac, const RoverPacket &pkt) {
  // Allow override from D1 Mini or broadcast
  if (pkt.targetID != thisNodeID && pkt.targetID != BROADCAST && pkt.senderID != D1_OVERRIDE)
    return;

  handleIncomingPacket(pkt);
}

void processSerialCommand(const String& cmd) {
  if (cmd == "E_STOP") {
    emergencyStop = true;
    Serial.println("Emergency Stop Activated!");
    // TODO: Add your stop logic here — e.g. disable motors, halt actuators, etc.
  }
  else if (cmd.startsWith("RESET_ESTOP")) {
    emergencyStop = false;
    Serial.println("Emergency Stop Reset.");
    // TODO: Resume normal operation
  }
  else if (cmd.startsWith("CALIBRATE")) {
    // parse calibration params from cmd and apply
    Serial.println("Calibration command received.");
  }
  else if (cmd.startsWith("MODE ")) {
    // parse mode number and switch operation mode
    Serial.println("Mode switch command received.");
  }
  else {
    Serial.print("Unknown command: ");
    Serial.println(cmd);
  }
}

void serialCommandLoop() {
  static String inputLine = "";
  while (Serial.available()) {
    char c = Serial.read();
    if (c == '\n' || c == '\r') {
      if (inputLine.length() > 0) {
        processSerialCommand(inputLine);
        inputLine = "";
      }
    } else {
      inputLine += c;
    }
  }
}