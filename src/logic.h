#pragma once
#include "packet.h"

void initLogic();
void handleLogic();
void handleIncomingPacket(const RoverPacket &pkt);
