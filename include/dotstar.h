#ifndef EVE_DOTSTAR_H
#define EVE_DOTSTAR_H

#include <pins.h>
#include <Adafruit_DotStar.h>


#define NUM_PIXELS 1

// ======================
// ===DIAGNOSTIC CODES===
// ======================

enum RGBDiagnostics {
    LED_STANDBY_NO_RADIO,   // Solid blue
    LED_ARMED,              // Solid green
    LED_RECOVERY,           // Solid purple
    LED_LOW_BATTERY,        // Solid amber
    LED_CALIBRATING,        // Solid cyan
    LED_READY,              // Solid lime
    LED_ERROR               // Solid red
};

/*
Code Table:
Error       |  DOT  |  DASH  |  DOT  |  DASH  |  CODE  |  COLOR
------------|-------|--------|-------|--------|--------|---------
General     |   0   |   0    |   0   |    1   |  B0001 |   RED
Radio       |   0   |   0    |   1   |    0   |  B0010 |   RED
GPS         |   0   |   0    |   1   |    1   |  B0011 |   RED
Ignitor     |   0   |   1    |   0   |    0   |  B0100 |  WHITE
IMU         |   0   |   1    |   0   |    1   |  B0101 |   RED
SHT         |   0   |   1    |   1   |    0   |  B0110 |   RED
Altimeter   |   0   |   1    |   1   |    1   |  B0111 |   RED
Low Battery |   1   |   0    |   0   |    0   |  B1000 |  AMBER

A dot is 125 ms on, 125 ms off
A dash is 250 ms on, 250 ms off
Space between codes is 1 sec
*/

enum ErrorCode {
    GEN_ERROR_CODE          = B0001,
    RADIO_ERROR_CODE        = B1010,
    GPS_ERROR_CODE          = B0011,
    IGNITOR_ERROR_CODE      = B0100,
    IMU_ERROR_CODE          = B0101,
    SHT_ERROR_CODE          = B0110,
    ALTIMETER_ERROR_CODE    = B0111,
    LOW_BATT_ERROR_CODE     = B1000
};

// DotStar instantiation
#define DASH_ON 250
#define DOT_ON 125
#define BLINK_INTERVAL 125
#define MESSAGE_INTERVAL 1000

extern Adafruit_DotStar EVEstrip;
extern const uint32_t OFF;       //BGR
extern const uint32_t WHITE;
extern const uint32_t BLUE;
extern const uint32_t RED;
extern const uint32_t GREEN;
extern const uint32_t PURPLE;
extern const uint32_t AMBER;
extern const uint32_t CYAN;
extern const uint32_t LIME;


void initDotStar();

void blinkCode(byte code, uint32_t color);

#endif