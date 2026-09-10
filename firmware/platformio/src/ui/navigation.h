#ifndef NAVIGATION_H
#define NAVIGATION_H

#include "../teclado/editor.h"

enum ResultadoNavegacao
{
    NAVEGACAO_NENHUMA,
    NAVEGACAO_CONSUMIDA,
    NAVEGACAO_CONTATO
};

ResultadoNavegacao processarNavegacao(
    char tecla,
    Editor& editor,
    bool modoNumerico
);

#endif