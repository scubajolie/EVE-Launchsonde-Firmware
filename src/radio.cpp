#include <LoRa.h>
#include <radio.h>
#include <Arduino.h>
#include <SPI.h>
#include <pins.h>
#include <dotstar.h>
#include <telemetry.h>
#include <commands.h>

const PROGMEM char UUID_FILENAME[9] = "UUID.txt";
byte CORE_UUID = 0xAA; // 8 bits signed byte: -63 to 63
byte UUID = 0xBB; // ROCKET 1 UUID
byte UUID_R1 = 0xBB;
byte UUID_R2 = 0xCC; // Rocket 2
byte UUID_R3 = 0xDD; // Rocket 3
byte GROUNDSTATION_UUID = 0xEE;
bool isUUIDConfig = true;
const PROGMEM byte RECEIVER_UUID = 0x00; // Default receiver UUID is 0x00
const byte TELEMETRY_PACKET;

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
    // LoRa.write(UUID);
    LoRa.write(TELEMETRY_PACKET);
    LoRa.write((uint8_t*) &data, data.packetSize);
    LoRa.endPacket();
    LoRa.receive();
}

void sendDiagnosticData(LogLevel level, const char * msg) {
    LoRa.beginPacket();
    LoRa.write(UUID);
    LoRa.write(RECEIVER_UUID);
    LoRa.write(PacketType(LOG_PACKET));    // packet type
    LoRa.write(LogLevel(level));   // diagnostic code
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
void radioCallback(int packetSize) {
    // if (packetSize == 0) return;

    // // 
    // byte sender = LoRa.read();
    // Serial.print(sender);  // CHANGE TO CHECK WHAT SENDER IS
    // byte destination = LoRa.read();
    // if (destination != UUID) return; // Ignore received messages if not the intended receiver
    // byte packetType = LoRa.read();
    // if (packetType != COMMAND_PACKET) return; //Ignore any packets that aren't command packets
    // byte cmdIdent = LoRa.read();
    // byte cmdMsg;
    // if (packetSize != 0) cmdMsg = LoRa.read(); // Remaining data is the command message
    // executeCommand((Command) cmdIdent, cmdMsg); // Grab command identifier from radio packet and execute appropriate command
    // //Additional processing for command messages???
}

