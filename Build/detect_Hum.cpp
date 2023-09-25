#include "detect_Hum.h"

float detect_Hum::getHum() {
    return readHumidity(); // Use the DHT library's readHumidity() method;
}