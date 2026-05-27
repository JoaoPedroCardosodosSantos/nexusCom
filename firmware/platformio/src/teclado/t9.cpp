#include "t9.h"

#define TEMPO_T9 700

const char* mapaT9[] =
{
    "",
    "",
    "ABC",
    "DEF",
    "GHI",
    "JKL",
    "MNO",
    "PQRS",
    "TUV",
    "WXYZ"
};

T9::T9()
{
    ultimaTecla=0;

    indice=0;

    ultimoTempo=0;
}

bool T9::mesmaSequencia(
    char tecla
)
{
    uint32_t agora=millis();

    if(
        tecla==ultimaTecla &&
        (agora-ultimoTempo)<TEMPO_T9
    )
    {
        indice++;

        ultimoTempo=agora;

        return true;
    }

    ultimaTecla=tecla;

    indice=0;

    ultimoTempo=agora;

    return false;
}

char T9::converter(char tecla)
{
    int n=tecla-'0';

    const char* grupo=
        mapaT9[n];

    int tam=
        strlen(grupo);

    if(tam==0)
        return 0;

    return grupo[
        indice%tam
    ];
}