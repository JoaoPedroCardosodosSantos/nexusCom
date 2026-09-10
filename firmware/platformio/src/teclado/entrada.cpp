#include "entrada.h"

#include "../core/sistema.h"
#include "../ui/ui.h"
#include "../ui/screens.h"


/* =========================================================
   PROCESSAMENTO DE ENTRADA DE MENSAGEM
========================================================= */

bool processarEntradaMensagem(
    char tecla,
    Editor& editor,
    EditorT9& t9,
    bool& modoNumerico
)
{
    if(!tecla)
    {
        return false;
    }


    if(telaAtual != TELA_MENSAGENS)
    {
        return false;
    }


    // =====================================================
    // TECLAS 1-9
    // =====================================================

    if(
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

        return true;
    }


    // =====================================================
    // * — MODO NUMÉRICO
    // =====================================================

    if(tecla == '*')
    {
        modoNumerico =
            !modoNumerico;

        t9.confirmar();

        drawEditor(
            editor.obter(),
            modoNumerico
        );

        return true;
    }


    // =====================================================
    // 0 — ESPAÇO / ZERO
    // =====================================================

    if(tecla == '0')
    {
        if(modoNumerico)
        {
            editor.inserir(
                '0'
            );
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

        return true;
    }


    // =====================================================
    // C — APAGAR
    // =====================================================

    if(tecla == 'C')
    {
        editor.apagarUltimo();

        t9.confirmar();

        drawEditor(
            editor.obter(),
            modoNumerico
        );

        return true;
    }


    return false;
}