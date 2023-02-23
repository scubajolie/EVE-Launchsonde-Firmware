#ifndef EVE_EVEHELPER_H
#define EVE_EVEHELPER_H

#define COUNTDOWN_TIME 10 // s
#define SAMPLE_TIME 50 // ms
#define LOG_TIME 500 // 1 log for every 10 samples



// Launchsonde modes helper
#include <modes.h>

// DotStar helper
#include <dotstar.h>

// Logging helper
#include <logging.h>

// Sensor helpers
#include <bmp388.h>
#include <bno055.h>
#include <sht31d.h>

// Command helper
#include <commands.h>

// Radio helpers
#include <radio.h>
#include <gps.h>

// Battery helper
#include <battery.h>

extern const PROGMEM char UUID_FILENAME[9];
extern byte UUID; // Default UUID is 0xFF to indicate no UUID is set yet
extern bool isUUIDConfig;
extern const PROGMEM byte RECEIVER_UUID; // Default receiver UUID is 0x00

void printTelemetryData();

void printBaseStationTelemetry();

#endif