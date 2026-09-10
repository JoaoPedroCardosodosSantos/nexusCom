#include "mensagemService.h"


/* =========================================================
   CONSTRUTOR
========================================================= */

MensagemService::MensagemService()
{
}


/* =========================================================
   ENVIAR
========================================================= */

bool MensagemService::enviar(
    const Mensagem& mensagem
)
{
    return filaSaida.adicionar(
        mensagem
    );
}


/* =========================================================
   RECEBER
========================================================= */

bool MensagemService::receber(
    const Mensagem& mensagem
)
{
    return filaEntrada.adicionar(
        mensagem
    );
}


/* =========================================================
   OBTER SAÍDA
========================================================= */

bool MensagemService::obterSaida(
    Mensagem& mensagem
)
{
    return filaSaida.obter(
        mensagem
    );
}


/* =========================================================
   OBTER ENTRADA
========================================================= */

bool MensagemService::obterEntrada(
    Mensagem& mensagem
)
{
    return filaEntrada.obter(
        mensagem
    );
}


/* =========================================================
   POSSUI SAÍDA
========================================================= */

bool MensagemService::possuiMensagensSaida() const
{
    return !filaSaida.vazia();
}


/* =========================================================
   POSSUI ENTRADA
========================================================= */

bool MensagemService::possuiMensagensEntrada() const
{
    return !filaEntrada.vazia();
}


/* =========================================================
   QUANTIDADE DE SAÍDA
========================================================= */

int MensagemService::quantidadeSaida() const
{
    return filaSaida.tamanho();
}


/* =========================================================
   QUANTIDADE DE ENTRADA
========================================================= */

int MensagemService::quantidadeEntrada() const
{
    return filaEntrada.tamanho();
}


/* =========================================================
   LIMPAR
========================================================= */

void MensagemService::limpar()
{
    filaSaida.limpar();

    filaEntrada.limpar();
}