#pragma once

#include "../Personagem.hpp"
#include "../../Item/Arma.hpp"

#define VELOCIDADE_JOGADOR 200.0f
#define TAMANHO_PULO 120.0f
#define TAMANHO_JOGADOR_X 50.0f
#define TAMANHO_JOGADOR_Y 90.0f
#define TAMANHO_ESPADA_X 80.0f
#define TEMPO_JOGADOR_MORRER 1.0f
#define TEMPO_JOGADOR_TOMARDANO 0.30f
#define BARRA_VIDA_JOGADOR_X 350.0f
#define BARRA_VIDA_JOGADOR_Y 20.0f
#define DANO 35.0f
#define FORCA_JOGADOR 50.0f
#define DEFESA_JOGADOR 20.0f
#define VITALIDADE_JOGADOR 20.0f

namespace Observador {
    class ObservadorJogador;
}

namespace Entidades {

    namespace Personagens {

        namespace Player {

            class Jogador : public Personagem {
            private:
                bool jogador2;
                bool noChao;
                Observador::ObservadorJogador* observadorJogador;
                sf::RectangleShape tuboBarraVida;
                sf::RectangleShape tuboBarraXP;
                sf::RectangleShape barraXP;
                Menu::Botao::Texto textoExp;

                void inicializarAnimacao();
                void inicializarBarraVida();
                void atualizarAnimacao();
                void atualizarBarraVida();
                void inicializarNivel();
                void inicializarBarraXP();
                void atualizarBarraXP();
                void atualizarNivel();
                void inicializarExp();
                void atualizarExp();
            public:
                Jogador(const sf::Vector2f pos, Item::Arma* arma);
                Jogador(const std::vector<std::string> atributos);
                ~Jogador();
                void colisao(Entidade* outraEntidade, sf::Vector2f ds = sf::Vector2f(0.0f, 0.0f));
                const bool getNoChao() const;
                const bool getAndando() const;
                void pular();
                void podePular();
                void mudarEstadoObservador();
                void addPontuacao(const unsigned int pontos);
                void addExperiencia(const float experiencia);
                void setVida(const float vida);
                const std::string salvar();
                void atualizar();
                void desenhar();
                void setJogador2(bool jog2);
                bool getJogador2();
            };

        }

    }

}