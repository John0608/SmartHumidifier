#include "lib/Adafruit_NeoPixel-master/Adafruit_NeoPixel.h"
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 32
#define OLED_RESET -1
#define SCREEN_ADDRESS 0x3C

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

class LED_Strap : public Adafruit_NeoPixel {
public:
  LED_Strap() : Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800) {
    begin();
    setBrightness(BRIGHTNESS);
  }

private:
  static const uint8_t PIN = 7;
  static const uint16_t NUMPIXELS = 280;
  static const uint8_t BRIGHTNESS = 180;
};

class detect_Hum : public DHT {
public:
  detect_Hum() : DHT(PIN, DHT11) {
    begin();
  }

  float getHum() {
    return readHumidity(); // Use the DHT library's readHumidity() method;
  }

private:
  static const uint8_t PIN = A1;
};

class Rotary_Encoder {
public:
  void setup() {

    // Attach interrupts to static member functions
    attachInterrupt(digitalPinToInterrupt(CLK), &Rotary_Encoder::CLICK_ISR, RISING);
    attachInterrupt(digitalPinToInterrupt(SW), &Rotary_Encoder::SWITCH_ISR, RISING);
  }
  
  static unsigned long milli_sec;

  static void CLICK_ISR() {
    unsigned long ms = millis();
    if (get_ms() != ms) {
      Serial.println("클릭");
      update_ms(ms);
    }
  }

  static void DIRECTION_ISR() {
    // Handle DIRECTION interrupt
    //Serial.println("돌림");
  }

  static void SWITCH_ISR() {
    unsigned long ms = millis();
    if (get_ms() != ms) {
      Serial.println("눌림");
      update_ms(ms);
    }
  }

  static void update_ms(unsigned long ms) {
    milli_sec = ms;
  }

  static unsigned long get_ms() {
    return milli_sec;
  }

private:
  const int CLK = 2;
  const int DT = 4;
  static const int SW = 3;
};

unsigned long Rotary_Encoder::milli_sec = 0;

detect_Hum hum; // 객체 생성시 'new' 연산자 사용하지 않음
Rotary_Encoder encoder;

const int moistureSensorPin = A3;

void setup() {
  Serial.begin(9600);
  encoder.setup(); // Rotary 엔코더 초기화
  // Your setup code here
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for (;;);
  }

  display.clearDisplay();
  display.setTextSize(2); // 텍스트 크기를 4로 설정
  display.setTextColor(SSD1306_WHITE);
}

void loop() {
  // Your loop code here

  float humidity = hum.getHum();
  int moistureLevel = analogRead(moistureSensorPin);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.print(humidity);
  display.print("%");

  display.setCursor(0, 10);
  display.print(moistureLevel);


  display.display();

  delay(1000);
}





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
