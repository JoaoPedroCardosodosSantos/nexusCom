#include "contatos.h"
#include "../../display/display.h"

void drawContatos()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.fillRect(0,0,240,25,ST77XX_GREEN);

    tft.setTextColor(ST77XX_WHITE);

    tft.setCursor(5,8);
    tft.print("CONTATOS");

    tft.setCursor(10,40);
    tft.print("Nenhum contato");

    tft.setCursor(10,300);
    tft.print("D=Menu");
}