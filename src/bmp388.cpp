#include <Adafruit_BMP3XX.h>
#include <bmp388.h>
#include <states.h>
#include <logging.h>
#include <telemetry.h>
#include <radio.h>

// BMP388 instantiation
Adafruit_BMP3XX bmp;
float initialPressure = 1013.25; //hPa
bool isInitialPressCal = false;

bool calibrateInitialPressure() {
	int failzone = 1; //Looks for +/- 1m condition
    double total = 0;
    const uint8_t reps = 10;
    for (uint8_t i = 0; i < reps; i++) {
        bmp.performReading();
        total += bmp.pressure;
        // Serial.print("Pressure: "); Serial.println(bmp.pressure);
        delay(100); //Minimum sample interval. Default is 66
    }
    initialPressure = total / reps / 100; // hPa
    // Serial.print("Pressure: "); Serial.print(initialPressure/100); Serial.print("\t Altitude:"); Serial.println(bmp.readAltitude(initialPressure/100)); //DEBUG
    // Serial.printf("Pressure: %d, Altitude: %d ...", initialPressure, bmp.readAltitude(initialPressure));

    if (bmp.readAltitude(initialPressure) < failzone && bmp.readAltitude(initialPressure) > -failzone) { //Check if the altitude is truely zeroed
		isInitialPressCal = true;
        return true;
	}
    else {
        return false;
	}
}

int initBMP388() {
    #ifdef DIAGNOSTIC
        Serial.print("Initializing BMP388...");
    #endif
    if (!bmp.begin_I2C()) {   // hardware I2C mode
        #ifdef DIAGNOSTIC
            Serial.println("Failed to initialize BMP388!"); // DEBUG
        #endif
        setLaunchsondeState(ALT_FAIL);
        // while (1) { // Blocks further code execution
        //    blinkCode((byte) ALTIMETER_ERROR_CODE, RED);
            // sendDiagnosticData(FATAL, "Failed to initialize BMP388"); // Broken, requires further testing 
        // }
        sendDiagnosticData(LogLevel(FATAL), "FATAL ERROR: Failed to initialize the altimeter (BMP388)");
        return -1;
    }
    // Set up oversampling and filter initialization
    bmp.setTemperatureOversampling(BMP3_OVERSAMPLING_8X);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_4X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_50_HZ);
    Serial.println("done!");

    Serial.print("Calibrating initial pressure...");
    while(!calibrateInitialPressure()); //Block code execution until initial pressure is calibrated
    Serial.println("done!");
    return 0;
}

void pollBMP388() {
    if (!bmp.performReading()) {
        Serial.println("Failed to get BMP388 reading"); // DEBUG
        // sendDiagnosticData(ERROR, "Failed to get BMP388 reading"); // Broken for now, requires further testing
    }
    data.baroTemp = bmp.temperature;
    data.pressure = bmp.pressure;
    data.altitude = bmp.readAltitude(initialPressure);
}