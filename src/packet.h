#pragma once

#include <Arduino.h>

enum NodeID {
  SENSOR_1 = 1,
  SENSOR_2 = 2,
  ROVER_MAIN  = 3,
  CONTROLLER = 4,  
  SCREEN = 5,
  D1_OVERRIDE = 6,  // <-- Add this line
  OEM = 99,  // new default/unknown mode
  BROADCAST= 255
  };


enum MsgType {
  MSG_STATUS      = 0,
  MSG_SENSOR_DATA = 1,
  MSG_COMMAND     = 2,
  MSG_CONFIG      = 3,
  MSG_LOG         = 4,
  MSG_ACK         = 5
};

enum CommandSubtype {
  CMD_CALIBRATE_X   = 1,
  CMD_CALIBRATE_Y   = 2,
  CMD_CALIBRATE_Z   = 3,
  CMD_SAVE_CONFIG   = 10,
  CMD_RESET_DEFAULT = 11
};

typedef struct __attribute__((packed)) {
  uint8_t senderID;
  uint8_t targetID;
  uint8_t msgType;
  uint8_t msgSubtype;
  uint32_t timestamp;
  float data1;
  float data2;
  float data3;
  uint8_t flags;
} RoverPacket;
