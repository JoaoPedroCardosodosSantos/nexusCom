#include <Arduino.h>
#include "ui/boot.h"
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

bool modoNumerico = false;

unsigned long respostaTempo = 0;
bool respostaPendente = false;

void setup()
{
    initDisplay();

    bootAnimation();

    teclado.iniciar();

    drawHomeScreen();

    drawEditor(
        "",
        modoNumerico
    );
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
                    editor.obter(),
                    modoNumerico
                );
            }
            else
            {
                telaAtual = TELA_MENU;

                drawMenu();
            }

            return;
        }

        // Atalho Contatos
        if(tecla == 'A')
        {
            telaAtual = TELA_CONTATOS;

            drawContatos();

            return;
        }

        // Atalho Status LoRa
        if(tecla == 'B')
        {
            telaAtual = TELA_STATUS;

            drawStatus();

            return;
        }

        // Navegação do menu
        if(telaAtual == TELA_MENU)
        {
            if(tecla == '1')
            {
                telaAtual = TELA_MENSAGENS;

                drawHomeScreen();

                drawEditor(
                    editor.obter(),
                    modoNumerico
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

        // Digitação apenas na tela principal
        if(telaAtual == TELA_MENSAGENS)
        {
            // Alterna ABC / 123
            if(tecla == '*')
            {
                modoNumerico =
                    !modoNumerico;

                t9.confirmar();

                drawEditor(
                    editor.obter(),
                    modoNumerico
                );
            }

            // Espaço
            else if(tecla == '0')
            {
                editor.espaco();

                t9.confirmar();

                drawEditor(
                    editor.obter(),
                    modoNumerico
                );
            }

            // Apagar
            else if(tecla == 'C')
            {
                editor.apagarUltimo();

                t9.confirmar();

                drawEditor(
                    editor.obter(),
                    modoNumerico
                );
            }

            // Enviar
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
                        editor.obter(),
                        modoNumerico
                    );
                }
            }

            // Teclas 1..9
            else if(
                tecla >= '1' &&
                tecla <= '9'
            )
            {
                if(modoNumerico)
                {
                    editor.inserir(
                        tecla
                    );

                    t9.confirmar();

                    drawEditor(
                        editor.obter(),
                        modoNumerico
                    );
                }
                else
                {
                    bool mesma =
                        t9.mesmaSequencia(
                            tecla
                        );

                    char letra =
                        t9.converter(
                            tecla
                        );

                    if(letra)
                    {
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
                            editor.obter(),
                            modoNumerico
                        );
                    }
                }
            }
        }
    }

    // Resposta simulada LoRa
    if(
        respostaPendente &&
        millis() - respostaTempo > 2000
    )
    {
        addRX("ACK");

        respostaPendente =
            false;
    }
}