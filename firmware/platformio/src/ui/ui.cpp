#include "ui.h"
#include "../display/display.h"

void drawHomeScreen()
{
    tft.fillScreen(ST77XX_BLACK);

    // Header
    tft.fillRect(0, 0, 240, 25, ST77XX_GREEN);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);

    tft.setCursor(5, 8);
    tft.print("NexusCom");

    tft.setCursor(170, 8);
    tft.print("LoRa SIM");

    // Area principal
    tft.drawRect(0, 25, 240, 270, ST77XX_WHITE);

    // Mensagem central
    tft.setTextSize(2);

    tft.setCursor(60, 140);
    tft.print("INICIANDO");

    // Footer
    tft.fillRect(0, 295, 240, 25, ST77XX_BLUE);

    tft.setTextSize(1);

    tft.setCursor(5, 303);
    tft.print("RX:0");

    tft.setCursor(190, 303);
    tft.print("TX:0");
}