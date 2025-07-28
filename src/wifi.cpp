#include "wifi.h"
#include <WiFi.h>
#include "secrets.h"

void connectToWiFi(const char* hostname) {
  WiFi.mode(WIFI_STA);
  WiFi.setHostname(hostname);
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);

  Serial.print("Connecting to WiFi");
  unsigned long start = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - start < 10000) {
    delay(250);
    Serial.print(".");
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi connected!");
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nWiFi failed — continuing without OTA");
    WiFi.disconnect(true);  // go offline cleanly
  }
}
