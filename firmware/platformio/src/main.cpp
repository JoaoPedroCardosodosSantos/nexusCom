#include <Arduino.h>

#include "teclado/teclado.h"

#include "teclado/t9.h"

#include "teclado/editor.h"

Teclado teclado;

T9 t9;

Editor editor;

void setup()
{
    Serial.begin(9600);

    teclado.iniciar();
}

void loop()
{
    char tecla=
        teclado.ler();

    if(!tecla)
        return;

    if(
        tecla>='2' &&
        tecla<='9'
    )
    {
        bool repetir=
            t9.mesmaSequencia(
                tecla
            );

        char letra=
            t9.converter(
                tecla
            );

        if(repetir)
        {
            editor.substituirUltimo(
                letra
            );
        }
        else
        {
            editor.inserir(
                letra
            );
        }

        Serial.print(
            "MSG: "
        );

        Serial.println(
            editor.obter()
        );
    }
}