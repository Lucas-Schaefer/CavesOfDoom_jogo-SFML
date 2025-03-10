#pragma once

//Classe Base
#include "../Ente.hpp"

//Fundo efeito Parallax
#include "../Fundo/Fundo.hpp"

//Gerenciadores
#include "../Gerenciador/GerenciadorColisao.hpp"
#include "../Gerenciador/GerenciadorArquivo.hpp"

//Listas
#include "../Lista/ListaEntidade.hpp"

#include "../Entidade/Personagem/Inimigo/Orc.hpp"
#include "../Entidade/Personagem/Inimigo/Lobo.hpp"
#include "../Entidade/Item/Projetil.hpp"
#include "../Entidade/Item/Vida.hpp"
#include "../Entidade/Obstaculo/PlataformaMovel.hpp"
#include "../Entidade/Obstaculo/Caixa.hpp"
#include "../Entidade/Personagem/Jogador/Jogador.hpp"
#include "../Observador/ObservadorFase.hpp"
#include "../Entidade/Obstaculo/Espinho.hpp"
#include "../Entidade/Personagem/Inimigo/Demonio.hpp"

#include "../Menu/Botao/Texto.hpp"

#include <fstream>

//#define CAMINHO_FONTE_FASE "../../imagens/Fonte/menuColocacao.ttf"


using namespace Entidades;
using namespace Personagens;

namespace Fase {

    class Fase : public Ente {
    private:
        static Observador::ObservadorFase* observadorFase;
        float tempo;

    protected:
        sf::IntRect limiteCamera;
        Lista::ListaEntidade* listaPersonagens;
        Lista::ListaEntidade* listaObstaculos;
        Gerenciador::GerenciadorArquivo GArquivo;
        Gerenciador::GerenciadorColisao* pColisao;
        Fundo::Fundo fundo;
        static Menu::Botao::Texto textoTempo;
        static unsigned int pontuacaoJogador;
        static Menu::Botao::Texto textoPontuacao;
        static Player::Jogador* pJogador;
        bool jogador2;

        void criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const std::string type, const sf::Vector2f escala = sf::Vector2f(1.0f, 1.0f));
        void criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const float distancia, const bool horizontal);
        void criarCaixa(const sf::Vector2f pos);
        void criarVida(const sf::Vector2f pos);
        void criarEspinho(const sf::Vector2f pos, const sf::Vector2f tam);

        void criarPersonagem(const IDs::IDs ID, const sf::Vector2f pos, const int nivel = 1);
        void criarEntidade(const IDs::IDs ID, const std::vector<std::string> primeiro, const std::vector<std::string> segundo, const bool ehPersonagem);

        std::vector<std::string> getAtributosEntidade(std::string linha);
    public:
        Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo);
        ~Fase();
        //void setDoisJogadores(bool dJ);
        virtual void criarFundo() = 0;
        virtual void criarMapa(const IDs::IDs ID_Mapa) = 0;
        Player::Jogador* getJogador();
        void mudarEstadoObservador();
        //  void mudarFase(const IDs::IDs ID_Fase = IDs::IDs::vazio);
        void removerJogadorLista();
        const unsigned int getPontuacaoJogador() const;
        virtual void recuperarJogada(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase) = 0;
        void setPontuacao(const unsigned int pontuacaoJogador);
        void atualizarTempo();
        void atualizarPontuacao();
        const std::vector<std::string> salvarEntidades();
        void setLimiteCamera(sf::IntRect limiteCamera);
        const sf::IntRect getLimiteCamera() const;
        const std::string salvar();
        void executar();
        void desenhar();
    };

}