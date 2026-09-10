#include "ui.h"
#include "../display/display.h"
#include "../core/sistema.h"
#include "../model/contato.h"
#include "../core/sistema.h"

#define MAX_MSG 8

String mensagens[MAX_MSG];
uint8_t totalMensagens = 0;


void drawMessages()
{
    // Limpa área de mensagens
    tft.fillRect(2, 27, 236, 230, ST77XX_BLACK);

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
    sistema.rxCount++;

    addMessage("RX> " + String(msg));

    drawStatusBar();
}

void addTX(const char* msg)
{
    sistema.txCount++;

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

    tft.setCursor(150, 8);
    tft.print(
        contatos[
            sistema.contatoSelecionado
        ].nome
    );

    // Área principal
    tft.drawRect(0, 25, 240, 270, ST77XX_WHITE);

    // Footer
    drawStatusBar();

    // Editor de texto
    drawEditor(
        "",
        false
    );
}

void drawStatusBar()
{
    tft.fillRect(0, 295, 240, 25, ST77XX_BLUE);

    tft.setTextColor(ST77XX_WHITE);
    tft.setTextSize(1);

    tft.setCursor(5, 303);
    tft.print("RX:");
    tft.print(
        sistema.rxCount
    );

    tft.setCursor(180, 303);
    tft.print("TX:");
    tft.print(
        sistema.txCount
    );
}

void drawEditor(
    const char* texto,
    bool modoNumerico
)
{
    // fundo

    tft.fillRect(
        0,
        260,
        240,
        35,
        ST77XX_BLACK
    );

    // borda

    tft.drawRect(
        0,
        260,
        240,
        35,
        ST77XX_WHITE
    );

    tft.setTextColor(
        ST77XX_YELLOW
    );

    tft.setTextSize(1);

    // texto digitado

    tft.setCursor(
        5,
        272
    );

    tft.print(">");

    tft.print(texto);

    // indicador de modo

    tft.setTextColor(
        ST77XX_CYAN
    );

    tft.setCursor(
        205,
        272
    );

    if(modoNumerico)
    {
        tft.print("123");
    }
    else
    {
        tft.print("ABC");
    }
}