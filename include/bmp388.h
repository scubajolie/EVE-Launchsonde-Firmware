#ifndef EVE_BMP388_H
#define EVE_BMP388_H

#include <Adafruit_BMP3XX.h>

// Polls 10 samples and verifies they are within a failzone of +/- 1m
bool calibrateInitialPressure();

// initializes the BMP388 (pressure sensor)
int initBMP388();

// polls 1 sample and stores the result into telemetry data structure
// records baroTemp, pressure, and altitude. 
void pollBMP388();

#endif
