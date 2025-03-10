#pragma once

#include "Observador.hpp"
#include "../Entidade/Personagem/Jogador/Jogador.hpp"
#include "../Gerenciador/GerenciadorEstado.hpp"


namespace Observador {

    class ObservadorJogador : public Observador {
    private:
        Player::Jogador* pJogador;
    public:
        ObservadorJogador(Player::Jogador* pJogador);
        ~ObservadorJogador();
        void teclaPressionada(const sf::Keyboard::Key tecla);
        void teclaSolta(const sf::Keyboard::Key tecla);
        void atualizarPontuacao(const unsigned int pontos);
    };

}