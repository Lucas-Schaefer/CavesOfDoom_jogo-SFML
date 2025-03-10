#include "../../headers/Fase/Fase1.hpp"


namespace Fase {

    Fase1::Fase1(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase, const IDs::IDs ID) :
        Fase(ID, IDs::IDs::fundo_fase1)
    {
        criarFundo();
        recuperarJogada(vectorEntidades, vectorInfoFase);
    }

    Fase1::Fase1(const IDs::IDs ID) :
        Fase(ID, IDs::IDs::fundo_fase1)
    {
        criarFundo();
        criarMapa(ID);
    }

    Fase1::~Fase1() {

    }

    void Fase1::recuperarJogada(const std::vector<std::string> vectorEntidades, const std::vector<std::string> vectorInfoFase) {
        try {
            setPontuacao(std::stoi(vectorInfoFase[1]));
            this->textoTempo.setString(vectorInfoFase[2]);
            std::vector<std::string> linhas = vectorEntidades;
            int i = 0;
            if (pJogador == nullptr) {
                i = 2;
                criarEntidade(IDs::IDs::jogador, getAtributosEntidade(linhas[0]), getAtributosEntidade(linhas[1]), true);
                //pGrafico->atualizarCamera(pJogador->getPos(), pJogador->getTam());
                //fundo.atualizarPosicao();
            }
            while (i < linhas.size()) {
                std::string linha = linhas[i];
                int id = std::stoi(linha.substr(0, linha.find(" ")));
                const std::vector<std::string> atributos = getAtributosEntidade(linhas[i]);
                switch (id)
                {
                case (6):
                {
                    //criar Lobo
                    criarEntidade(IDs::IDs::Lobo, atributos, getAtributosEntidade(linhas[i + 1]), true);
                    i++;
                }
                break;
                /*case (54):
                {
                    //criar Demonio com projetil
                    criarEntidade(IDs::IDs::Demonio, atributos, getAtributosEntidade(linhas[i + 1]), true);
                    i++;
                }
                break;*/
                case (7):
                {
                    //cria plataforma
                    criarEntidade(IDs::IDs::plataforma, atributos, {}, false);
                }
                break;
                case (8):
                {
                    //criar caixa
                    criarEntidade(IDs::IDs::caixa, atributos, {}, false);
                }
                break;

                case (9):
                {
                    //criar vida
                    criarEntidade(IDs::IDs::vida, atributos, {}, false);
                }
                break;
                case(49):
                {
                    //criar plataforma
                    criarEntidade(IDs::IDs::plataforma_movel, atributos, {}, false);
                }
                break;

                case(53):
                {
                    criarEntidade(IDs::IDs::espinho, atributos, {}, false);
                }
                break;
                case (5):
                    criarEntidade(IDs::IDs::Orc, atributos, {}, true);

                }
                i++;
            }
        }
        catch (const std::exception& e) {
            std::cerr << e.what() << std::endl;
            exit(1);
        }
    }

    void Fase1::criarFundo() {
        fundo.addCamada("/fase1background1.png", 0.0f);
        fundo.addCamada("/fase1background2.png", 0.1f);
        fundo.addCamada("/fase1background3.png", 0.3f);
        fundo.addCamada("/fase1background4.png", 0.5f);
    }

    void Fase1::criarMapa(const IDs::IDs ID_Mapa) {
        switch (ID_Mapa)
        {
        case (IDs::IDs::fase1_parte_1):
        {
            criarMapa1();
        }
        break;
        case (IDs::IDs::fase1_parte_2):
        {
            criarMapa2();
        }
        break;
        case (IDs::IDs::fase1_parte_3):
        {
            criarMapa3();
        }
        break;
        default:
        {
            std::cout << "ERRO::Fase1::ID invalido" << std::endl;
            exit(1);
        }
        break;
        }
    }

    void Fase1::criarMapa1() {
        sf::Vector2f tamJanela = pGrafico->getTamJanela();
        limiteCamera.left = -550.0f + tamJanela.x / 2.0f - 75.f;
        limiteCamera.top = 150.0f;
        limiteCamera.width = 11 * 500.0f - 50.0f;
        limiteCamera.height = tamJanela.y - 350.0f;
        pGrafico->setLimiteCamera(limiteCamera);

        criarPlataforma(sf::Vector2f(-550.0f, 100.0f), sf::Vector2f(50.f, 500.0f), "parede");
        //ch�o
        for (int i = -1; i < 11; i++) {
            criarPlataforma(sf::Vector2f(i * 500.0f, 550.0f), sf::Vector2f(500.0f, 50.0f), "padrao");
        }
        criarPlataforma(sf::Vector2f(11 * 500.0f, 100.0f), sf::Vector2f(50.f, 500.0f), "parede");

        //plataforma do jogador
        criarPersonagem(IDs::IDs::jogador, sf::Vector2f(150.0f, 300.0f));

        // teste
        criarPlataforma(sf::Vector2f(300.0f, 0.0f), sf::Vector2f(80.0f, 50.0f), 400.0f, false);

        //criando espinho
        criarEspinho(sf::Vector2f(320.0f, 525.0f), sf::Vector2f(80.0f, 25.0f));

        criarPlataforma(sf::Vector2f(0.0f, 400.0f), sf::Vector2f(250.0f, 10.0f), "madeira", sf::Vector2f(1.0f, 15.2f));

        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(450.0f, 450.0f), 1);
        criarCaixa(sf::Vector2f(700.0f, 500.0f));

        criarPlataforma(sf::Vector2f(750.0f, 400.0f), sf::Vector2f(300.0f, 10.0f), "madeira", sf::Vector2f(1.0f, 15.2f));
        criarPlataforma(sf::Vector2f(750.0f + 300.0f, 400.0f), sf::Vector2f(300.0f, 10.0f), "madeira", sf::Vector2f(1.0f, 15.2f));
        criarEspinho(sf::Vector2f(1000.0f, 375.0f), sf::Vector2f(80.0f, 25.0f));
        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(900.0f, 300.0f), 1);
        criarPlataforma(sf::Vector2f(1350.0f, 200.0f), sf::Vector2f(80.0f, 50.0f), 200.0f, false);

        criarPlataforma(sf::Vector2f(1350.0f + 80.0f, 200.0f), sf::Vector2f(350.0f, 50.0f), "flutuante_maior", sf::Vector2f(1.0f, 1.2f));
        criarEspinho(sf::Vector2f(1480.0f, 175.0f), sf::Vector2f(80.0f, 25.0f));
        //criarPorta(sf::Vector2f(150.0f, 250.0f), sf::Vector2f(85.0f, 110.0f),sf::Vector2f(150.0f, 200.0f), sf::Vector2f(40.0f, 40.0f), IDs::IDs::floresta_branca_parte_2);
        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(1700.0f, 100.0f), 4);
        criarCaixa(sf::Vector2f(2200.0f, 500.0f));

        criarPlataforma(sf::Vector2f(2300.0f, 400.0f), sf::Vector2f(300.0f, 10.0f), "madeira", sf::Vector2f(1.0f, 15.2f));
        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(2500.0f, 300.0f), 5);
        criarPlataforma(sf::Vector2f(2600.0f, 400.0f), sf::Vector2f(80.0f, 50.0f), 300.0f, true);
        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(2800.0f, 300.0f), 4);

        criarPlataforma(sf::Vector2f(2980.0f, 400.0f), sf::Vector2f(300.0f, 10.0f), "madeira", sf::Vector2f(1.0f, 15.2f));
        criarPlataforma(sf::Vector2f(3300.0f, 200.0f), sf::Vector2f(80.0f, 50.0f), 200.0f, false);
        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(3650.0f, 200.0f), 3);
        criarPersonagem(IDs::IDs::Orc, sf::Vector2f(3600.0f, 450.0f), 1);
        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(3800.0f, 450.0f), 3);
        criarPersonagem(IDs::IDs::Lobo, sf::Vector2f(3800.0f, 100.0f), 4);
        criarPlataforma(sf::Vector2f(3400.0f, 200.0f), sf::Vector2f(80.0f, 50.0f), 200.0f, true);
        criarPlataforma(sf::Vector2f(3700.0f, 200.0f), sf::Vector2f(350.0f, 50.0f), "flutuante_maior", sf::Vector2f(1.0f, 1.2f));
        criarPlataforma(sf::Vector2f(4080.0f, 200.0f), sf::Vector2f(80.0f, 50.0f), 200.0f, true);
        criarPlataforma(sf::Vector2f(4380.0f, 200.0f), sf::Vector2f(350.0f, 50.0f), "flutuante_maior", sf::Vector2f(1.0f, 1.2f));
    }


    void Fase1::criarMapa2() {
        sf::Vector2f tamJanela = pGrafico->getTamJanela();
        limiteCamera.left = -550.0f + tamJanela.x / 2.0f - 75.f;
        limiteCamera.top = 150.0f;
        limiteCamera.width = 500.0f - 50.0f;
        limiteCamera.height = tamJanela.y - 350.0f;
        pGrafico->setLimiteCamera(limiteCamera);

        criarPlataforma(sf::Vector2f(-550.0f, 100.0f), sf::Vector2f(50.f, 500.0f), "parede");
        criarPlataforma(sf::Vector2f(-220.0f, -100.0f), sf::Vector2f(50.f, 500.0f), "parede_flutuante");
        criarPlataforma(sf::Vector2f(-500.0f, 450.0f), sf::Vector2f(80.0f, 1.0f), "ponte_direita", sf::Vector2f(1.0f, 40.0f));
        criarPlataforma(sf::Vector2f(-220.0f - 80.0f, 350.0f), sf::Vector2f(80.0f, 1.0f), "ponte_esquerda", sf::Vector2f(1.0f, 40.0f));
        criarPlataforma(sf::Vector2f(-500.0f, 250.0f), sf::Vector2f(80.0f, 1.0f), "ponte_direita", sf::Vector2f(1.0f, 40.0f));
        for (int i = -1; i < 1; i++) {
            criarPlataforma(sf::Vector2f(i * 500.0f, 550.0f), sf::Vector2f(500.0f, 50.0f), "padrao");
        }


        //Boss
        criarPersonagem(IDs::IDs::Orc, sf::Vector2f(400.0f, 300.0f), 2);

        criarPlataforma(sf::Vector2f(500.0f, 100.0f), sf::Vector2f(50.f, 500.0f), "parede");
    }

    void Fase1::criarMapa3() {
        for (int i = -2; i < 8; i++) {
            criarPlataforma(sf::Vector2f(i * 500.0f, 550.0f), sf::Vector2f(500.0f, 50.0f), "padrao");
        }
        criarPlataforma(sf::Vector2f(400.0f, 400.0f), sf::Vector2f(350.0f, 50.0f), "madeira", sf::Vector2f(1.0f, 3.0f));
        criarPlataforma(sf::Vector2f(800.0f, 150.0f), sf::Vector2f(80.0f, 50.0f), 250.0f, false);
        criarPlataforma(sf::Vector2f(1000.0f, 150.0f), sf::Vector2f(350.0f, 50.0f), "madeira", sf::Vector2f(1.0f, 3.0f));
        criarCaixa(sf::Vector2f(250.0f, 500.0f));

    }

}

