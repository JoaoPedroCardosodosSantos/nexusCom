#include "dispatcher.h"

#include <Arduino.h>

void Dispatcher::adicionar(
    Evento e
)
{
    fila.push(e);
}

void Dispatcher::processar()
{
    Evento e;

    while(
        fila.pop(e)
    )
    {
        switch(e.tipo)
        {
            case EVENTO_TECLA:

                Serial.print(
                    "TECLA: "
                );

                Serial.println(
                    e.tecla
                );

                break;

            case EVENTO_TX:

                Serial.println(
                    "TX"
                );

                break;

            case EVENTO_RX:

                Serial.println(
                    "RX"
                );

                break;

            case EVENTO_CONTATO_TROCADO:

                Serial.println(
                    "CONTATO"
                );

                break;

            default:

                break;
        }
    }
}