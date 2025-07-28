#include <Preferences.h>
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
