#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_GFX.h>
#include "pinDefine.h"

#ifndef Rotary_Encoder_h
#define Rotary_Encoder_h
#include "Rotary_Encoder.h"
#endif

#ifndef MYOLED_H
#define MYOLED_H

class Rotary_Encoder;

class MyOLED {
    public:
        MyOLED() {
          display = Adafruit_SSD1306(DISPLAY_SCREEN_WIDTH, DISPLAY_SCREEN_HEIGHT, &Wire, DISPLAY_OLED_RESET);
        }
        void begin();
        void clearDisplay();
        void displayText(int x, int y, const char* text);
        void displayText(int x, int y, const char* text1, unsigned int text2);
        void RT_Link(Rotary_Encoder* rt_object);

    private:
        Adafruit_SSD1306 display;
        Rotary_Encoder *rt_object;
};

#endif // MYOLED_H