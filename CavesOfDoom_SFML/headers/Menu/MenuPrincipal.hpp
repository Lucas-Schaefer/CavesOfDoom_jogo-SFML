#pragma once

#include "Menu.hpp"
#include "../Fundo/Fundo.hpp"


namespace Menu {

    class MenuPrincipal : public Menu {
    protected:
        Fundo::Fundo fundo;

    private:
        void criarFundo();

    public:
        MenuPrincipal();
        MenuPrincipal(const IDs::IDs ID, std::string nome, const unsigned int tamFonte = 60);
        virtual ~MenuPrincipal();
        virtual void criarBotoes();
        virtual void executar();
    };

}