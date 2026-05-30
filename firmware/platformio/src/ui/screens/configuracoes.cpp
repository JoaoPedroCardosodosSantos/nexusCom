#include "configuracoes.h"
#include "../../display/display.h"

void drawConfiguracoes()
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
    tft.print("CONFIGURACOES");

    tft.setCursor(10, 40);
    tft.print("Canal: 1");

    tft.setCursor(10, 60);
    tft.print("ACK: ON");

    tft.setCursor(10, 80);
    tft.print("Potencia: Alta");

    tft.setCursor(10, 300);
    tft.print("D=Menu");
}