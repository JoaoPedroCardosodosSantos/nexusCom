#ifndef DISPATCHER_H
#define DISPATCHER_H

#include "../eventos/evento.h"
#include "fila.h"

class Dispatcher
{
private:

    FilaCircular<Evento, 32> fila;

public:

    bool adicionar(
        const Evento& evento
    );

    void processar();
};

#endif