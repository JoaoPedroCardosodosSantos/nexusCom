#ifndef TRANSPORTE_H
#define TRANSPORTE_H

#include "../model/mensagem.h"

class Transporte
{
public:

    virtual ~Transporte() {}

    virtual bool enviar(
        const Mensagem& mensagem
    ) = 0;

    virtual bool receber(
        Mensagem& mensagem
    ) = 0;

    virtual bool disponivel() const = 0;

    virtual void atualizar() = 0;
};

#endif