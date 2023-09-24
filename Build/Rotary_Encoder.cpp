#include "Rotary_Encoder.h"
#include "pinDefine.h"

Rotary_Encoder::Rotary_Encoder()
{
    pinMode(CLK, INPUT);
    pinMode(SW, INPUT_PULLUP);
    pinMode(DT, INPUT);
    attachInterrupt(digitalPinToInterrupt(CLK), Rotary_Encoder::CLICK_ISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(SW), Rotary_Encoder::SWITCH_ISR, RISING);
}

static void Rotary_Encoder::oled_Link(MyOLED* oled_obj)
{
    this->oled_obj = oled_obj;
}

static void Rotary_Encoder::CLICK_ISR()
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

static void Rotary_Encoder::SWITCH_ISR()
{
    unsigned long ms = millis();
    if (get_ms() != ms)
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