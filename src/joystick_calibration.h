#pragma once
#include <Arduino.h>

struct JoystickCalibration {
  int centerX = 2048;
  int centerY = 2048;
  int minX = 0;
  int maxX = 4095;
  int minY = 0;
  int maxY = 4095;
};

extern JoystickCalibration joy1;
extern JoystickCalibration joy2;

void calibrateJoystick(const char* name, int pinX, int pinY, JoystickCalibration &calib);
void saveCalibration(const char* name, const JoystickCalibration &calib);
bool loadCalibration(const char* name, JoystickCalibration &calib);
int applyCalibration(int raw, int center, int minVal, int maxVal);
void applyDeadzoneAndCenter(JoystickCalibration &calib, int &x, int &y);