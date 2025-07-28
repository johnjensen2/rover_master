#include "device_selector.h"

#if defined(BOARD_SENSOR)
  extern void setupDevice();
  extern void loopDevice();
#elif defined(BOARD_ROVER_MAIN)
  extern void setupDevice();
  extern void loopDevice();
#elif defined(BOARD_CONTROLLER)
  extern void setupDevice();
  extern void loopDevice();
#else
  #error "Board type not defined!"
#endif
