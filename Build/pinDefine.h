/* 로터리 엔코더 */
#pragma region Encoder
#define Encoder_CLK 2
#define Encoder_DT 4
#define Encoder_SW 3
#pragma endregion

/* 디스플레이 OLED */
#pragma region Display      
#define DISPLAY_SCREEN_WIDTH 128
#define DISPLAY_SCREEN_HEIGHT 32
#define DISPLAY_OLED_RESET -1
#define DISPLAY_SCREEN_ADDRESS 0x3C
#pragma endregion

/* LED STRAP */
#pragma region LED_Strap
#define LedStrap_PIN 7;
#define LedStrap_NUMPIXELS 280;
#define LedStrap_BRIGHTNESS 180;
#pragma endregion

/* 습도 측정기 */
#pragma region detect_Hum
#define DetectHum_Pin A1
#pragma endregion