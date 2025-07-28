#include <esp_now.h>
#include <WiFi.h>
#include "comms.h"
#include "logic.h"  // for dispatch

static uint8_t thisNodeID;

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
