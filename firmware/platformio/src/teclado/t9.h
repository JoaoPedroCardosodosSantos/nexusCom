#ifndef T9_H
#define T9_H

#include <Arduino.h>

class EditorT9
{
private:

    char ultimaTecla;

    uint8_t indice;

    uint32_t ultimoTempo;

    bool composicaoAtiva;

public:

    EditorT9();

    bool mesmaSequencia(char tecla);

    char converter(char tecla);

    void confirmar();

    bool emComposicao();
};

#endif