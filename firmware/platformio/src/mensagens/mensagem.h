#ifndef MENSAGEM_H
#define MENSAGEM_H

struct Mensagem
{
    char texto[65];

    int remetente;

    int destinatario;

    bool confirmada;
};

#endif