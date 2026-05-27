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
        Serial.println(
            e.tecla
        );
    }
}