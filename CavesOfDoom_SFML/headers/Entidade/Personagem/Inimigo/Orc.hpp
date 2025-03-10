#pragma once

#include "Inimigo.hpp"

#define TAMANHO_ORC_X 50.0f
#define TAMANHO_ORC_Y 90.0f
#define TEMPO_ORC_MORRER 1.5f
#define PONTOS_ORC 200
#define EXPERIENCIA_ORC 50.0f


namespace Entidades {

    namespace Personagens {

        namespace Inimigos {

            class Orc : public Inimigo {
            private:
                bool raiva;
                float tempoRaiva;
                sf::Color corPadrao;

                void inicializarAnimacao();
                void inicializarNivel();
                void atualizarRaiva();
                void atualizarAnimacao();
            public:
                Orc(const sf::Vector2f pos, const int nivel, Player::Jogador* jogador);
                Orc(const std::vector<std::string> atributos, Player::Jogador* jogador);
                ~Orc();
                void tomarDano(const float dano);
                const std::string salvar();
                void atualizarTempoAtacar();
                void moveInimigo();
            };

        }

    }

}