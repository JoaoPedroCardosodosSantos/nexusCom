#ifndef CONTATO_H
#define CONTATO_H

#include <Arduino.h>

struct Contato
{
    const char* nome;
    uint8_t id;
};

extern Contato contatos[];

extern const uint8_t TOTAL_CONTATOS;

#endif