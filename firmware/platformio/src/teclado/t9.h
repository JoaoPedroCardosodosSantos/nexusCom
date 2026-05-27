#ifndef T9_H
#define T9_H

#include <Arduino.h>

class T9
{
private:

    char ultimaTecla;

    uint8_t indice;

    uint32_t ultimoTempo;

public:

    T9();

    bool mesmaSequencia(char tecla);

    char converter(char tecla);
};

#endif