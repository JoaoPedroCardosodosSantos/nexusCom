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
   PROCESSAMENTO DE MENSAGENS
========================================================= */

static void processarMensagem(char tecla)
{
    if(telaAtual != TELA_MENSAGENS)
    {
        return;
    }


    // =====================================================
    // TECLAS 1-9
    // =====================================================

    if(
        tecla >= '1' &&
        tecla <= '9'
    )
    {
        if(sistema.modoNumerico)
        {
            editor.inserir(
                tecla
            );

            t9.confirmar();

            drawEditor(
                editor.obter(),
                sistema.modoNumerico
            );
        }
        else
        {
            bool mesma =
                t9.mesmaSequencia(
                    tecla
                );

            char letra =
                t9.converter(
                    tecla
                );


            if(mesma)
            {
                editor.substituirUltimo(
                    letra
                );
            }
            else
            {
                editor.inserir(
                    letra
                );
            }


            drawEditor(
                editor.obter(),
                sistema.modoNumerico
            );
        }

        return;
    }


    // =====================================================
    // * — MODO NUMÉRICO
    // =====================================================

    if(tecla == '*')
    {
        sistema.modoNumerico =
            !sistema.modoNumerico;

        t9.confirmar();

        drawEditor(
            editor.obter(),
            sistema.modoNumerico
        );

        return;
    }


    // =====================================================
    // 0 — ESPAÇO / ZERO
    // =====================================================

    if(tecla == '0')
    {
        if(sistema.modoNumerico)
        {
            editor.inserir(
                '0'
            );
        }
        else
        {
            editor.espaco();
        }

        t9.confirmar();

        drawEditor(
            editor.obter(),
            sistema.modoNumerico
        );

        return;
    }


    // =====================================================
    // # — ENVIAR
    // =====================================================

    if(tecla == '#')
    {
        if(!editor.vazio())
        {
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

        return;
    }


    // =====================================================
    // C — APAGAR
    // =====================================================

    if(tecla == 'C')
    {
        editor.apagarUltimo();

        t9.confirmar();

        drawEditor(
            editor.obter(),
            sistema.modoNumerico
        );

        return;
    }
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


        // -------------------------------------------------
        // TECLA CONSUMIDA PELA NAVEGAÇÃO
        // -------------------------------------------------

        if(
            resultado != NAVEGACAO_NENHUMA
        )
        {
            // ---------------------------------------------
            // TROCA DE CONTATO
            // ---------------------------------------------

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


            return;
        }


        // -------------------------------------------------
        // PROCESSAMENTO DE MENSAGEM
        // -------------------------------------------------

        processarMensagem(
            tecla
        );
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