#include "editor.h"

Editor::Editor()
{
    cursor=0;

    texto[0]='\0';
}

void Editor::inserir(char c)
{
    if(cursor>=64)
        return;

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

void Editor::apagarUltimo()
{
    if(cursor<=0)
        return;

    cursor--;

    texto[cursor]='\0';
}

void Editor::limpar()
{
    cursor=0;

    texto[0]='\0';
}

void Editor::espaco()
{
    inserir(' ');
}

bool Editor::vazio()
{
    return cursor==0;
}

const char* Editor::obter()
{
    return texto;
}