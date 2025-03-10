#pragma once

//Gerenciador
#include "Gerenciador/GerenciadorGrafico.hpp"
#include "Gerenciador/GerenciadorEvento.hpp"

//Fases
#include "Fase/Fase1.hpp"
#include "Fase/Fase2.hpp"

#include "Gerenciador/GerenciadorEstado.hpp"

#include <SFML/Audio.hpp>


class Principal {
private:
    static Gerenciador::GerenciadorGrafico* pGrafico;
    static Gerenciador::GerenciadorEvento* pEvento;
    static Gerenciador::GerenciadorEstado* pGerenciadorEstado;

    void inicializa();
public:
    Principal();
    ~Principal();
    void executar();
};