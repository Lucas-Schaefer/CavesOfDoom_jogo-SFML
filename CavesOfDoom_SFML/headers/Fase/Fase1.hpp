#pragma once

#include "Fase.hpp"
#include "../Entidade/Personagem/Inimigo/Demonio.hpp"


namespace Fase {

    class Fase1 : public Fase {
    private:
        void recuperarJogada(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase);
        void criarMapa1();
        void criarMapa2();
        void criarMapa3();
    public:
        Fase1(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase, const IDs::IDs ID);
        Fase1(const IDs::IDs ID = IDs::IDs::fase1_parte_1);
        ~Fase1();
        void criarFundo();
        void criarMapa(const IDs::IDs ID_Mapa);
    };

}