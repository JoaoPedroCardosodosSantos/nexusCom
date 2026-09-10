#ifndef MENSAGEM_SERVICE_H
#define MENSAGEM_SERVICE_H

#include "filaMensagem.h"
#include "../transporte/transporte.h"
#include "../core/debug/logger.h"

class MensagemService
{
private:

    FilaMensagem filaSaida;

    FilaMensagem filaEntrada;

    Transporte* transporte;


public:

    MensagemService();

    void definirTransporte(
        Transporte* transporte
    );

    bool enviar(
        const Mensagem& mensagem
    );

    bool receber(
        const Mensagem& mensagem
    );

    bool obterSaida(
        Mensagem& mensagem
    );

    bool obterEntrada(
        Mensagem& mensagem
    );

    bool possuiMensagensSaida() const;

    bool possuiMensagensEntrada() const;

    int quantidadeSaida() const;

    int quantidadeEntrada() const;

    void atualizar();

    void limpar();
};

#endif