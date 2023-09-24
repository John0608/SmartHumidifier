#include "main.h"

// int Rotary_Encoder::old_DT = 0;
// int Rotary_Encoder::direction = 0;
// int Rotary_Encoder::virtualPosition = 0; // 정적으로 선언
// unsigned long Rotary_Encoder::last_milli_sec = 0;
MyOLED myOLED;
Rotary_Encoder encoder;


void setup() {
  Serial.begin(9600);
  myOLED.begin();
  encoder.oled_Link(&myOLED);
  myOLED.RT_Link(&encoder);
  delay(2000);
  // Your setup code here
}

unsigned int a = 0;
void loop() {
  myOLED.clearDisplay(); 
  myOLED.displayText(0,0,"num : ",a);
  a++;
  delay(500);
}