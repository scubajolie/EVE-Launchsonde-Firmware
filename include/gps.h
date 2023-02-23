#ifndef EVE_GPS_H
#define EVE_GPS_H

#include <MicroNMEA.h>

void printUnknownSentence(const MicroNMEA& nmea);

void ppsHandler(void);

void initGPS();

void pollGPS();

#endif