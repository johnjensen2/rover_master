#pragma once
#include <Arduino.h>  // <-- This defines uint8_t and other Arduino types

void initConfig(uint8_t nodeID);
void saveCalibration();
void resetCalibration();
void setCalibrationX(float x);
// Repeat for Y, Z as needed
