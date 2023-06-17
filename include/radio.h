#ifndef EVE_RADIO_H
#define EVE_RADIO_H

#include <LoRa.h>
#include <Arduino.h>
#include <SPI.h>
#include <logging.h>
#include <states.h>

// enum PacketType {
//     TELEMETRY_PACKET, // 1
//     LOG_PACKET,       // 2
//     COMMAND_PACKET,   // 3
//     STATE_PACKET      // 4
// };

extern const byte TELEMETRY_PACKET = 1;

// UPDATE UUID TO CURRENT ROCKET BEFORE UPLOADING IN RADIO.CPP
extern const PROGMEM char UUID_FILENAME[9];
extern byte CORE_UUID;
extern byte UUID;
extern byte GROUNDSTATION_UUID;
extern bool isUUIDConfig;
extern const PROGMEM byte RECEIVER_UUID; // Default receiver UUID is 0x00

void initRadio();

/*
Packet structure:
---IMPLICIT HEADERS---
1. Sender UUID
2. Destination UUID
3. Payload type (telemetry, log, command)

---TELEMETRY PAYLOAD---
4a. Telemetry data structure
5a. End packet

---DIAGNOSTIC PAYLOAD---
4b. Log level
5b. Log message
6b. End packet

---COMMAND PAYLOAD---
4c. Command identifier
5c. Command message (if applicable)
6c. End packet
*/
void sendTelemetryData();

void sendDiagnosticData(LogLevel level, const char * msg);

void sendState(State_t s);

void radioCallback(int packetSize);

#endif
