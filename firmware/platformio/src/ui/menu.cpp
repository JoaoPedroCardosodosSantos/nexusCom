#include "menu.h"
#include "../display/display.h"

void drawMenu()
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

    tft.setCursor(
        5,
        8
    );

    tft.print("MENU");

    tft.setCursor(10,40);
    tft.print("1 Mensagens");

    tft.setCursor(10,60);
    tft.print("2 Contatos");

    tft.setCursor(10,80);
    tft.print("3 Configuracoes");

    tft.setCursor(10,100);
    tft.print("4 Status LoRa");

    tft.setCursor(10,120);
    tft.print("5 Sobre");
}