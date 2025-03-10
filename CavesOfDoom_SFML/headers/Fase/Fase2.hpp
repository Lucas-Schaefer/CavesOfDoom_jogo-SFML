#pragma once

#include "Fase.hpp"


namespace Fase {

    class Fase2 : public Fase {
    private:
        void recuperarJogada(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase);
    public:
        Fase2(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase, const IDs::IDs ID);
        Fase2(const IDs::IDs ID = IDs::IDs::fundo_fase2);
        ~Fase2();
        void criarFundo();
        void criarMapa(const IDs::IDs ID_Mapa);
    };

}