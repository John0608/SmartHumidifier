#include <Adafruit_NeoPixel.h>
#include "pinDefine.h"

class LED_Strap {

public:
    static const uint8_t PIN = LedStrap_PIN;
    static const uint16_t NUMPIXELS = LedStrap_NUMPIXELS;
    static const uint8_t BRIGHTNESS = LedStrap_BRIGHTNESS;
    
    LED_Strap()
    {
        pixel = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);
        pixel.begin();
        pixel.setBrightness(BRIGHTNESS);
    }

    void setBrightness(uint8_t value);


private:
    Adafruit_NeoPixel pixel; 
};