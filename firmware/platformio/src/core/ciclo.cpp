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

#include "../mensagens/mensagemService.h"
#include "../model/mensagem.h"


/* =========================================================
   INSTÂNCIAS DO SISTEMA
========================================================= */

Dispatcher dispatcher;

Teclado teclado;

Editor editor;

EditorT9 t9;

MensagemService mensagemService;

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


    Mensagem mensagem = {};

    strncpy(
        mensagem.texto,
        editor.obter(),
        sizeof(mensagem.texto) - 1
    );

    mensagem.texto[
        sizeof(mensagem.texto) - 1
    ] = '\0';


    mensagem.remetente = 0;

    mensagem.destinatario =
        sistema.contatoSelecionado;

    mensagem.confirmada = false;


    if(
        !mensagemService.enviar(
            mensagem
        )
    )
    {
        LOG_INFO(
            "MENSAGEM",
            "Fila de saida cheia"
        );

        return;
    }


    addTX(
        mensagem.texto
    );


    Evento evento;

    evento.tipo =
        EVENTO_TX;

    evento.tecla =
        0;


    dispatcher.adicionar(
        evento
    );


    editor.limpar();

    t9.confirmar();


    drawEditor(
        editor.obter(),
        sistema.modoNumerico
    );
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
    // DISPATCHER
    // =====================================================

    dispatcher.processar();

    if(mensagemService.processarLoopback())
{
    Mensagem mensagem;

    if(mensagemService.obterEntrada(mensagem))
    {
        addRX(
            mensagem.texto
        );

        Evento evento;

        evento.tipo =
            EVENTO_RX;

        evento.tecla =
            0;

        dispatcher.adicionar(
            evento
        );
    }
}


    // =====================================================
    // COMANDOS SERIAL
    // =====================================================

    commandManager.process();
}