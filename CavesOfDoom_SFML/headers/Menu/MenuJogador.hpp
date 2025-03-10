#pragma once

#include "MenuPrincipal.hpp"



namespace Menu {

    class MenuJogador : public MenuPrincipal {
    private:


    public:
        MenuJogador();
        ~MenuJogador();
        void criarBotoes();
        void executar();
    };

}