#include <telemetry.h>
#include <SPI.h>
#include <string.h>




Telemetry data;

void printTelemetryData() {
    Serial.println("---TELEMETRY PACKET---");
    Serial.print("Battery voltage:  "); Serial.print(data.voltage);             Serial.println(" V");
    Serial.print("GPS month:        "); Serial.print(data.month);               Serial.println();
    Serial.print("GPS day:          "); Serial.print(data.day);                 Serial.println();
    Serial.print("GPS year:         "); Serial.print(data.year);                Serial.println();
    Serial.print("GPS hour:         "); Serial.print(data.hour);                Serial.println();
    Serial.print("GPS minute:       "); Serial.print(data.minute);              Serial.println();
    Serial.print("GPS second:       "); Serial.print(data.second);              Serial.println();
    Serial.print("Milliseconds:     "); Serial.print(data.msecond);             Serial.println();
    Serial.print("GPS fix:          "); Serial.print(data.GPSFix);              Serial.println();
    Serial.print("# of sats:        "); Serial.print(data.numSats);             Serial.println();
    Serial.print("GPS HDOP:         "); Serial.print(data.HDOP/10);             Serial.println();
    Serial.print("Latitude:         "); Serial.print(data.latitude/1000000);    Serial.println("°");
    Serial.print("Longitude:        "); Serial.print(data.longitude/1000000);   Serial.println("°");
    Serial.print("GPS speed:        "); Serial.print(data.GPSSpeed/1000);       Serial.println(" kts");
    Serial.print("GPS course:       "); Serial.print(data.GPSCourse/1000);      Serial.println("°");
    Serial.print("Barometer temp:   "); Serial.print(data.baroTemp);	        Serial.println("°C");
    Serial.print("Pressure:         "); Serial.print(data.pressure);            Serial.println(" Pa");
    Serial.print("Altitude (AGL):   "); Serial.print(data.altitude);            Serial.println(" m");
    Serial.print("System calib:     "); Serial.print(data.sysCal);              Serial.println();
    Serial.print("Gyro calib:       "); Serial.print(data.gyroCal);             Serial.println();
    Serial.print("Accel calib:      "); Serial.print(data.accelCal);            Serial.println();
    Serial.print("Mag calib:        "); Serial.print(data.magCal);              Serial.println();
    Serial.print("X acceleration:   "); Serial.print(data.accelX);              Serial.println(" m/s");
    Serial.print("Y acceleration:   "); Serial.print(data.accelY);              Serial.println(" m/s");
    Serial.print("Z acceleration:   "); Serial.print(data.accelZ);              Serial.println(" m/s");
    Serial.print("X gyro:           "); Serial.print(data.gyroX);               Serial.println(" rad/s");
    Serial.print("Y gyro:           "); Serial.print(data.gyroY);               Serial.println(" rad/s");
    Serial.print("Z gyro:           "); Serial.print(data.gyroZ);               Serial.println(" rad/s");
    Serial.print("Roll:             "); Serial.print(data.roll);                Serial.println("°");
    Serial.print("Pitch:            "); Serial.print(data.pitch);               Serial.println("°");
    Serial.print("Yaw:              "); Serial.print(data.yaw);                 Serial.println("°");
    Serial.print("X linear accel:   "); Serial.print(data.linAccelX);           Serial.println(" m/s");
    Serial.print("X linear accel:   "); Serial.print(data.linAccelY);           Serial.println(" m/s");
    Serial.print("X linear accel:   "); Serial.print(data.linAccelZ);           Serial.println(" m/s");
    Serial.print("IMU temp:         "); Serial.print(data.imuTemp);             Serial.println("°C");
    Serial.print("SHT temp:         "); Serial.print(data.shtTemp);             Serial.println("°C");
    Serial.print("Humidity:         "); Serial.print(data.humidity);             Serial.println("%");
    Serial.print("State:            "); Serial.print(data.state);               Serial.println();
    Serial.print("Packet size:      "); Serial.print(data.packetSize);          Serial.println();
}

/**
 * Prints out telemetry data in the format expected by the base station. For testing purposes only!
*/
void printBaseStationTelemetry() {
    // Parse timestamp
    char _buf[64];
    sprintf(_buf, "%04d-%02d-%02dT%02d:%02d:%02d.%03d", data.year, data.month, data.day, data.hour, data.minute, data.second, data.msecond);

    Serial.print(_buf); Serial.print(',');
    Serial.print(data.voltage); Serial.print(',');
    Serial.print(data.GPSFix); Serial.print(',');
    Serial.print(data.numSats); Serial.print(',');
    Serial.print(data.HDOP); Serial.print(',');
    Serial.print(data.latitude); Serial.print(',');
    Serial.print(data.longitude); Serial.print(',');
    Serial.print(data.GPSSpeed); Serial.print(',');
    Serial.print(data.GPSCourse); Serial.print(',');
    Serial.print(data.altitude); Serial.print(',');
    Serial.print(data.sysCal); Serial.print(',');
    Serial.print(data.gyroCal); Serial.print(',');
    Serial.print(data.accelCal); Serial.print(',');
    Serial.print(data.magCal); Serial.print(',');
    Serial.print(data.accelX); Serial.print(',');
    Serial.print(data.accelY); Serial.print(',');
    Serial.print(data.accelZ); Serial.print(',');
    Serial.print(data.gyroX); Serial.print(',');
    Serial.print(data.gyroY); Serial.print(',');
    Serial.print(data.gyroZ); Serial.print(',');
    Serial.print(data.roll); Serial.print(',');
    Serial.print(data.pitch); Serial.print(',');
    Serial.print(data.yaw); Serial.print(',');
    Serial.print(data.linAccelX); Serial.print(',');
    Serial.print(data.linAccelY); Serial.print(',');
    Serial.print(data.linAccelZ); Serial.print(',');
    Serial.print(data.imuTemp); Serial.print(',');
    Serial.print(data.shtTemp); Serial.print(',');
    Serial.print(data.humidity); Serial.print(',');
    Serial.print(data.state); Serial.print(',');
    Serial.print(data.packetSize); Serial.print(',');
    Serial.print(0); Serial.print(','); // Period
    Serial.print(0); Serial.print(','); // Frequency
    Serial.print(0); Serial.print(','); // RSSI
    Serial.print(0); Serial.print(','); // DX
    Serial.print(0); Serial.print(','); // DY
    Serial.println(0);                  // Distance
}