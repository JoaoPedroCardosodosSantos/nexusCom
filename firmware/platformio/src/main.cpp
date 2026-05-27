#include <Arduino.h>

#include <string.h>

#include "teclado/teclado.h"

#include "teclado/t9.h"

#include "teclado/editor.h"

#include "mensagens/mensagem.h"

#include "mensagens/filaMensagem.h"

Teclado teclado;

T9 t9;

Editor editor;

FilaMensagem filaEnvio;

void mostrarMensagem()
{
    Serial.print(
        "MSG: "
    );

    Serial.println(
        editor.obter()
    );
}

void enviarMensagem()
{
    if(
        editor.vazio()
    )
    {
        Serial.println(
            "MSG VAZIA"
        );

        return;
    }

    Mensagem msg;

    strcpy(
        msg.texto,
        editor.obter()
    );

    msg.remetente=1;

    msg.destinatario=2;

    msg.confirmada=false;

    if(
        filaEnvio.adicionar(
            msg
        )
    )
    {
        Serial.print(
            "ENVIADA: "
        );

        Serial.println(
            msg.texto
        );

        editor.limpar();

        t9.confirmar();
    }
    else
    {
        Serial.println(
            "FILA CHEIA"
        );
    }
}

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

        if(
            repetir &&
            !editor.vazio()
        )
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

        mostrarMensagem();

        return;
    }

    switch(tecla)
    {
        case '#':
        {
            t9.confirmar();

            Serial.println(
                "CONFIRMADO"
            );

            break;
        }

        case '*':
        {
            editor.apagarUltimo();

            mostrarMensagem();

            break;
        }

        case '0':
        {
            t9.confirmar();

            editor.espaco();

            mostrarMensagem();

            break;
        }

        case 'B':
        {
            t9.confirmar();

            editor.limpar();

            mostrarMensagem();

            break;
        }

        case 'A':
        {
            enviarMensagem();

            break;
        }
    }
}