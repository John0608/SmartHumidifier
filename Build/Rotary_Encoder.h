#include "MyOLED.h"
#ifndef MyOLED_H
#define MyOLED_H
#include "MyOLED.h"
#endif // MyOLED_H
#include "pinDefine.h"


class MyOLED;

#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H


class Rotary_Encoder
{
public:
    static unsigned long last_milli_sec;
    static int count;
    int old_DT;
    int direction;       // 방향 저장 변수
    int virtualPosition; // 정적으로 선언
    static const int CLK = Encoder_CLK;
    static const int DT = Encoder_DT;
    static const int SW = Encoder_SW;
    static MyOLED* oled_obj;

    Rotary_Encoder();
    static void oled_Link(MyOLED* oled_obj);
    static void CLICK_ISR();
    static void SWITCH_ISR();
    static void update_ms(unsigned long ms);
    void setup();
    static unsigned long Rotary_Encoder::get_ms();

};

#endif // ROTARY_ENCODER_H