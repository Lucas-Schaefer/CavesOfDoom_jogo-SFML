#pragma once 

#include "MenuPausa.hpp"
#include "../Fase/Fase.hpp"
#include "../Gerenciador/GerenciadorArquivo.hpp"

#define TAMANHO_BOTAO_MENU_GAME_OVER_X 180.0f
#define TAMANHO_BOTAO_MENU_GAME_OVER_Y 60.0f
#define CAMINHO_FONTE_MENU_GAME_OVER "/menu.ttf"


namespace Menu {

    class MenuGameOver : public MenuPausa {
    private:
        sf::RectangleShape fundoCaracter;
        Botao::Texto texto;
        Botao::Texto pontuacao;
        Gerenciador::GerenciadorArquivo gerenciadorArquivo;

        void ajustarTexto();
    public:
        MenuGameOver(Fase::Fase* fase);
        ~MenuGameOver();
        void criarBotoes();
        void addCaracter(char caracter);
        void removerCaracter();
        void salvarColocacao();
        void executar();
    };

}