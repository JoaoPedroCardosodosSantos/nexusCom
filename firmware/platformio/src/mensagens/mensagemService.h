#ifndef MENSAGEM_SERVICE_H
#define MENSAGEM_SERVICE_H

#include "mensagem.h"
#include "filaMensagem.h"

#include "../lora/loraService.h"

class MensagemService
{
private:

    FilaMensagem fila;

    LoRaService* lora;

public:

    MensagemService();

    void iniciar(
        LoRaService* servicoLoRa
    );

    bool enviar(
        Mensagem msg
    );

    void atualizar();
};

#endif