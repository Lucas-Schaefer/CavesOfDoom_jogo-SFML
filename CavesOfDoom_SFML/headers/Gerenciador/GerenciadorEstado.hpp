#pragma once

//Gerenciadores
#include "GerenciadorGrafico.hpp"

#include "../Estado/EstadoJogar.hpp"
#include "../Estado/EstadoMenu.hpp"

//Pilha
#include <stack>


namespace Gerenciador {

    class GerenciadorEstado {
    private:
        std::stack<Estado::Estado*> pilhaEstados;

        //padr�o de projeto singleton
        static GerenciadorEstado* pGerenciadorEstado;
        GerenciadorEstado();

        void desativarObservadores();
        void ativarObservadores();
    public:
        ~GerenciadorEstado();
        static GerenciadorEstado* getGerenciadorEstado();
        void executar();
        Estado::Estado* getEstado(const int qtdRemove);
        void addEstado(const IDs::IDs ID);
        void removerEstado(const int qtd);
        void removerEstado();
        Estado::Estado* getEstadoAtual();
    };

}