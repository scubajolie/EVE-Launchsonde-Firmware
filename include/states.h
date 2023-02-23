#ifndef EVE_STATES_H
#define EVE_STATES_H

enum State_t {
    // Nominal states
    BOOTING,                    // Package is initializing
    STANDBY,                    // Package has initialized and is calibrating sensors
    READY,                      // Package has calibrated sensors and is ready to fly
    ARMED,                      // Package is armed and ready to ignite motor
    LAUNCHING,                  // Package is preparing for launch
    FLIGHT,                     // Package is in flight
    RECOVERY,                   // Package has landed and is in recovery mode
    
    // Additional functions
    IMU_RECORDING = 10,         // Package is recording IMU calibration data and saving it

    // Error states
    GEN_ERROR = -1,             // Package has encountered an undiagnosed error
    RADIO_FAIL = -2,            // Radio has failed to initialize
    GPS_FAIL = -3,              // GPS has failed to initialize
    ALT_FAIL = -4,              // Altimeter has failed to initialize
    IMU_FAIL = -5,              // IMU has failed to initialize
    SHT_FAIL = -6,              // SHT has failed to initialize
    IGN_FAIL = -7,              // Ignitor failed to ignite motor or has lost connection
    LOW_BATT = -8,              // Battery voltage is below threshold
    FILE_SYSTEM_FAIL = -9       // File system failed to initialize properly
};


extern State_t previousState;


int GetStateInt(State_t s);


void setLaunchsondeState(State_t s);

#endif