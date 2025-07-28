#include <Preferences.h>
#include "packet.h"  // for NodeID enum


static Preferences prefs;

static float calX = 0.0f;

void initConfig(uint8_t nodeID) {
  prefs.begin("calib", false);
  calX = prefs.getFloat("calX", 0.0f);
}

void saveCalibration() {
  prefs.putFloat("calX", calX);
  prefs.end();
  prefs.begin("calib", false);
}

void resetCalibration() {
  calX = 0.0f;
  saveCalibration();
}

void setCalibrationX(float x) {
  calX = x;
}

uint8_t loadNodeID() {
  prefs.begin("rover", true);  // read-only
  uint8_t id = prefs.getUChar("node_id", OEM);  // default to OEM
  prefs.end();
  return id;
}

void saveNodeID(uint8_t id) {
  prefs.begin("rover", false);  // read-write
  prefs.putUChar("node_id", id);
  prefs.end();
}