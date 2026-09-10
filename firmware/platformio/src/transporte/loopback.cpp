#include "loopback.h"


Loopback::Loopback()
{
    pendente = false;
}


bool Loopback::enviar(
    const Mensagem& novaMensagem
)
{
    if(pendente)
    {
        return false;
    }

    mensagem = novaMensagem;

    pendente = true;

    return true;
}


bool Loopback::receber(
    Mensagem& destino
)
{
    if(!pendente)
    {
        return false;
    }

    destino = mensagem;

    pendente = false;

    return true;
}


bool Loopback::disponivel() const
{
    return !pendente;
}


void Loopback::atualizar()
{
}