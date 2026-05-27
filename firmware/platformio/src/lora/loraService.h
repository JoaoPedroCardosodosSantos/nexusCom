#ifndef LORA_SERVICE_H
#define LORA_SERVICE_H

#include <Arduino.h>

#include "../mensagens/mensagem.h"

class LoRaService
{
private:

    bool transmitindo;

    uint32_t inicioTX;

    Mensagem atual;

public:

    LoRaService();

    bool ocupado();

    void enviar(
        Mensagem msg
    );

    void atualizar();
};

#endif