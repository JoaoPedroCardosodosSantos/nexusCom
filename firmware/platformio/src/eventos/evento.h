#ifndef EVENTO_H
#define EVENTO_H

enum TipoEvento
{
    EVENTO_NENHUM,

    EVENTO_TECLA,

    EVENTO_TX,

    EVENTO_RX,

    EVENTO_CONTATO_TROCADO,

    EVENTO_MENSAGEM_ENVIADA,

    EVENTO_MENSAGEM_RECEBIDA,

    EVENTO_ACK
};


struct Evento
{
    TipoEvento tipo;

    char tecla;
};


#endif