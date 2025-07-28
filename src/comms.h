#pragma once
#include "packet.h"

void initComms(uint8_t nodeID);
bool sendPacket(const uint8_t *mac, const RoverPacket &pkt);
void onPacketReceived(const uint8_t *mac, const RoverPacket &pkt);
