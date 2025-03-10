#pragma once

#include "MenuPrincipal.hpp"
#include "MenuJogador.hpp"



namespace Menu {

    class MenuSelecaoFase : public MenuPrincipal {
    private:


    public:
        MenuSelecaoFase();
        ~MenuSelecaoFase();
        void criarBotoes();
        void executar();
    };

}