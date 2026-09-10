#include "display.h"

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

// =====================================================
// ST7789 - ESP32
// =====================================================

#define TFT_BL     27
#define TFT_RST    25
#define TFT_CS     33
#define TFT_DC     32

#define TFT_SCLK   18
#define TFT_MOSI   23

// =====================================================
// DISPLAY GLOBAL
// =====================================================

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

// =====================================================
// INICIALIZAÇÃO
// =====================================================

void initDisplay()
{
    // Backlight
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, HIGH);

    // SPI
    SPI.begin(
        TFT_SCLK,
        -1,
        TFT_MOSI,
        TFT_CS
    );

    // ST7789
    tft.init(240, 320);

    tft.setRotation(0);

    tft.fillScreen(ST77XX_BLACK);
}