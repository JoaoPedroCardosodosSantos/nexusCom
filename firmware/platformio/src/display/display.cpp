#include "display.h"

#include <Adafruit_GFX.h>
#include <Adafruit_ST7789.h>

#define TFT_CS   10
#define TFT_DC    9
#define TFT_RST  -1

Adafruit_ST7789 tft(TFT_CS, TFT_DC, TFT_RST);

void initDisplay()
{
    tft.init(240, 320);
    tft.setRotation(2);
}