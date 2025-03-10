#include "../../headers/Menu/MenuPrincipal.hpp"

namespace Menu {

    MenuPrincipal::MenuPrincipal() :
        Menu(IDs::IDs::menu_principal, sf::Vector2f(TAMANHO_BOTAO_X, TAMANHO_BOTAO_Y), "CAVES OF DOOM", 60),
        fundo(IDs::IDs::fundo_menu)
    {
        titulo.setPos(sf::Vector2f(tamJanela.x / 2.0f - titulo.getTam().x / 2.0f, 25.0f));
        titulo.setCorTexto(sf::Color{ 0,200,0 });
        criarFundo();
    }

    MenuPrincipal::MenuPrincipal(const IDs::IDs ID, std::string nome, const unsigned int tamFonte) :
        Menu(ID, sf::Vector2f(TAMANHO_BOTAO_X, TAMANHO_BOTAO_Y), nome, tamFonte),
        fundo(IDs::IDs::fundo_menu)
    {
        titulo.setPos(sf::Vector2f(tamJanela.x / 2.0f - titulo.getTam().x / 2.0f, 25.0f));
        titulo.setCorTexto(sf::Color{ 0,200,0 });

        criarFundo();
    }

    MenuPrincipal::~MenuPrincipal() {

    }

    void MenuPrincipal::criarFundo() {
        fundo.addCamada("imagens/Menu/Background1.png", 0.0f);
        fundo.addCamada("imagens/Menu/Background2.png", 0.05f);
        fundo.addCamada("imagens/Menu/Background3.png", 0.1f);
        fundo.addCamada("imagens/Menu/Background4.png", 0.15f);
        fundo.addCamada("imagens/Menu/Background5.png", 0.2f);
        fundo.addCamada("imagens/Menu/Background6.png", 0.4f);
        fundo.addCamada("imagens/Menu/Background7.png", 0.6f);
        fundo.addCamada("imagens/Menu/Background8.png", 0.8f);
    }

    void MenuPrincipal::criarBotoes() {
        const float posBotaoX = tamJanela.x / 2.0f - tamBotao.x / 2.0f;
        addBotao("novo jogo", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f), IDs::IDs::botao_novoJogo, sf::Color{ 0, 255, 0 });
        addBotao("carregar jogo", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 1.2f), IDs::IDs::botao_carregar_jogo, sf::Color{ 0, 255, 0 });
        addBotao("colocacao", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 2.4f), IDs::IDs::botao_colocacao, sf::Color{ 0, 255, 0 });
        addBotao("sair", sf::Vector2f(posBotaoX, tamJanela.y / 2.0f + tamBotao.y * 4.8f), IDs::IDs::botao_sair, sf::Color{ 0, 255, 0 });
        inicializarIterator();
    }

    void MenuPrincipal::executar() {
        //conte�do do efeito Parallax
        posFundo = sf::Vector2f(posFundo.x + pGrafico->getTempo() * 80.0f, posFundo.y);
        pGrafico->atualizarCamera(sf::Vector2f(posFundo.x + tamJanela.x / 2.0f, posFundo.y + tamJanela.y / 2.0f));
        fundo.executar();
        pGrafico->resetarJanela();

        //desenha todo o conte�do do menu principal na tela
        desenhar();
        pGrafico->desenhaElemento(titulo.getTexto());
    }

}