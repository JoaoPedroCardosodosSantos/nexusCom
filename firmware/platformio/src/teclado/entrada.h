#ifndef ENTRADA_H
#define ENTRADA_H

#include "editor.h"
#include "t9.h"

bool processarEntradaMensagem(
    char tecla,
    Editor& editor,
    EditorT9& t9,
    bool& modoNumerico
);

#endif