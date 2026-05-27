#ifndef PCF8574_H
#define PCF8574_H

#include <Arduino.h>

#include <Wire.h>

class PCF8574
{
private:

    uint8_t endereco;

public:

    PCF8574(uint8_t addr);

    void iniciar();

    void escrever(
        uint8_t valor
    );

    uint8_t ler();
};

#endif