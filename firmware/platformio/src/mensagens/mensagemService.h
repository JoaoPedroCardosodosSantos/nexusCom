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


    // -----------------------------------------------------
    // ENVIO
    // -----------------------------------------------------

    bool enviar(
        const Mensagem& mensagem
    );


    // -----------------------------------------------------
    // RECEBIMENTO
    // -----------------------------------------------------

    bool receber(
        const Mensagem& mensagem
    );


    // -----------------------------------------------------
    // LEITURA DAS FILAS
    // -----------------------------------------------------

    bool obterSaida(
        Mensagem& mensagem
    );

    bool obterEntrada(
        Mensagem& mensagem
    );


    // -----------------------------------------------------
    // ESTADO
    // -----------------------------------------------------

    bool possuiMensagensSaida() const;

    bool possuiMensagensEntrada() const;

    int quantidadeSaida() const;

    int quantidadeEntrada() const;


    // -----------------------------------------------------
    // LIMPEZA
    // -----------------------------------------------------

    void limpar();
};

#endif