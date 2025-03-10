#pragma once

#include "Inimigo.hpp"

#define RECONHECIMENTO_LOBO_X 350.0f
#define RECONHECIMENTO_LOBO_Y 120.0f
#define EXPERIENCIA_LOBO 100.0f
#define TAMANHO_LOBO_X 55.0f
#define TAMANHO_LOBO_Y 50.0f
#define TEMPO_LOBO_MORRER 1.5f
#define TEMPO_LOBO_ATACAR 1.0f
#define PONTOS_LOBO 250
#define TEMPO_LOBO_INVISIVEL 2.0f
#define FORCA_LOBO 25.0f
#define DEFESA_LOBO 20.0f
#define VITALIDADE_LOBO 10.0f


namespace Entidades {

    namespace Personagens {

        namespace Inimigos {

            class Lobo : public Inimigo {
            private:
                bool raiva;
                float tempoRaiva;
                sf::Color corPadrao;

                void inicializarAnimacao();
                void inicializarNivel();
                void atualizarRaiva();
                void atualizarAnimacao();
            public:
                Lobo(const sf::Vector2f pos, const int nivel, Player::Jogador* jogador);
                Lobo(const std::vector<std::string> atributos, Player::Jogador* jogador);
                ~Lobo();
                void tomarDano(const float dano);
                const std::string salvar();
                void atualizarTempoAtacar();
                void moveInimigo();
            };

        }

    }

}