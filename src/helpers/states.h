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


State_t previousState;


static int GetStateInt(State_t s) {
    switch(s) {
        case BOOTING:
            return static_cast<int8_t>(State_t::BOOTING);
            break;
        case STANDBY:
            return static_cast<int8_t>(State_t::STANDBY);
            break;
        case READY:
            return static_cast<int8_t>(State_t::READY);
            break;
        case ARMED:
            return static_cast<int8_t>(State_t::ARMED);
            break;
        case LAUNCHING:
            return static_cast<int8_t>(State_t::LAUNCHING);
            break;
        case FLIGHT:
            return static_cast<int8_t>(State_t::FLIGHT);
            break;
        case RECOVERY:
            return static_cast<int8_t>(State_t::RECOVERY);
            break;
        case IMU_RECORDING:
            return static_cast<int8_t>(State_t::IMU_RECORDING);
            break;
        case RADIO_FAIL:
            return static_cast<int8_t>(State_t::RADIO_FAIL);
            break;
        case GPS_FAIL:
            return static_cast<int8_t>(State_t::GPS_FAIL);
            break;
        case ALT_FAIL:
            return static_cast<int8_t>(State_t::ALT_FAIL);
            break;
        case IMU_FAIL:
            return static_cast<int8_t>(State_t::IMU_FAIL);
            break;
        case SHT_FAIL:
            return static_cast<int8_t>(State_t::SHT_FAIL);
            break;
        case IGN_FAIL:
            return static_cast<int8_t>(State_t::IGN_FAIL);
            break;
        case LOW_BATT:
            return static_cast<int8_t>(State_t::LOW_BATT);
            break;
        default:
            Serial.println("Invalid State");
            break;
    }
}



static void setLaunchsondeState(State_t s) {
    previousState = (State_t) data.state;
    data.state = s;                         //send state to groundstation
    // TODO: switch-case with the state and set LED color based off state (See RGBDiagnostics enum)
}