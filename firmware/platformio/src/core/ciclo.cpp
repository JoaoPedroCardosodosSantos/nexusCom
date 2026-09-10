#include "ciclo.h"

#include <Arduino.h>

#include "sistema.h"
#include "dispatcher.h"

#include "debug/logger.h"
#include "serial/commandManager.h"

#include "../display/display.h"

#include "../ui/boot.h"
#include "../ui/ui.h"
#include "../ui/navigation.h"
#include "../ui/screens.h"

#include "../model/contato.h"

#include "../teclado/teclado.h"
#include "../teclado/editor.h"
#include "../teclado/t9.h"
#include "../teclado/entrada.h"


/* =========================================================
   INSTÂNCIAS DO SISTEMA
========================================================= */

Dispatcher dispatcher;

Teclado teclado;

Editor editor;

EditorT9 t9;


/* =========================================================
   ESTADO TEMPORÁRIO DO LoRa SIMULADO
========================================================= */

unsigned long respostaTempo = 0;

bool respostaPendente = false;


/* =========================================================
   INICIALIZAÇÃO
========================================================= */

void sistemaInicializar()
{
    // -----------------------------------------------------
    // LOGGER
    // -----------------------------------------------------

    logger.begin(115200);

    LOG_INFO(
        "SISTEMA",
        "NexusCom iniciando"
    );


    // -----------------------------------------------------
    // COMANDOS SERIAL
    // -----------------------------------------------------

    commandManager.begin();


    // -----------------------------------------------------
    // DISPLAY
    // -----------------------------------------------------

    initDisplay();

    LOG_INFO(
        "DISPLAY",
        "ST7789 inicializado"
    );

    bootAnimation();


    // -----------------------------------------------------
    // TECLADO
    // -----------------------------------------------------

    teclado.iniciar();

    LOG_INFO(
        "TECLADO",
        "Teclado inicializado"
    );


    // -----------------------------------------------------
    // ESTADO DO SISTEMA
    // -----------------------------------------------------

    sistemaInicializarEstado();


    // -----------------------------------------------------
    // INTERFACE INICIAL
    // -----------------------------------------------------

    drawHomeScreen();

    addRX(
        "Sistema iniciado"
    );

    drawEditor(
        "",
        sistema.modoNumerico
    );


    LOG_INFO(
        "SISTEMA",
        "Inicializacao concluida"
    );
}


/* =========================================================
   ENVIO SIMULADO
========================================================= */

static void processarEnvio(char tecla)
{
    if(tecla != '#')
    {
        return;
    }


    if(telaAtual != TELA_MENSAGENS)
    {
        return;
    }


    if(editor.vazio())
    {
        return;
    }


    addTX(
        editor.obter()
    );


    Evento evento;

    evento.tipo =
        EVENTO_TX;

    evento.tecla =
        0;


    dispatcher.adicionar(
        evento
    );


    respostaTempo =
        millis();

    respostaPendente =
        true;


    editor.limpar();

    t9.confirmar();


    drawEditor(
        editor.obter(),
        sistema.modoNumerico
    );
}


/* =========================================================
   LoRa SIMULADO
========================================================= */

static void processarLoRaSimulado()
{
    if(!respostaPendente)
    {
        return;
    }


    if(
        millis() - respostaTempo <= 2000
    )
    {
        return;
    }


    addRX(
        "ACK"
    );


    Evento evento;

    evento.tipo =
        EVENTO_RX;

    evento.tecla =
        0;


    dispatcher.adicionar(
        evento
    );


    respostaPendente =
        false;
}


/* =========================================================
   CICLO PRINCIPAL
========================================================= */

void sistemaAtualizar()
{
    char tecla =
        teclado.ler();


    // =====================================================
    // ENTRADA DO TECLADO
    // =====================================================

    if(tecla)
    {
        ResultadoNavegacao resultado =
            processarNavegacao(
                tecla,
                editor,
                sistema.modoNumerico
            );


        if(
            resultado != NAVEGACAO_NENHUMA
        )
        {
            if(
                resultado == NAVEGACAO_CONTATO
            )
            {
                Evento evento;

                evento.tipo =
                    EVENTO_CONTATO_TROCADO;

                evento.tecla =
                    tecla;


                dispatcher.adicionar(
                    evento
                );
            }
        }
        else
        {
            bool processada =
                processarEntradaMensagem(
                    tecla,
                    editor,
                    t9,
                    sistema.modoNumerico
                );


            if(!processada)
            {
                processarEnvio(
                    tecla
                );
            }
        }
    }


    // =====================================================
    // COMUNICAÇÃO LoRa SIMULADA
    // =====================================================

    processarLoRaSimulado();


    // =====================================================
    // DISPATCHER
    // =====================================================

    dispatcher.processar();


    // =====================================================
    // COMANDOS SERIAL
    // =====================================================

    commandManager.process();
}