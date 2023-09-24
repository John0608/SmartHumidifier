#include "MyOLED.h"

MyOLED::MyOLED() {
    display(128, 32, &Wire, -1);
}

void MyOLED::begin(){
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
      Serial.println(F("SSD1306 allocation failed"));
      for (;;) {}
    }
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(1, 1);
    display.print("Hello World");
    display.display();
}

void MyOLED::clearDisplay() {
    display.clearDisplay();
}

void MyOLED::displayText(int x, int y, const char* text) {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(text);
    display.display();
  }
void MyOLED::displayText(int x, int y, const char* text1, unsigned int text2) {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(text1);
    display.print(text2, DEC);
    display.display();
  }
void MyOLED::displayBitmap(const uint8_t* bitmap, int width, int height) {
    display.drawBitmap(0, 0, bitmap, width, height, SSD1306_WHITE);
    display.display();
    }

void MyOLED::RT_Link(Rotary_Encoder rt_obj) {
    rt_object = rt_obj;
}