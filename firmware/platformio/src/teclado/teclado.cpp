#include "teclado.h"

#include "../config/pinos.h"

#include "keymap.h"

Teclado::Teclado()
{
    linhas[0] = LINHA1;
    linhas[1] = LINHA2;
    linhas[2] = LINHA3;
    linhas[3] = LINHA4;

    colunas[0] = COLUNA1;
    colunas[1] = COLUNA2;
    colunas[2] = COLUNA3;
    colunas[3] = COLUNA4;
}

void Teclado::iniciar()
{
    for(int i=0;i<4;i++)
    {
        pinMode(
            linhas[i],
            OUTPUT
        );

        digitalWrite(
            linhas[i],
            HIGH
        );
    }

    for(int i=0;i<4;i++)
    {
        pinMode(
            colunas[i],
            INPUT_PULLUP
        );
    }
}

char Teclado::ler()
{
    for(int l=0;l<4;l++)
    {
        digitalWrite(
            linhas[l],
            LOW
        );

        for(int c=0;c<4;c++)
        {
            if(
                digitalRead(
                    colunas[c]
                ) == LOW
            )
            {
                digitalWrite(
                    linhas[l],
                    HIGH
                );

                return mapa[l][c];
            }
        }

        digitalWrite(
            linhas[l],
            HIGH
        );
    }

    return 0;
}