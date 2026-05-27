#ifndef EDITOR_H
#define EDITOR_H

class Editor
{
private:

    char texto[65];

    int cursor;

public:

    Editor();

    void inserir(char c);

    void substituirUltimo(char c);

    void apagarUltimo();

    void limpar();

    void espaco();

    const char* obter();
};

#endif