#include <Arduino.h>
#line 1 "C:\\Users\\dygks\\바탕 화면\\졸작\\SmartHumidifier\\Build\\Build.ino"
#include "main.h"

int Rotary_Encoder::old_DT = 0;
int Rotary_Encoder::direction = 0;
int Rotary_Encoder::virtualPosition = 0; // 정적으로 선언
unsigned long Rotary_Encoder::last_milli_sec = 0;



#line 10 "C:\\Users\\dygks\\바탕 화면\\졸작\\SmartHumidifier\\Build\\Build.ino"
void setup();
#line 21 "C:\\Users\\dygks\\바탕 화면\\졸작\\SmartHumidifier\\Build\\Build.ino"
void loop();
#line 10 "C:\\Users\\dygks\\바탕 화면\\졸작\\SmartHumidifier\\Build\\Build.ino"
void setup() {
  encoder.setup(); // Rotary 엔코더 초기화
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
