#include "navigation.h"

#include "ui.h"
#include "menu.h"
#include "screens.h"

#include "screens/contatos.h"
#include "screens/configuracoes.h"
#include "screens/status.h"
#include "screens/sobre.h"

#include "../core/sistema.h"
#include "../model/contato.h"


/* =========================================================
   AUXILIAR
========================================================= */

static void abrirMensagens(
    Editor& editor,
    bool modoNumerico
)
{
    telaAtual = TELA_MENSAGENS;

    drawHomeScreen();

    drawEditor(
        editor.obter(),
        modoNumerico
    );
}


/* =========================================================
   NAVEGAÇÃO
========================================================= */

ResultadoNavegacao processarNavegacao(
    char tecla,
    Editor& editor,
    bool modoNumerico
)
{
    if(!tecla)
    {
        return NAVEGACAO_NENHUMA;
    }


    // =====================================================
    // A — CONTATOS
    // =====================================================

    if(tecla == 'A')
    {
        telaAtual = TELA_CONTATOS;

        drawContatos();

        return NAVEGACAO_CONSUMIDA;
    }


    // =====================================================
    // B — STATUS
    // =====================================================

    if(tecla == 'B')
    {
        telaAtual = TELA_STATUS;

        drawStatus();

        return NAVEGACAO_CONSUMIDA;
    }


    // =====================================================
    // D — MENU
    // =====================================================

    if(tecla == 'D')
    {
        if(telaAtual == TELA_MENU)
        {
            abrirMensagens(
                editor,
                modoNumerico
            );
        }
        else
        {
            telaAtual = TELA_MENU;

            drawMenu();
        }

        return NAVEGACAO_CONSUMIDA;
    }


    // =====================================================
    // MENU PRINCIPAL
    // =====================================================

    if(telaAtual == TELA_MENU)
    {
        switch(tecla)
        {
            case '1':

                abrirMensagens(
                    editor,
                    modoNumerico
                );

                return NAVEGACAO_CONSUMIDA;


            case '2':

                telaAtual =
                    TELA_CONTATOS;

                drawContatos();

                return NAVEGACAO_CONSUMIDA;


            case '3':

                telaAtual =
                    TELA_CONFIGURACOES;

                drawConfiguracoes();

                return NAVEGACAO_CONSUMIDA;


            case '4':

                telaAtual =
                    TELA_STATUS;

                drawStatus();

                return NAVEGACAO_CONSUMIDA;


            case '5':

                telaAtual =
                    TELA_SOBRE;

                drawSobre();

                return NAVEGACAO_CONSUMIDA;


            default:

                return NAVEGACAO_CONSUMIDA;
        }
    }


    // =====================================================
    // CONTATOS
    // =====================================================

    if(telaAtual == TELA_CONTATOS)
    {
        if(
            tecla >= '1' &&
            tecla <= ('0' + TOTAL_CONTATOS)
        )
        {
            sistema.contatoSelecionado =
                tecla - '1';


            abrirMensagens(
                editor,
                modoNumerico
            );


            return NAVEGACAO_CONTATO;
        }


        return NAVEGACAO_CONSUMIDA;
    }


    // =====================================================
    // NENHUMA NAVEGAÇÃO
    // =====================================================

    return NAVEGACAO_NENHUMA;
}