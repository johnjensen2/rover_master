#pragma once
#include <Arduino.h>

enum StatusCode {
  STATUS_OK,
  STATUS_WAITING,
  STATUS_ERROR,
  STATUS_COMM_LOST,
  STATUS_CONFIG_MISSING
};

void initLED(uint8_t nodeID);     // Solid color by ID
void setStatusLED(StatusCode);   // Blinking pattern
void ledOff();                   // Turn off LED
