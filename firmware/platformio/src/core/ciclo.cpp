#include "ciclo.h"

#include <Arduino.h>

#include "sistema.h"
#include "dispatcher.h"

#include "debug/logger.h"
#include "serial/commandManager.h"

#include "../display/display.h"

#include "../ui/boot.h"
#include "../ui/ui.h"

#include "../teclado/teclado.h"
#include "../teclado/editor.h"
#include "../teclado/t9.h"


// =========================================================
// INSTÂNCIAS DO SISTEMA
// =========================================================

Dispatcher dispatcher;
Teclado teclado;
Editor editor;
EditorT9 t9;


// =========================================================
// ESTADO TEMPORÁRIO DA SIMULAÇÃO LoRa
// =========================================================

unsigned long respostaTempo = 0;
bool respostaPendente = false;


// =========================================================
// INICIALIZAÇÃO
// =========================================================

void sistemaInicializar()
{
    logger.begin(115200);

    LOG_INFO(
        "SISTEMA",
        "NexusCom iniciando"
    );

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
    // INTERFACE INICIAL
    // -----------------------------------------------------

    sistemaInicializarEstado();

    drawHomeScreen();

    addRX("Sistema iniciado");

    drawEditor(
        "",
        sistema.modoNumerico
    );


    LOG_INFO(
        "SISTEMA",
        "Inicializacao concluida"
    );
}


// =========================================================
// ATUALIZAÇÃO
// =========================================================

void sistemaAtualizar()
{
    char tecla = teclado.ler();

    /*
     * A lógica atual do loop ainda permanece aqui
     * temporariamente.
     *
     * Nas próximas etapas vamos retirar gradualmente
     * cada responsabilidade deste bloco.
     */

    if(tecla)
    {
        // A lógica atual será movida para módulos
        // específicos nas próximas etapas.
    }


    // -----------------------------------------------------
    // PROCESSAMENTO DOS EVENTOS
    // -----------------------------------------------------

    dispatcher.processar();


    // -----------------------------------------------------
    // COMANDOS SERIAL
    // -----------------------------------------------------

    commandManager.process();
}