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

#include "model/contato.h"
#include "model/contato_atual.h"

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
        // ==========================
        // ATALHOS GLOBAIS
        // ==========================

        if(tecla == 'A')
        {
            telaAtual = TELA_CONTATOS;

            drawContatos();

            return;
        }

        if(tecla == 'B')
        {
            telaAtual = TELA_STATUS;

            drawStatus();

            return;
        }

        // ==========================
        // MENU
        // ==========================

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

        // ==========================
        // MENU PRINCIPAL
        // ==========================

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

        // ==========================
        // CONTATOS
        // ==========================

        if(telaAtual == TELA_CONTATOS)
        {
            if(tecla >= '1' &&
               tecla <= '0' + TOTAL_CONTATOS)
            {
                contatoSelecionado =
                    tecla - '1';

                telaAtual =
                    TELA_MENSAGENS;

                drawHomeScreen();

                drawEditor(
                    editor.obter(),
                    modoNumerico
                );
            }

            return;
        }

        // ==========================
        // MENSAGENS
        // ==========================

        if(telaAtual == TELA_MENSAGENS)
        {
            if(tecla >= '1' &&
               tecla <= '9')
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

            else if(tecla == '*')
            {
                modoNumerico =
                    !modoNumerico;

                drawEditor(
                    editor.obter(),
                    modoNumerico
                );
            }

            else if(tecla == '0')
            {
                if(modoNumerico)
                {
                    editor.inserir('0');
                }
                else
                {
                    editor.espaco();
                }

                t9.confirmar();

                drawEditor(
                    editor.obter(),
                    modoNumerico
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
                        editor.obter(),
                        modoNumerico
                    );
                }
            }

            else if(tecla == 'C')
            {
                editor.apagarUltimo();

                t9.confirmar();

                drawEditor(
                    editor.obter(),
                    modoNumerico
                );
            }
        }
    }

    // ==========================
    // RESPOSTA LoRa SIMULADA
    // ==========================

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