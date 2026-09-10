#ifndef LOOPBACK_H
#define LOOPBACK_H

#include "transporte.h"

class Loopback : public Transporte
{
private:

    Mensagem mensagem;

    bool pendente;

public:

    Loopback();

    bool enviar(
        const Mensagem& mensagem
    ) override;

    bool receber(
        Mensagem& mensagem
    ) override;

    bool disponivel() const override;

    void atualizar() override;
};

#endif