#ifndef FILA_MENSAGEM_H
#define FILA_MENSAGEM_H

#include "../model/mensagem.h"

#define FILA_MENSAGENS_CAPACIDADE 64

class FilaMensagem
{
private:

    Mensagem fila[FILA_MENSAGENS_CAPACIDADE];

    int inicio;

    int fim;

    int quantidade;

public:

    FilaMensagem();

    bool adicionar(
        const Mensagem& mensagem
    );

    bool obter(
        Mensagem& mensagem
    );

    bool vazia() const;

    bool cheia() const;

    int tamanho() const;

    void limpar();
};

#endif