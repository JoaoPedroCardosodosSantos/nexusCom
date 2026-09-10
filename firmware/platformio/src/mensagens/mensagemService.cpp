#include "mensagemService.h"


MensagemService::MensagemService()
{
    transporte = nullptr;
}


void MensagemService::definirTransporte(
    Transporte* novoTransporte
)
{
    transporte = novoTransporte;
}


bool MensagemService::enviar(
    const Mensagem& mensagem
)
{
    return filaSaida.adicionar(
        mensagem
    );
}


bool MensagemService::receber(
    const Mensagem& mensagem
)
{
    return filaEntrada.adicionar(
        mensagem
    );
}


bool MensagemService::obterSaida(
    Mensagem& mensagem
)
{
    return filaSaida.obter(
        mensagem
    );
}


bool MensagemService::obterEntrada(
    Mensagem& mensagem
)
{
    return filaEntrada.obter(
        mensagem
    );
}


bool MensagemService::possuiMensagensSaida() const
{
    return filaSaida.tamanho() > 0;
}


bool MensagemService::possuiMensagensEntrada() const
{
    return filaEntrada.tamanho() > 0;
}


int MensagemService::quantidadeSaida() const
{
    return filaSaida.tamanho();
}


int MensagemService::quantidadeEntrada() const
{
    return filaEntrada.tamanho();
}


void MensagemService::atualizar()
{
    if(transporte == nullptr)
        return;

    transporte->atualizar();

    if(transporte->disponivel())
    {
        Mensagem mensagem;

        if(filaSaida.obter(mensagem))
        {
            LOG_INFO(
                "MENSAGEM",
                "Enviando para transporte"
            );

            if(!transporte->enviar(mensagem))
            {
                LOG_INFO(
                    "MENSAGEM",
                    "Transporte recusou mensagem"
                );

                filaSaida.adicionar(mensagem);
            }
        }
    }

    Mensagem recebida;

    if(transporte->receber(recebida))
    {
        LOG_INFO(
            "MENSAGEM",
            "Mensagem recebida do transporte"
        );

        filaEntrada.adicionar(recebida);
    }
}


void MensagemService::limpar()
{
    filaSaida.limpar();

    filaEntrada.limpar();
}