#ifndef EVENTO_H
#define EVENTO_H

enum TipoEvento
{
    EVENTO_NENHUM,

    EVENTO_TECLA,

    EVENTO_TX,

    EVENTO_RX,

    EVENTO_CONTATO_TROCADO
};

struct Evento
{
    TipoEvento tipo;

    char tecla;
};

#endif