#ifndef TECLADO_H
#define TECLADO_H

#include <Arduino.h>

class Teclado
{
private:

    byte linhas[4];

    byte colunas[4];

public:

    Teclado();

    void iniciar();

    char ler();
};

#endif