#pragma once

#include "Lista.hpp"
#include "../Entidade/Entidade.hpp"


namespace Lista {

    class ListaEntidade {
    private:
        Lista<Entidades::Entidade> objListaEntidade;
    public:
        ListaEntidade();
        ~ListaEntidade();
        void addEntidade(Entidades::Entidade* entidade);
        void addEntidade(Entidades::Entidade* entidade, int pos);
        void removerEntidade(Entidades::Entidade* entidade, const bool deletar = true);
        void removerEntidade(int pos, const bool deletar = true);
        const int getTam();
        Entidades::Entidade* operator[](int pos);
        std::vector<Entidades::Entidade*> getEntidades(const IDs::IDs ID);
        void limparLista();
        void executar();
        void desenharEntidades();
    };

}