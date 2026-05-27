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

    const char* obter();
};

#endif