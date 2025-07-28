#pragma once
#include "packet.h"
#include <Arduino.h>

void initComms(uint8_t nodeID);
bool sendPacket(const uint8_t *mac, const RoverPacket &pkt);
void onPacketReceived(const uint8_t *mac, const RoverPacket &pkt);

// New additions for serial command handling:
void serialCommandLoop();
bool isEmergencyStopped();
void resetEmergencyStop();
