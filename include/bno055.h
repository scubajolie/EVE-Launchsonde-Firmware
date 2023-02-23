#ifndef EVE_BNO055_H
#define EVE_BNO055_H

#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

// IMU Instantiations
extern Adafruit_BNO055 bno;
extern adafruit_bno055_offsets_t offsets; //struct for the calibration offsets to be saved into memory and loaded.
extern uint8_t sysCal, gyroCal, accelCal, magCal;
extern bool calDataLoaded;

// initializes the IMU board (bno055)
// if initialization fails, it blocks further code execution
// and prints an error message to the serial port. 
// TODO: Switch error system
void initBNO055();

// calibrates and polls data
// assigns measured values to telemetry data structure
// records accel x/y/z, gyro x/y/z, roll, pitch, yaw, and linAccel x/y/z.
void pollBNO055();

#endif