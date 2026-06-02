#include "boot.h"
#include "../display/display.h"

static uint8_t progressoAnterior = 0;

void drawBootScreen()
{
    tft.fillScreen(ST77XX_BLACK);

    tft.setTextColor(
        ST77XX_GREEN
    );

    tft.setTextSize(2);

    tft.setCursor(
        45,
        60
    );

    tft.print(
        "NexusCom"
    );

    tft.setTextSize(1);

    tft.setCursor(
        70,
        90
    );

    tft.print(
        "LoRa Messenger"
    );

    // Moldura da barra

    tft.drawRect(
        20,
        150,
        200,
        20,
        ST77XX_WHITE
    );

    progressoAnterior = 0;
}

void updateBootProgress(
    uint8_t percentual,
    const char* texto
)
{
    uint16_t larguraAnterior =
        (progressoAnterior * 196) / 100;

    uint16_t larguraNova =
        (percentual * 196) / 100;

    if(
        larguraNova > larguraAnterior
    )
    {
        tft.fillRect(
            22 + larguraAnterior,
            152,
            larguraNova - larguraAnterior,
            16,
            ST77XX_GREEN
        );
    }

    // Limpa área do percentual

    tft.fillRect(
        90,
        180,
        60,
        12,
        ST77XX_BLACK
    );

    tft.setTextColor(
        ST77XX_WHITE
    );

    tft.setCursor(
        100,
        180
    );

    tft.print(percentual);

    tft.print("%");

    // Limpa área da mensagem

    tft.fillRect(
        20,
        200,
        200,
        12,
        ST77XX_BLACK
    );

    tft.setCursor(
        20,
        200
    );

    tft.print(texto);

    progressoAnterior =
        percentual;
}

void bootAnimation()
{
    drawBootScreen();

    updateBootProgress(
        25,
        "Inicializando Display..."
    );

    delay(1000);

    updateBootProgress(
        50,
        "Inicializando Teclado..."
    );

    delay(1000);

    updateBootProgress(
        75,
        "Inicializando LoRa..."
    );

    delay(1000);

    updateBootProgress(
        100,
        "Carregando Interface..."
    );

    delay(1000);
}