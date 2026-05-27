#include "teclado.h"

#include "keymap.h"

Teclado::Teclado() :

pcf(0x20)

{
    estadoAnterior=false;
}

void Teclado::iniciar()
{
    pcf.iniciar();
}

bool Teclado::pressionado()
{
    for(int linha=0; linha<4; linha++)
    {
        uint8_t estado=0xFF;

        estado &= ~(1<<linha);

        pcf.escrever(estado);

        delayMicroseconds(100);

        uint8_t leitura=
            pcf.ler();

        for(int coluna=0; coluna<4; coluna++)
        {
            int bit=coluna+4;

            if(
                !(leitura &
                (1<<bit))
            )
            {
                return true;
            }
        }
    }

    return false;
}

char Teclado::ler()
{
    bool atual=
        pressionado();

    if(
        atual &&
        estadoAnterior
    )
    {
        return 0;
    }

    if(
        !atual
    )
    {
        estadoAnterior=false;

        return 0;
    }

    estadoAnterior=true;

    for(int linha=0; linha<4; linha++)
    {
        uint8_t estado=0xFF;

        estado &= ~(1<<linha);

        pcf.escrever(estado);

        delayMicroseconds(100);

        uint8_t leitura=
            pcf.ler();

        for(int coluna=0; coluna<4; coluna++)
        {
            int bit=coluna+4;

            if(
                !(leitura &
                (1<<bit))
            )
            {
                return mapa[
                    linha
                ][
                    coluna
                ];
            }
        }
    }

    return 0;
}