#include "contatos.h"

#include "../../display/display.h"
#include "../../model/contato.h"

void drawContatos()
{
    tft.fillScreen(ST77XX_BLACK);

    // Header

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

    tft.setCursor(
        5,
        8
    );

    tft.print(
        "CONTATOS"
    );

    // Lista

    int y = 50;

    for(
        uint8_t i = 0;
        i < TOTAL_CONTATOS;
        i++
    )
    {
        tft.setCursor(
            20,
            y
        );

        tft.print(
            i + 1
        );

        tft.print(
            " - "
        );

        tft.print(
            contatos[i].nome
        );

        y += 25;
    }

    tft.setCursor(
        10,
        300
    );

    tft.print(
        "D = Voltar"
    );
}