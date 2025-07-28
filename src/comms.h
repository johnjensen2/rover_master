#pragma once
#include "packet.h"
#include <Arduino.h>

void initComms(uint8_t nodeID);
bool sendPacket(const uint8_t *mac, const RoverPacket &pkt);
void onPacketReceived(const uint8_t *mac, const RoverPacket &pkt);
bool sendPacketToNode(uint8_t targetID, const RoverPacket& pkt);
const uint8_t* getMacForNode(uint8_t nodeID);

// New additions for serial command handling:
void serialCommandLoop();
bool isEmergencyStopped();
void resetEmergencyStop();
