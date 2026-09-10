#include "dispatcher.h"

#include <Arduino.h>


/* =========================================================
   ADICIONAR EVENTO
========================================================= */

bool Dispatcher::adicionar(
    const Evento& evento
)
{
    return fila.push(
        evento
    );
}


/* =========================================================
   PROCESSAR EVENTOS
========================================================= */

void Dispatcher::processar()
{
    Evento evento;


    while(
        fila.pop(evento)
    )
    {
        switch(evento.tipo)
        {
            // ---------------------------------------------
            // NENHUM
            // ---------------------------------------------

            case EVENTO_NENHUM:

                break;


            // ---------------------------------------------
            // TECLA
            // ---------------------------------------------

            case EVENTO_TECLA:

                Serial.print(
                    "EVENTO TECLA: "
                );

                Serial.println(
                    evento.tecla
                );

                break;


            // ---------------------------------------------
            // TX
            // ---------------------------------------------

            case EVENTO_TX:

                Serial.println(
                    "EVENTO TX"
                );

                break;


            // ---------------------------------------------
            // RX
            // ---------------------------------------------

            case EVENTO_RX:

                Serial.println(
                    "EVENTO RX"
                );

                break;


            // ---------------------------------------------
            // CONTATO
            // ---------------------------------------------

            case EVENTO_CONTATO_TROCADO:

                Serial.println(
                    "EVENTO CONTATO"
                );

                break;


            // ---------------------------------------------
            // MENSAGEM ENVIADA
            // ---------------------------------------------

            case EVENTO_MENSAGEM_ENVIADA:

                Serial.println(
                    "EVENTO MENSAGEM ENVIADA"
                );

                break;


            // ---------------------------------------------
            // MENSAGEM RECEBIDA
            // ---------------------------------------------

            case EVENTO_MENSAGEM_RECEBIDA:

                Serial.println(
                    "EVENTO MENSAGEM RECEBIDA"
                );

                break;


            // ---------------------------------------------
            // ACK
            // ---------------------------------------------

            case EVENTO_ACK:

                Serial.println(
                    "EVENTO ACK"
                );

                break;


            // ---------------------------------------------
            // DESCONHECIDO
            // ---------------------------------------------

            default:

                Serial.println(
                    "EVENTO DESCONHECIDO"
                );

                break;
        }
    }
}