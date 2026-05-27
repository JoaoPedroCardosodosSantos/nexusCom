#ifndef FILA_MENSAGEM_H
#define FILA_MENSAGEM_H

#include "mensagem.h"

class FilaMensagem
{
private:

    Mensagem fila[10];

    int inicio;

    int fim;

    int quantidade;

public:

    FilaMensagem();

    bool adicionar(
        Mensagem msg
    );

    bool obter(
        Mensagem &msg
    );

    int tamanho();
};

#endif