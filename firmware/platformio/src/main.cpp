#include <Arduino.h>

#include "display/display.h"

#include "ui/ui.h"
#include "ui/menu.h"
#include "ui/screens.h"

#include "ui/screens/contatos.h"
#include "ui/screens/configuracoes.h"
#include "ui/screens/status.h"
#include "ui/screens/sobre.h"

#include "teclado/teclado.h"
#include "teclado/editor.h"
#include "teclado/t9.h"

Teclado teclado;
Editor editor;
T9 t9;

unsigned long respostaTempo = 0;
bool respostaPendente = false;

void setup()
{
    initDisplay();

    teclado.iniciar();

    drawHomeScreen();

    drawEditor("");
}

void loop()
{
    char tecla = teclado.ler();

    if(tecla)
    {
        // MENU
        if(tecla == 'D')
        {
            if(telaAtual == TELA_MENU)
            {
                telaAtual = TELA_MENSAGENS;

                drawHomeScreen();

                drawEditor(
                    editor.obter()
                );
            }
            else
            {
                telaAtual = TELA_MENU;

                drawMenu();
            }

            return;
        }

        // SELEÇÃO DE TELAS
        if(telaAtual == TELA_MENU)
        {
            if(tecla == '1')
            {
                telaAtual = TELA_MENSAGENS;

                drawHomeScreen();

                drawEditor(
                    editor.obter()
                );
            }

            else if(tecla == '2')
            {
                telaAtual = TELA_CONTATOS;

                drawContatos();
            }

            else if(tecla == '3')
            {
                telaAtual = TELA_CONFIGURACOES;

                drawConfiguracoes();
            }

            else if(tecla == '4')
            {
                telaAtual = TELA_STATUS;

                drawStatus();
            }

            else if(tecla == '5')
            {
                telaAtual = TELA_SOBRE;

                drawSobre();
            }

            return;
        }

        // Apenas tela de mensagens aceita digitação
        if(telaAtual == TELA_MENSAGENS)
        {
            if(tecla >= '1' && tecla <= '9')
            {
                bool mesma =
                    t9.mesmaSequencia(tecla);

                char letra =
                    t9.converter(tecla);

                if(mesma)
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

                drawEditor(
                    editor.obter()
                );
            }

            else if(tecla == '*')
            {
                editor.apagarUltimo();

                t9.confirmar();

                drawEditor(
                    editor.obter()
                );
            }

            else if(tecla == '0')
            {
                editor.espaco();

                t9.confirmar();

                drawEditor(
                    editor.obter()
                );
            }

            else if(tecla == '#')
            {
                if(!editor.vazio())
                {
                    addTX(
                        editor.obter()
                    );

                    respostaTempo =
                        millis();

                    respostaPendente =
                        true;

                    editor.limpar();

                    t9.confirmar();

                    drawEditor(
                        editor.obter()
                    );
                }
            }
        }
    }

    // Simulação de resposta LoRa
    if(
        respostaPendente &&
        millis() - respostaTempo > 2000
    )
    {
        addRX("ACK");

        respostaPendente = false;
    }
}