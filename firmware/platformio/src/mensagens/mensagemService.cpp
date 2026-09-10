#include "mensagemService.h"

MensagemService::MensagemService()
{
    lora = nullptr;
}

void MensagemService::iniciar(
    LoRaService* servicoLoRa
)
{
    lora = servicoLoRa;
}

bool MensagemService::enviar(
    Mensagem msg
)
{
    if(lora == nullptr)
        return false;

    if(lora->ocupado())
        return false;

    return fila.adicionar(
        msg
    );
}

void MensagemService::atualizar()
{
    if(lora == nullptr)
        return;

    lora->atualizar();

    if(lora->ocupado())
        return;

    Mensagem msg;

    if(
        fila.obter(msg)
    )
    {
        lora->enviar(
            msg
        );
    }
}