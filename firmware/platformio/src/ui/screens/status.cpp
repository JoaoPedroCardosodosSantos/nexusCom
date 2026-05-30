#include "status.h"
#include "../../display/display.h"

void drawStatus()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.fillRect(
        0,
        0,
        240,
        25,
        ST77XX_GREEN
    );

    tft.setTextColor(
        ST77XX_WHITE
    );

    tft.setTextSize(1);

    tft.setCursor(5, 8);
    tft.print("STATUS LORA");

    tft.setCursor(10, 40);
    tft.print("RSSI: ---");

    tft.setCursor(10, 60);
    tft.print("SNR: ---");

    tft.setCursor(10, 80);
    tft.print("Canal: 1");

    tft.setCursor(10, 300);
    tft.print("D=Menu");
}