#include "display/display.h"
#include "ui/ui.h"
#include "teclado/teclado.h"
#include "teclado/editor.h"
#include "teclado/t9.h"

Teclado teclado;
Editor editor;
T9 t9;

void setup()
{
    initDisplay();
    teclado.iniciar();
    drawHomeScreen();
    addTX("Mensagem 2");
    addRX("Recebido");
}

void loop()
{
    char tecla = teclado.ler();

    if(tecla)
    {
        if(tecla >= '2' && tecla <= '9')
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
        else if(tecla == '#')
        {
          if(!editor.vazio())
          {
              addTX(
                  editor.obter()
              );

              editor.limpar();

              t9.confirmar();

              drawEditor(
                  editor.obter()
              );
          }
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
    }
}