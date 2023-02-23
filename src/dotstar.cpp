#include <pins.h>
#include <Adafruit_DotStar.h>
#include <dotstar.h>
#include <states.h>

Adafruit_DotStar EVEstrip(1, DOTSTAR_DATA_PIN, DOTSTAR_CLK_PIN, DOTSTAR_RGB);
const uint32_t OFF      =  EVEstrip.Color(0, 0, 0);       //BGR
const uint32_t WHITE    =  EVEstrip.Color(255, 255, 255);
const uint32_t BLUE     =  EVEstrip.Color(255, 0, 0);
const uint32_t RED      =  EVEstrip.Color(0, 0, 255);
const uint32_t GREEN    =  EVEstrip.Color(0, 255, 0);
const uint32_t PURPLE   =  EVEstrip.Color(255, 0, 255);
const uint32_t AMBER    =  EVEstrip.Color(0, 191, 255);
const uint32_t CYAN     =  EVEstrip.Color(255, 255, 0);
const uint32_t LIME     =  EVEstrip.Color(0, 255, 125);


void initDotStar() {
    #ifdef DIAGNOSTIC
        Serial.print("Initializing DotStar RGB LED...");
    #endif
    EVEstrip.begin(); // Initialize pins for output
    EVEstrip.setBrightness(50);
    EVEstrip.clear(); // Turn all LEDs off ASAP
    EVEstrip.show();  
    #ifdef DIAGNOSTIC
        Serial.println("done!");
    #endif
}

void blinkCode(byte code, uint32_t color) {
    bool dash = true;
    for (int n=0; n<4; n++) {
        if (bitRead(code, n)) {
            if (dash) {
                EVEstrip.setPixelColor(0, color); EVEstrip.show();
                delay(DASH_ON);
                EVEstrip.setPixelColor(0, OFF); EVEstrip.show();
                delay(BLINK_INTERVAL);
            }
            else {
                EVEstrip.setPixelColor(0, color); EVEstrip.show();
                delay(DOT_ON);
                EVEstrip.setPixelColor(0, OFF); EVEstrip.show();
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