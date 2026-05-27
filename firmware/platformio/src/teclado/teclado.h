#ifndef TECLADO_H
#define TECLADO_H

#include <Arduino.h>

#include "pcf8574.h"

class Teclado
{
private:

    PCF8574 pcf;

    bool estadoAnterior;

public:

    Teclado();

    void iniciar();

    char ler();

    bool pressionado();
};

#endif