#include <pins.h>
#include <Adafruit_DotStar.h>
#include <dotstar.h>
#include <states.h>


void initDotStar() {
    #ifdef DIAGNOSTIC
        Serial.print("Initializing DotStar RGB LED...");
    #endif
    strip.begin(); // Initialize pins for output
    strip.setBrightness(50);
    strip.clear(); // Turn all LEDs off ASAP
    strip.show();  
    #ifdef DIAGNOSTIC
        Serial.println("done!");
    #endif
}

void blinkCode(byte code, uint32_t color) {
    bool dash = true;
    for (int n=0; n<4; n++) {
        if (bitRead(code, n)) {
            if (dash) {
                strip.setPixelColor(0, color); strip.show();
                delay(DASH_ON);
                strip.setPixelColor(0, OFF); strip.show();
                delay(BLINK_INTERVAL);
            }
            else {
                strip.setPixelColor(0, color); strip.show();
                delay(DOT_ON);
                strip.setPixelColor(0, OFF); strip.show();
                delay(BLINK_INTERVAL);
            }
        }
        else {
            if (dash) delay(DASH_ON+BLINK_INTERVAL);
            else delay(DOT_ON+BLINK_INTERVAL);
        }
        dash = !dash;
    }
    delay(MESSAGE_INTERVAL);
}