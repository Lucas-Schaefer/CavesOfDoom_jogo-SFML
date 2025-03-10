#include "../../headers/Observador/ObservadorJogador.hpp"
#include "../../headers/Estado/EstadoJogar.hpp"

namespace Observador {

    ObservadorJogador::ObservadorJogador(Player::Jogador* pJogador) :
        Observador(), pJogador(pJogador)
    {

    }

    ObservadorJogador::~ObservadorJogador() {

    }


    void ObservadorJogador::teclaPressionada(const sf::Keyboard::Key tecla) {
        if (pJogador->getJogador2()) {
            if (teclado[tecla] == 'j') {
                pJogador->andar(true);
            }
            else if (teclado[tecla] == 'l') {
                pJogador->andar(false);
            }
            else if (teclado[tecla] == 'i') {
                pJogador->pular();
            }
            else if (teclado[tecla] == 'k') {
                if (pJogador->getNoChao() && !pJogador->getAndando()) {
                    pJogador->atacar(true);
                }
            }
        }
        else {
            if (!pJogador->getMorrer()) {
                if (teclado[tecla] == 'a') {
                    pJogador->andar(true);
                }
                else if (teclado[tecla] == 'd') {
                    pJogador->andar(false);
                }
                else if (teclado[tecla] == 'w') {
                    pJogador->pular();
                }
                else if (teclado[tecla] == 's') {
                    if (pJogador->getNoChao() && !pJogador->getAndando()) {
                        pJogador->atacar(true);
                    }
                }
            }
        }
    }

    void ObservadorJogador::teclaSolta(const sf::Keyboard::Key tecla) {
        if (pJogador->getJogador2()) {
            if (teclado[tecla] == 'j' || teclado[tecla] == 'l') {
                pJogador->parar();
            }
            else if (teclado[tecla] == 'i' || teclado[tecla] == 'k') {
                pJogador->atacar(false);
            }
        }
        else {
            if (!pJogador->getMorrer()) {
                if (teclado[tecla] == 'a' || teclado[tecla] == 'd') {
                    pJogador->parar();
                }
                else if (teclado[tecla] == 'w' || teclado[tecla] == 's') {
                    pJogador->atacar(false);
                }
            }
        }
    }

    void ObservadorJogador::atualizarPontuacao(const unsigned int pontos) {
        Estado::Estado* estado = pGEstado->getEstadoAtual();
        if (estado->getID() == IDs::IDs::jogar_fase1 || estado->getID() == IDs::IDs::jogar_fase2) {
            Estado::EstadoJogar* estadoJogar = dynamic_cast<Estado::EstadoJogar*>(estado);
            Fase::Fase* fase = estadoJogar->getFase();
            if (fase == nullptr) {
                std::cout << "ObservadorJogador::Fase eh nullptr" << std::endl;
                exit(1);
            }
            fase->setPontuacao(pontos);

        }
    }

}