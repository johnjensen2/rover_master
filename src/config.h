#pragma once
#include <Arduino.h>  // <-- This defines uint8_t and other Arduino types
#include <stdint.h>

uint8_t loadNodeID();
void saveNodeID(uint8_t id);

void initConfig(uint8_t nodeID);
void saveCalibration();
void resetCalibration();
void setCalibrationX(float x);
// Repeat for Y, Z as needed
