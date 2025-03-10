#pragma once

#include "Inimigo.hpp"


namespace Entidades {

    namespace Personagens {

        namespace Inimigos {

            class Demonio : public Inimigo {
            private:
                //bool noChao;
                void inicializarAnimacao();
                void inicializarNivel();
            public:
                Demonio(const sf::Vector2f pos, const int nivel, Player::Jogador* pJogador);
                Demonio(const std::vector<std::string> atributos, Player::Jogador* pJogador);
                ~Demonio();
                const std::string salvar();
            };

        }

    }

}