#include "Rotary_Encoder.h"
#include "pinDefine.h"

int Rotary_Encoder::count = 0;
unsigned long Rotary_Encoder::last_milli_sec = 0;
MyOLED* Rotary_Encoder::oled_obj;

Rotary_Encoder::Rotary_Encoder()
{
    pinMode(CLK, INPUT);
    pinMode(SW, INPUT_PULLUP);
    pinMode(DT, INPUT);
}

void Rotary_Encoder::setup()
{
  attachInterrupt(digitalPinToInterrupt(this->CLK), Rotary_Encoder::CLICK_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(SW), Rotary_Encoder::SWITCH_ISR, RISING);
}

static void Rotary_Encoder::oled_Link(MyOLED* oled_obj)
{
    oled_obj = oled_obj;
}

static void Rotary_Encoder::CLICK_ISR()
{
    boolean up = (digitalRead(DT) == digitalRead(CLK));
    boolean TurnDetected = false;
    
    if (up)
    {
        count -= 1;
        Serial.println("LEFT");
        Rotary_Encoder::oled_obj->displayText(0, 0, "num : ", count);
        
    }
    else
    {
        // 오른쪽으로 돌렸을 때
        count += 1;
        Serial.println("RIGHT");
        Rotary_Encoder::oled_obj->displayText(0, 0, "num : ", count);
    }
    TurnDetected = true;

    if (TurnDetected) TurnDetected = false; 
}

static void Rotary_Encoder::SWITCH_ISR()
{
    unsigned long ms = millis();
    if (Rotary_Encoder::get_ms() != ms)
    {
        Serial.println("눌림");
        update_ms(ms);
    }
}

static void Rotary_Encoder::update_ms(unsigned long ms)
{
    last_milli_sec = ms;
}

static unsigned long Rotary_Encoder::get_ms()
{
    return last_milli_sec;
}