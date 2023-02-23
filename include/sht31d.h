#ifndef EVE_SHT31D_H
#define EVE_SHT31D_H

#include <Adafruit_SHT31.h>

// initialize the temp+humidity sensor
// changes Launchsonde state to SHT_FAIL if unsuccessful
void initSHT31();

// poll temp+humidity sensor and store in telemetry data structure
// does NOT check for error***
void pollSHT31();

#endif