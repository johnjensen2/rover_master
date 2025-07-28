#include "joystick_calibration.h"
#include <Preferences.h>

Preferences prefs;

void calibrateJoystick(const char* name, int pinX, int pinY, JoystickCalibration &calib) {
  Serial.println();
  Serial.printf("Calibrating joystick: %s\n", name);
  delay(1000);

  calib.minX = 4095;
  calib.maxX = 0;
  calib.minY = 4095;
  calib.maxY = 0;

  unsigned long startTime = millis();
  while (millis() - startTime < 5000) {  // 5-second calibration window
    int x = analogRead(pinX);
    int y = analogRead(pinY);

    calib.minX = min(calib.minX, x);
    calib.maxX = max(calib.maxX, x);
    calib.minY = min(calib.minY, y);
    calib.maxY = max(calib.maxY, y);

    delay(5);
  }

  calib.centerX = (calib.minX + calib.maxX) / 2;
  calib.centerY = (calib.minY + calib.maxY) / 2;

  Serial.printf("Center: X=%d Y=%d | Min: X=%d Y=%d | Max: X=%d Y=%d\n",
    calib.centerX, calib.centerY,
    calib.minX, calib.minY,
    calib.maxX, calib.maxY
  );

  saveCalibration(name, calib);
}

void saveCalibration(const char* name, const JoystickCalibration &calib) {
  prefs.begin(name, false);
  prefs.putInt("minX", calib.minX);
  prefs.putInt("maxX", calib.maxX);
  prefs.putInt("centerX", calib.centerX);
  prefs.putInt("minY", calib.minY);
  prefs.putInt("maxY", calib.maxY);
  prefs.putInt("centerY", calib.centerY);
  prefs.end();
}

bool loadCalibration(const char* name, JoystickCalibration &calib) {
  prefs.begin(name, true);
  calib.minX = prefs.getInt("minX", -1);
  calib.maxX = prefs.getInt("maxX", -1);
  calib.centerX = prefs.getInt("centerX", -1);
  calib.minY = prefs.getInt("minY", -1);
  calib.maxY = prefs.getInt("maxY", -1);
  calib.centerY = prefs.getInt("centerY", -1);
  prefs.end();

  // Check if calibration is valid
  return (calib.minX >= 0 && calib.maxX > calib.minX &&
          calib.minY >= 0 && calib.maxY > calib.minY &&
          calib.centerX >= calib.minX && calib.centerX <= calib.maxX &&
          calib.centerY >= calib.minY && calib.centerY <= calib.maxY);
}

int applyCalibration(int raw, int center, int minVal, int maxVal) {
  if (raw > center) {
    return map(raw, center, maxVal, 0, 127);
  } else {
    return map(raw, minVal, center, -127, 0);
  }
}
