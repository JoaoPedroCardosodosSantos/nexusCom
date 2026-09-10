#include "sistema.h"

Sistema sistema =
{
    false,  // iniciado
    false,  // modoNumerico
    0,      // contato selecionado
    0,      // RX
    0       // TX
};


void sistemaInicializarEstado()
{
    sistema.iniciado = true;
    sistema.modoNumerico = false;
    sistema.contatoSelecionado = 0;
    sistema.rxCount = 0;
    sistema.txCount = 0;
}