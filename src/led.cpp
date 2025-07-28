#include "led.h"
#include <Adafruit_NeoPixel.h>

#define LED_PIN    48
#define LED_COUNT  1

Adafruit_NeoPixel pixel(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
uint32_t nodeColor = 0;

void initLED(uint8_t nodeID) {
  pixel.begin();
  pixel.setBrightness(16);

  switch (nodeID) {
    case 1: nodeColor = pixel.Color(0, 0, 255); break;          // Blue
    case 2: nodeColor = pixel.Color(128, 0, 128); break;        // Purple
    case 3: nodeColor = pixel.Color(255, 0, 0); break;          // Red
    case 4: nodeColor = pixel.Color(0, 255, 0); break;          // Green
    case 5: nodeColor = pixel.Color(255, 255, 0); break;        // Yellow
    case 6: nodeColor = pixel.Color(255, 255, 255); break;      // White
    default: nodeColor = pixel.Color(255, 128, 0); break;       // Orange
  }

  pixel.setPixelColor(0, nodeColor);
  pixel.show();
}

void ledOff() {
  pixel.setPixelColor(0, 0);
  pixel.show();
}

// 🔁 Call in loop if using blinking pattern
void setStatusLED(StatusCode code) {
  static unsigned long lastBlink = 0;
  static bool ledOn = false;

  unsigned long now = millis();
  uint16_t interval = 500;

  switch (code) {
    case STATUS_OK:
      pixel.setPixelColor(0, nodeColor);  // Steady color
      pixel.show();
      return;

    case STATUS_WAITING:
      interval = 1000;
      break;

    case STATUS_ERROR:
      interval = 250;
      break;

    case STATUS_COMM_LOST:
      interval = 150;
      break;

    case STATUS_CONFIG_MISSING:
      interval = 100;
      break;
  }

  if (now - lastBlink >= interval) {
    lastBlink = now;
    ledOn = !ledOn;
    pixel.setPixelColor(0, ledOn ? pixel.Color(255, 0, 0) : 0);  // Red blink
    pixel.show();
  }
}
