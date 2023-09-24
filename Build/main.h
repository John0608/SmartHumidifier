#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "MyOLED.h"
#include "Rotary_Encoder.h"

// 로터리 엔코더 핀
static int now_hum = 0;
static int target_hum = 0;
static int count = 0; 

extern Rotary_Encoder encoder;

class LED_Strap : public Adafruit_NeoPixel
{
public:
    LED_Strap() : Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800)
    {
        begin();
        setBrightness(BRIGHTNESS);
    }

private:
    static const uint8_t PIN = 7;
    static const uint16_t NUMPIXELS = 280;
    static const uint8_t BRIGHTNESS = 180;
};

class detect_Hum : public DHT
{
public:
    detect_Hum() : DHT(PIN, DHT11)
    {
        begin();
    }

    float getHum()
    {
        return readHumidity(); // Use the DHT library's readHumidity() method;
    }

private:
    static const uint8_t PIN = A1;
};

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
