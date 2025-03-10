#include "./../../headers/Menu/MenuSelecaoFase.hpp"
#include "../../headers/Fase/Fase.hpp"

namespace Menu {

    MenuSelecaoFase::MenuSelecaoFase() :
        MenuPrincipal(IDs::IDs::menu_selecao_fase, "SELECIONE FASE", 40)
    {

    }

    MenuSelecaoFase::~MenuSelecaoFase() {

    }


    void MenuSelecaoFase::criarBotoes() {
        const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
        addBotao("fase 1", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f), IDs::IDs::botao_fase1, sf::Color{ 0, 255, 0 });
        addBotao("fase 2", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 1.2f), IDs::IDs::botao_fase2, sf::Color{ 0, 255, 0 });
        addBotao("voltar", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 2.4f), IDs::IDs::botao_voltar, sf::Color{ 0, 255, 0 });
        inicializarIterator();
    }



    void MenuSelecaoFase::executar() {
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