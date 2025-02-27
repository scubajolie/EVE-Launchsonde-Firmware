#ifndef EVE_BATTERY_H
#define EVE_BATTERY_H

#include <telemetry.h>
#include <pins.h>

#define BATT_VOLTAGE_THRESHOLD 2.5 // V

bool checkBattVoltage() {
    data.voltage = analogRead(BATT_IN_PIN) * (3.3 / 65536) * 2; //Read true voltage of battery
    return data.voltage > BATT_VOLTAGE_THRESHOLD && data.voltage < 4.4; //Check if battery is above 2.5V and below 4.3V
}

#endif