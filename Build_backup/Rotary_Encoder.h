#include "MyOLED.h"
#ifndef MyOLED_H
#define MyOLED_H
#include "MyOLED.h"
#endif // MyOLED_H
#include "pinDefine.h"

#ifndef ROTARY_ENCODER_H
#define ROTARY_ENCODER_H

class MyOLED;

class Rotary_Encoder
{
public:
    unsigned long last_milli_sec;
    int old_DT;
    int direction;       // 방향 저장 변수
    int virtualPosition; // 정적으로 선언

    Rotary_Encoder();
    void oled_Link(MyOLED* oled_obj);
    void CLICK_ISR();
    void SWITCH_ISR();
    void update_ms(unsigned long ms);
    void get_ms();

private:
    const int CLK = Encoder_CLK;
    const int DT = Encoder_DT;
    const int SW = Encoder_SW;
    int count = 0;
    MyOLED* oled_obj;
};

#endif // ROTARY_ENCODER_H