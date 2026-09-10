#ifndef SISTEMA_H
#define SISTEMA_H

#include <stdint.h>

struct Sistema
{
    bool iniciado;
    bool modoNumerico;
    uint8_t contatoSelecionado;
    uint16_t rxCount;
    uint16_t txCount;
};

extern Sistema sistema;

void sistemaInicializarEstado();

#endif