#include "editor.h"

Editor::Editor()
{
    cursor=0;

    texto[0]='\0';
}

void Editor::inserir(char c)
{
    texto[cursor]=c;

    cursor++;

    texto[cursor]='\0';
}

void Editor::substituirUltimo(
    char c
)
{
    if(cursor==0)
    {
        inserir(c);

        return;
    }

    texto[cursor-1]=c;
}

const char* Editor::obter()
{
    return texto;
}