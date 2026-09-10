#include "filaMensagem.h"


/* =========================================================
   CONSTRUTOR
========================================================= */

FilaMensagem::FilaMensagem()
{
    inicio = 0;

    fim = 0;

    quantidade = 0;
}


/* =========================================================
   ADICIONAR
========================================================= */

bool FilaMensagem::adicionar(
    const Mensagem& mensagem
)
{
    if(cheia())
    {
        return false;
    }


    fila[fim] = mensagem;


    fim++;

    if(
        fim >= FILA_MENSAGENS_CAPACIDADE
    )
    {
        fim = 0;
    }


    quantidade++;

    return true;
}


/* =========================================================
   OBTER
========================================================= */

bool FilaMensagem::obter(
    Mensagem& mensagem
)
{
    if(vazia())
    {
        return false;
    }


    mensagem = fila[inicio];


    inicio++;

    if(
        inicio >= FILA_MENSAGENS_CAPACIDADE
    )
    {
        inicio = 0;
    }


    quantidade--;

    return true;
}


/* =========================================================
   VAZIA
========================================================= */

bool FilaMensagem::vazia() const
{
    return quantidade == 0;
}


/* =========================================================
   CHEIA
========================================================= */

bool FilaMensagem::cheia() const
{
    return quantidade >=
           FILA_MENSAGENS_CAPACIDADE;
}


/* =========================================================
   TAMANHO
========================================================= */

int FilaMensagem::tamanho() const
{
    return quantidade;
}


/* =========================================================
   LIMPAR
========================================================= */

void FilaMensagem::limpar()
{
    inicio = 0;

    fim = 0;

    quantidade = 0;
}