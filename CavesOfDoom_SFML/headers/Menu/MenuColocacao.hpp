#pragma once

#include "MenuPrincipal.hpp"
#include "../Gerenciador/GerenciadorArquivo.hpp"
#include <vector> 

#define CAMINHO_ARQUIVO_COLOCACAO "arquivos/colocacao/colocacao.txt"
#define QUANTIDADE_PALAVRAS 2
#define CAMINHO_FONTE_COLOCACAO "fonte/menuColocacao.ttf"


namespace Menu {

    class MenuColocacao : public MenuPrincipal {
    private:
        std::vector<Botao::Texto*> vectorTexto;
        Gerenciador::GerenciadorArquivo gerenciadorArquivo;

        void criarTexto(std::string linha);
        void criarColocacao();
        void desenharColocacao();
    public:
        MenuColocacao();
        ~MenuColocacao();
        void criarBotoes();
        void executar();
    };

}