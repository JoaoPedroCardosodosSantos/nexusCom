#include "loraService.h"

#include <Arduino.h>

LoRaService::LoRaService()
{
    transmitindo=false;

    inicioTX=0;
}

bool LoRaService::ocupado()
{
    return transmitindo;
}

void LoRaService::enviar(
    Mensagem msg
)
{
    atual=msg;

    transmitindo=true;

    inicioTX=millis();

    Serial.print(
        "TX -> "
    );

    Serial.println(
        atual.texto
    );
}

void LoRaService::atualizar()
{
    if(!transmitindo)
        return;

    if(
        millis()-inicioTX
        >2000
    )
    {
        Serial.print(
            "ACK <- "
        );

        Serial.println(
            atual.texto
        );

        transmitindo=false;
    }
}