#include <DHT.h>
#include "pinDefine.h"

class detect_Hum : public DHT
{
public:
    detect_Hum() : DHT(PIN, DHT11) {
        begin();
    }

    float getHum();

private:
    static const uint8_t PIN = DetectHum_Pin;
};