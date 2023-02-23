#include <stdint.h>
#include <telemetry.h>
#include <SPI.h>
#include <states.h>



State_t previousState;


int GetStateInt(State_t s) {
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
            return -1;
            break;
    }

    return -1;
}

void setLaunchsondeState(State_t s) {
    previousState = (State_t) data.state;
    data.state = s;                         //send state to groundstation
    // TODO: switch-case with the state and set LED color based off state (See RGBDiagnostics enum)
}