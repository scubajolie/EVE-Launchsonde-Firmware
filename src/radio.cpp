#include <LoRa.h>
#include <radio.h>
#include <Arduino.h>
#include <SPI.h>
#include <pins.h>
#include <dotstar.h>
#include <telemetry.h>
#include <commands.h>


void initRadio() {
    #ifdef DIAGNOSTIC
        Serial.print("Initializing radio...");
    #endif
    LoRa.setPins(RFM_CS_PIN, RFM_RST_PIN, RFM_IRQ_PIN);
    
    if (!LoRa.begin(915E6)) {
        #ifdef DIAGNOSTIC
            Serial.println("Starting LoRa failed!");
        #endif
        while(true) blinkCode(RADIO_ERROR_CODE, RED); // Block further code execution
    }
    LoRa.setSyncWord(0xF3);
    #ifdef DIAGNOSTIC
        Serial.println("done!");
    #endif
}


void sendTelemetryData() {
    LoRa.beginPacket();
    LoRa.write(UUID);
    LoRa.write(RECEIVER_UUID);
    LoRa.write(TELEMETRY_PACKET);
    LoRa.write((uint8_t*) &data, data.packetSize);
    LoRa.endPacket();
    LoRa.receive();
}

void sendDiagnosticData(LogLevel level, const char * msg) {
    LoRa.beginPacket();
    LoRa.write(UUID);
    LoRa.write(RECEIVER_UUID);
    LoRa.write(LogLevel(LOG_PACKET)                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                  );     // packet type
    LoRa.write((byte) level);   // diagnostic code
    LoRa.print(msg);            // diagnostic message
    LoRa.endPacket();
    LoRa.receive();
}

void sendState(State_t s) {
    LoRa.beginPacket();
    LoRa.write(UUID);
    LoRa.write(RECEIVER_UUID);
    LoRa.write(STATE_PACKET);
    LoRa.write((int8_t) s);
    LoRa.endPacket();
    LoRa.receive();
}


// TODO: DEBUG FUNCTION
// TODO: RESEARCH LORA UUID AND PACKET HEADERS
void radioCallback(int packetSize) {
    if (packetSize == 0) return;

    // 
    byte sender = LoRa.read();
    Serial.print(sender);  // CHANGE TO CHECK WHAT SENDER IS
    byte destination = LoRa.read();
    if (destination != UUID) return; // Ignore received messages if not the intended receiver
    byte packetType = LoRa.read();
    if (packetType != COMMAND_PACKET) return; //Ignore any packets that aren't command packets
    byte cmdIdent = LoRa.read();
    byte cmdMsg;
    if (packetSize != 0) cmdMsg = LoRa.read(); // Remaining data is the command message
    executeCommand((Command) cmdIdent, cmdMsg); // Grab command identifier from radio packet and execute appropriate command
    //Additional processing for command messages???
}

