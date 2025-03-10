#include "../../headers/Observador/ObservadorFase.hpp"
#include "../../headers/Gerenciador/GerenciadorEstado.hpp"
#include "../../headers/Fase/Fase.hpp"



namespace Observador {

    ObservadorFase::ObservadorFase() :
        Observador(), fase(nullptr)
    {

    }

    ObservadorFase::~ObservadorFase() {

    }

    void ObservadorFase::setFase(Fase::Fase* fase) {
        this->fase = fase;
    }

    void ObservadorFase::notificarJogadorMorreu() {
        pGEstado->addEstado(IDs::IDs::estado_menu_game_over);
    }

    void ObservadorFase::teclaPressionada(const sf::Keyboard::Key tecla) {
        //terminar..
    }

    void ObservadorFase::teclaSolta(const sf::Keyboard::Key tecla) {
        if (tecladoEspecial[tecla] == "Escape" || teclado[tecla] == 'p') {
            pGEstado->addEstado(IDs::IDs::estado_menu_pausa);
        }
    }

}