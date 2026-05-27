#ifndef FILA_H
#define FILA_H

template<typename T,int TAM>

class FilaCircular
{
private:

    T dados[TAM];

    int inicio;

    int fim;

    int quantidade;

public:

    FilaCircular()
    {
        inicio=0;
        fim=0;
        quantidade=0;
    }

    bool push(T item)
    {
        if(quantidade>=TAM)
            return false;

        dados[fim]=item;

        fim=(fim+1)%TAM;

        quantidade++;

        return true;
    }

    bool pop(T &item)
    {
        if(quantidade==0)
            return false;

        item=dados[inicio];

        inicio=(inicio+1)%TAM;

        quantidade--;

        return true;
    }
};

#endif