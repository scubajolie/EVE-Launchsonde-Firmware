#ifndef EVE_COMMANDS_H
#define EVE_COMMANDS_H

#include <stdint.h>
#include <Arduino.h>

// FOR KEYBOARD COMMANDS (TESTING) SET ARM=0x30!
enum Command {
    ARM = 0x30,                        // Arm the package for launch
    DISARM,                     // Disarm the package for safety
    LAUNCH,                     // Ignite the motor and launch package
    ZERO_ALT,                   // Zero the altimeter
    CAL_IMU,                    // Load calibration data into IMU
    RECORD_IMU,                 // Record calibration data from IMU and put it into EEPROM
    SET_UUID,                   // Uses aditional argument to set the UUID of the instrumentation
    ZERO_GPS                    // Zero the GPS start point (only used on ground station)
};

// Using a switch funciton and given the Command type, 
// returns a string of the command. 
// @param: string pointer to store returned command string
// @param: Command
void getCommandString(char* outStr, Command c);

// checks if GPS has a positive fix
// checksif altimiter is in range ±1m
// checks if IMU is calibrated using isFullyCalibrated()
bool checkSensorsReady();

// if state is ARMED and checkSensorsReady returns TRUE
// then countdown, launch (currently attempts to ignite), 
// assumes flight was successful and the state is set to LAUNCH. 
void launch();

// Load offset data to BNO sensor'
// Used to calibrate IMU
void loadIMUCalData();

// execute command based on command type
// @param:Command
// @param: byte message
void executeCommand(Command cmd, byte msg);
#endif