#line 1 "C:\\Users\\dygks\\바탕 화면\\졸작\\SmartHumidifier\\Build\\main.h"
#include <Adafruit_NeoPixel.h>
#include <DHT.h>
#include <Wire.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>
#include <Adafruit_GFX.h>


// 로터리 엔코더 핀
#pragma region Encoder 
#define Encoder_CLK 2
#define Encoder_DT 4
#define Encoder_SW 3
#pragma endregion

#pragma region Display
#define DISPLAY_SCREEN_WIDTH 128
#define DISPLAY_SCREEN_HEIGHT 32
#define DISPLAY_OLED_RESET -1
#define DISPLAY_SCREEN_ADDRESS 0x3C
#pragma endregion

static int now_hum = 0;
static int target_hum = 0;
static int count = 0; 

extern detect_Hum hum; // 객체 생성시 'new' 연산자 사용하지 않음
extern MyOLED myOLED;
extern Rotary_Encoder encoder;

class MyOLED {
public:
  MyOLED() : display(128, 32, &Wire, -1) {}

  void begin() {
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

  void clearDisplay() {
    display.clearDisplay();
  }

  void displayText(int x, int y, const char* text) {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.println(text);
    display.display();
  }

  void displayText(int x, int y, const char* text1, unsigned int text2) {
    display.setTextSize(2);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(x, y);
    display.print(text1);
    display.print(text2, DEC);
    display.display();
  }

  void displayBitmap(const uint8_t* bitmap, int width, int height) {
    display.drawBitmap(0, 0, bitmap, width, height, SSD1306_WHITE);
    display.display();
  }

  void RT_Link(Rotary_Encoder rt_obj)
  {
    rt_object = rt_obj;
  }

private:
  Adafruit_SSD1306 display;
  Rotary_Encoder *rt_object;
};

class Rotary_Encoder
{
public:
    unsigned long last_milli_sec;
    int old_DT;
    int direction;       // 방향 저장 변수
    int virtualPosition; // 정적으로 선언
    
    void setup()
    {
        pinMode(CLK, INPUT);
        pinMode(SW, INPUT_PULLUP);
        pinMode(DT, INPUT);
        attachInterrupt(digitalPinToInterrupt(CLK), &Rotary_Encoder::CLICK_ISR, CHANGE);
        attachInterrupt(digitalPinToInterrupt(SW), &Rotary_Encoder::SWITCH_ISR, RISING);
    }

    void oled_Link(MyOLED* oled_obj)
    {
        this->oled_obj = oled_obj;
    }

    void CLICK_ISR()
    {
        boolean up = (digitalRead(DT) == digitalRead(CLK));
        boolean TurnDetected = false;
        
        if (up)
        {
            count -= 1;
            Serial.println("LEFT");
            oled_obj->displayText(0, 0, "num : ", count);
        }
        else
        {
            // 오른쪽으로 돌렸을 때
            count += 1;
            Serial.println("RIGHT");
            oled_obj->displayText(0, 0, "num : ", count);
        }
        TurnDetected = true;

        if (TurnDetected) TurnDetected = false; 
    }

    void SWITCH_ISR()
    {
        unsigned long ms = millis();
        if (get_ms() != ms)
        {
            Serial.println("눌림");
            update_ms(ms);
        }
    }

    void update_ms(unsigned long ms)
    {
        last_milli_sec = ms;
    }

    unsigned long get_ms()
    {
        return last_milli_sec;
    }

private:
    const int CLK = Encoder_CLK;
    const int DT = Encoder_DT;
    const int SW = Encoder_SW;
    MyOLED* oled_obj;
};


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
