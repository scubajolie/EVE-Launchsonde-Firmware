/**
* PROJECT EVE
* FLORIDA INSTITUTE OF TECHNOLOGY, OEMS DEPARTMENT
* UNDERWATER TECHNOLOGY LABORATORY
* Supervising Professor: Dr. Stephen Wood, Ph.D, PE
*
* @file   Launchsonde Firmware Version 1.1
* @date   4/26/2023
* @author Braidan Duffy & Jolie Elliott
*
* Theory of Operation:
*/


#include <stdio.h>
#include <SPI.h>
#include <SD.h>
#include <modes.h>
#include <dotstar.h>
#include <commands.h>

// Communication Headers
#include <LoRa.h>
#include <radio.h>
#include <gps.h>

// Sensor Board headers
#include <pins.h>
#include <bmp388.h>
#include <bno055.h>
#include <sht31d.h>

// Telemetry Data Header
#include <telemetry.h>


// ===========================
// === PROTOTYPE FUNCTIONS ===
// ===========================
void serialError(const char * msg, int error ) {
    char Error_Message[100];
    Serial.printf( "ERROR [%d]: %s \n", error, msg );
        int msgSize = strlen(msg);
    if (msgSize>=99) {
        sprintf(Error_Message, "ERROR [%d]: Message was too long.", error);
    } else {
        sprintf(Error_Message, "ERROR [%d]: %s \n", error, msg);
    }
    sendDiagnosticData(LogLevel(ERROR), Error_Message);
}

void setup() {
	#ifdef DIAGNOSTIC
    	Serial.begin(115200);
		while(!Serial); // Wait for serial connection
	#endif

    initDotStar();

    #ifdef DIAGNOSTIC
        currentMode = DIAGNOSTIC_MODE;
        Serial.println("Launchsonde is in DIAGNOSTIC mode"); //DEBUG
        // sendDiagnosticData(WARN, "Launchsonde is in DIAGNOSTIC mode"); // Broken, needs more testing
        blinkCode(B1111, PURPLE); // Blink .-.- in PURPLE on the diagnostic RGB LED
    #endif
    if (currentMode == FLIGHT_MODE) {
        #ifdef DIAGNOSTIC
            Serial.println("Launchsonde is in FLIGHT mode"); //DEBUG
        #endif
        // sendDiagnosticData(WARN, "Launchsonde is in FLIGHT mode"); // Broken, needs more testing
        blinkCode(B1111, GREEN); // Blink .-.- in GREEN on the diagnoostic RGB LED
    }
        
    setLaunchsondeState(BOOTING); // System is on and initializing

    initRadio();
    initGPS();
    initBNO055(); // IMU
    initBMP388(); // altimeter
    initSHT31();

    setLaunchsondeState(STANDBY); // System initialized successfully and is awaiting sensor calibration
}

void loop() {
    // if (currentMode == DIAGNOSTIC_MODE) {
    //     while (Serial.available()) { // Check for commands from the Serial terminal and execute.
    //         executeCommand((Command) Serial.read(), Serial.read());
    //         Serial.flush(); // Clear Serial port of remain characters
    //     }
    // }

    // sendDiagnosticData(DEBUG, "Testing Diagnostic Data Function");
    
    // if (!isInDiagMode) { // Check if launchsonde is in FLIGHT mode
    //     if (!checkBattVoltage()) { // Check battery voltage is out of flight range (2.5-4.4 V)
    //         setLaunchsondeState(LOW_BATT);
    //         while (1) { // Blocks further code execution
    //             blinkCode(LOW_BATT_ERROR_CODE, AMBER);
    //             // sendDiagnosticData(FATAL, "Low battery voltage detected"); // Broken, needs more testing
    //             if (checkBattVoltage()) { // Check if false reading and break loop if so
    //                 setLaunchsondeState(prevState);
    //                 break;
    //             } 
    //         }
    //     }
    // }
    // else checkBattVoltage(); // If in DIAGNOSTIC mode, check the battery voltage anyways, but do not block code if its low

	// Set the NeoPixel to always be green when in FLIGHT mode
	EVEstrip.setPixelColor(0, currentMode == DIAGNOSTIC_MODE ? BLUE : GREEN);
	EVEstrip.show();

	static long unsigned int _lastSample = 0;
    static long unsigned int _lastLog = 0;
	if (millis() > _lastSample+SAMPLE_TIME) {
		_lastSample = millis();
		pollGPS();
		// pollBNO055();
		pollBMP388();
		pollSHT31();
        data.packetSize = sizeof(data);
        sendTelemetryData(); // Broken, needs more testing
	}

    // if(millis() > _lastLog+LOG_TIME) {
    //     _lastLog = millis();
    //     // msg = getLogLevelString()
    //     sendDiagnosticData(TRACE, "Everything is Normal");
    // }

    // if (data.state == STANDBY && checkSensorsReady()) { // Check if sensors are calibrated
    //     setLaunchsondeState(READY);
    // }
    // else {
    //     // Check if state has changed
    //     if (data.state != previousState) {
    //         setLaunchsondeState(previousState);
    //         //sendState( static_cast<State_t>( data.state ) );      // also works!!
    //         sendState(State_t(data.state));
    //     }
    // }

    // if (currentMode == DIAGNOSTIC_MODE) {
    //     printTelemetryData();
    //     // printBaseStationTelemetry();
    //     delay(500); // Delay between readings
    // }

}