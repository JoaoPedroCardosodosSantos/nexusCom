#include "filaMensagem.h"

FilaMensagem::FilaMensagem()
{
    inicio = 0;
    fim = 0;
    quantidade = 0;
}

bool FilaMensagem::adicionar(
    Mensagem msg
)
{
    if(quantidade >= 10)
        return false;

    fila[fim] = msg;

    fim = (fim + 1) % 10;

    quantidade++;

    return true;
}

bool FilaMensagem::obter(
    Mensagem &msg
)
{
    if(quantidade == 0)
        return false;

    msg = fila[inicio];

    inicio = (inicio + 1) % 10;

    quantidade--;

    return true;
}

int FilaMensagem::tamanho()
{
    return quantidade;
}