#include "ui.h"
#include "../display/display.h"

#define MAX_MSG 8

String mensagens[MAX_MSG];
uint8_t totalMensagens = 0;

uint16_t rxCount = 0;
uint16_t txCount = 0;

void drawMessages()
{
    // Limpa área de mensagens
    tft.fillRect(2, 27, 236, 266, ST77XX_BLACK);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);

    int y = 35;

    for (int i = 0; i < totalMensagens; i++)
    {
        tft.setCursor(5, y);
        tft.print(mensagens[i]);
        y += 15;
    }
}

void addMessage(String msg)
{
    if (totalMensagens < MAX_MSG)
    {
        mensagens[totalMensagens++] = msg;
    }
    else
    {
        for (int i = 1; i < MAX_MSG; i++)
        {
            mensagens[i - 1] = mensagens[i];
        }

        mensagens[MAX_MSG - 1] = msg;
    }

    drawMessages();
}

void addRX(const char* msg)
{
    rxCount++;

    addMessage("RX> " + String(msg));

    drawStatusBar();
}

void addTX(const char* msg)
{
    txCount++;

    addMessage("TX> " + String(msg));

    drawStatusBar();
}

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

    // Área principal
    tft.drawRect(0, 25, 240, 270, ST77XX_WHITE);

    // Footer
    drawStatusBar();

    // Mensagens de teste
    addRX("Sistema iniciado");
    addTX("Teste");
    addRX("ACK");
}

void drawStatusBar()
{
    tft.fillRect(0, 295, 240, 25, ST77XX_BLUE);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);

    tft.setCursor(5, 303);
    tft.print("RX:");
    tft.print(rxCount);

    tft.setCursor(180, 303);
    tft.print("TX:");
    tft.print(txCount);
}