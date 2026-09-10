#ifndef MENSAGEM_SERVICE_H
#define MENSAGEM_SERVICE_H

#include "filaMensagem.h"


class MensagemService
{
private:

    FilaMensagem filaSaida;

    FilaMensagem filaEntrada;

public:

    MensagemService();

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

    bool processarLoopback();

    void limpar();
};

#endif