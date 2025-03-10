#include "./../../headers/Menu/MenuJogador.hpp"
#include "../../headers/Fase/Fase.hpp"

namespace Menu {

    MenuJogador::MenuJogador() :
        MenuPrincipal(IDs::IDs::menu_jogador, "SELECIONE JOGADOR", 40)
        //vectorTexto(), gerenciadorArquivo() //arquivo()
    {

    }

    MenuJogador::~MenuJogador() {

    }


    void MenuJogador::criarBotoes() {
        const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
        addBotao("1 jogador", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f), IDs::IDs::botao_1_jogador, sf::Color{ 0, 255, 0 });
        addBotao("2 jogadores", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 1.2f), IDs::IDs::botao_2_jogadores, sf::Color{ 0, 255, 0 });
        addBotao("voltar", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 2.4f), IDs::IDs::botao_voltar, sf::Color{ 0, 255, 0 });
        inicializarIterator();
    }



    void MenuJogador::executar() {
        //conte�do efeito parallax
        posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
        pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
        fundo.executar();
        pGrafico->resetarJanela();

        //desenha os bot�es
        desenhar();

        //desenha o t�tulo
        pGrafico->desenhaElemento(titulo.getTexto());


    }

}