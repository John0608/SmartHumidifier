#include <Thread.h>

#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_GFX.h>

#include "MyOLED.h"
#include "Rotary_Encoder.h"
#include "LED_Strap.h"
#include "detect_Hum.h"

// 로터리 엔코더 핀
static int now_hum = 0;
static int target_hum = 0;
static int count = 0; 

extern Rotary_Encoder encoder;
extern MyOLED myOLED;
extern LED_Strap led_strap;
extern detect_Hum d_Hum;




class detect_water
{
public:
    static void detect()
    {
        Serial.println("빗물 감지됨");
    }

private:
    static const int PIN = A3;
};

// void colorWipe(uint32_t c, uint8_t wait){
//   for(uint16_t i=0; i<strip.numiPxels(); i++){
//     strip.setPixelColor(i,c);9
//     strip.show();
//     delay(wait);
//   }
// }

// strip.setBrightness(BRIGHTNESS);
// strip.begin();
// strip.show();

//  strip.begin();
// strip.setPixelColor(0, 255, 0, 0);
// strip.setPixelColor(1, 0, 255, 0);
// strip.setPixelColor(2, 0, 0, 0);
// strip.setPixelColor(3, 255, 255, 50);
// strip.show();
// delay(500);

// colorWipe(strip.Color(255,0,0),5);
// colorWipe(strip.Color(0,255,0),5);
// colorWipe(strip.Color(0,0,255),5);
// colorWipe(strip.Color(255,255,255),5);
