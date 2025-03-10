#include "../../headers/Fase/Fase.hpp"



using namespace Entidades;
using namespace Personagens;

namespace Fase {

    Player::Jogador* Fase::pJogador = nullptr;
    Observador::ObservadorFase* Fase::observadorFase = nullptr;
    unsigned int Fase::pontuacaoJogador = 0;
    Menu::Botao::Texto Fase::textoPontuacao = Menu::Botao::Texto(pGrafico->carregarFonte("/menuColocacao.ttf"), "", 32);
    Menu::Botao::Texto Fase::textoTempo = Menu::Botao::Texto(pGrafico->carregarFonte("/menuColocacao.ttf"), "", 32);

    Fase::Fase(const IDs::IDs ID_Fase, const IDs::IDs ID_Fundo) :
        Ente(ID_Fase), fundo(ID_Fundo), listaPersonagens(new Lista::ListaEntidade()), listaObstaculos(new Lista::ListaEntidade()),
        pColisao(new Gerenciador::GerenciadorColisao(listaPersonagens, listaObstaculos)),
        GArquivo(), tempo(0.0f)
    {
        if (listaPersonagens == nullptr || listaObstaculos == nullptr) {
            std::cout << "Fase::nao foi possivel criar lista de entidades na fase" << std::endl;
            exit(1);
        }

        if (pColisao == nullptr) {
            std::cout << "Fase::nao foi possivel criar um Gerenciador de Colisao" << std::endl;
            exit(1);
        }

        if (observadorFase == nullptr) {
            observadorFase = new Observador::ObservadorFase();
        }

        observadorFase->setFase(this);
        if (textoPontuacao.getString() == "" && textoTempo.getString() == "") {
            textoPontuacao.setString("Pontos: 00000");
            textoPontuacao.setTamanhoBorda(2);
            textoTempo.setString("Tempo 00:00");
            textoTempo.setTamanhoBorda(2);
        }
    }

    Fase::~Fase() {
        if (pColisao != nullptr) {
            delete(pColisao);
            pColisao = nullptr;
        }
        if (observadorFase != nullptr) {
            delete(observadorFase);
            observadorFase = nullptr;
        }

        if (listaPersonagens != nullptr) {
            if (getJogador() != nullptr && pJogador != nullptr) {
                delete(listaPersonagens);
                pJogador = nullptr;
            }
            else {
                delete(listaPersonagens);
            }
            listaPersonagens = nullptr;
        }

        if (listaObstaculos != nullptr) {
            delete(listaObstaculos);
            listaObstaculos = nullptr;
        }

        if (pontuacaoJogador > 0) {
            pontuacaoJogador = 0;
            textoPontuacao.setString("");
            textoTempo.setString("");
        }
    }

    std::vector<std::string> Fase::getAtributosEntidade(std::string linha) {
        std::string espaco = " ";
        size_t pos = 0;
        std::vector<std::string> atributos;
        while ((pos = linha.find(espaco)) != std::string::npos) {
            atributos.push_back(linha.substr(0, pos));
            linha.erase(0, pos + espaco.length());
        }
        return atributos;
    }

    /*void Fase::setDoisJogadores(bool dJ) {
        this->jogador2 = dJ;
    }*/

    void Fase::criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const std::string type, const sf::Vector2f escala) {
        Obstaculo::Plataforma* plataforma = new Obstaculo::Plataforma(IDs::IDs::plataforma, pos, tam, type);
        if (plataforma == nullptr) {
            std::cout << "Fase::nao foi possivel criar plataforma" << std::endl;
            exit(1);
        }
        plataforma->setEscala(escala);
        listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(plataforma));
    }

    void Fase::criarPlataforma(const sf::Vector2f pos, const sf::Vector2f tam, const float distancia, const bool horizontal) {
        Obstaculo::PlataformaMovel* plataformaMovel = new Obstaculo::PlataformaMovel(pos, distancia, tam, horizontal);
        if (plataformaMovel == nullptr) {
            std::cout << "Fase::nao foi possivel criar plataformaMovel" << std::endl;
            exit(1);
        }
        listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(plataformaMovel));
    }

    void Fase::criarCaixa(const sf::Vector2f pos) {
        Obstaculo::Caixa* caixa = new Obstaculo::Caixa(pos);
        if (caixa == nullptr) {
            std::cout << "Fase::nao foi possivel criar caixa" << std::endl;
            exit(1);
        }
        listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(caixa));
    }


    void Fase::criarVida(const sf::Vector2f pos) {
        Item::Vida* vida = new Item::Vida(pos);
        if (vida == nullptr) {
            std::cout << "Fase::nao foi possivel criar vida" << std::endl;
            exit(1);
        }
        listaPersonagens->addEntidade(static_cast<Entidades::Entidade*>(vida));
    }



    void Fase::criarEspinho(const sf::Vector2f pos, const sf::Vector2f tam) {
        Obstaculo::Espinho* espinho = new Obstaculo::Espinho(pos, tam);
        if (espinho == nullptr) {
            std::cout << "Fase::nao foi possivel criar espinhos" << std::endl;
            exit(1);
        }
        listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(espinho));
    }

    void Fase::criarPersonagem(const IDs::IDs ID, const sf::Vector2f pos, const int nivel) {
        Entidades::Entidade* personagem = nullptr;
        Entidades::Entidade* arma = nullptr;
        if (ID == IDs::IDs::jogador) {
            if (pJogador != nullptr) {
                std::cout << "ERRO::pJogador ja existe" << std::endl;
                exit(1);
            }
            Item::Arma* espadaJogador = new Item::Arma(IDs::IDs::espada_jogador);
            if (espadaJogador == nullptr) {
                std::cout << "Fase::nao foi possivel criar espada do jogador" << std::endl;
                exit(1);
            }
            pJogador = new Player::Jogador(pos, espadaJogador);
            if (pJogador == nullptr) {
                std::cout << "Fase::nao foi possivel criar jogador" << std::endl;
                exit(1);
            }
            personagem = static_cast<Entidades::Entidade*>(pJogador);
            arma = static_cast<Entidades::Entidade*>(espadaJogador);
        }
        else {
            if (pJogador == nullptr) {
                std::cout << "ERRO::Fase o ponteiro do jogador eh nullptr" << std::endl;
                exit(1);
            }
            if (ID == IDs::IDs::Lobo) {
                Inimigos::Lobo* Lobo = new Inimigos::Lobo(pos, nivel, pJogador);
                if (Lobo == nullptr) {
                    std::cout << "Fase::nao foi possivel criar Lobo" << std::endl;
                    exit(1);
                }
                Item::Arma* espadaInimigo = new Item::Arma(IDs::IDs::espada_inimigo);
                if (espadaInimigo == nullptr) {
                    std::cout << "Fase::nao foi possivel criar espada Lobo" << std::endl;
                    exit(1);
                }
                Lobo->setArma(espadaInimigo);
                personagem = static_cast<Entidades::Entidade*>(Lobo);
                arma = static_cast<Entidades::Entidade*>(espadaInimigo);
            }
            else if (ID == IDs::IDs::Demonio) {
                Inimigos::Demonio* Demonio = new Inimigos::Demonio(pos, nivel, pJogador);
                if (Demonio == nullptr) {
                    std::cout << "Fase::nao foi possivel criar Demonio" << std::endl;
                    exit(1);
                }
                Item::Projetil* projetil = new Item::Projetil();
                if (projetil == nullptr) {
                    std::cout << "Fase::nao foi possivel criar projetil" << std::endl;
                    exit(1);
                }
                Demonio->setArma(static_cast<Item::Projetil*>(projetil));
                projetil->inicializarAnimacao();
                personagem = static_cast<Entidades::Entidade*>(Demonio);
                arma = static_cast<Entidades::Entidade*>(projetil);
            }
            else if (ID == IDs::IDs::Orc) {
                Inimigos::Orc* Orc = new Inimigos::Orc(pos, nivel, pJogador);
                if (Orc == nullptr) {
                    std::cout << "Fase::nao foi possive criar Orc" << std::endl;
                    exit(1);
                }
                personagem = static_cast<Entidades::Entidade*>(Orc);
            }
        }
        if (personagem != nullptr) {
            listaPersonagens->addEntidade(personagem);
            if (arma != nullptr) {
                listaPersonagens->addEntidade(arma);
            }
        }
    }

    void Fase::criarEntidade(const IDs::IDs ID, const std::vector<std::string> primeiro, const std::vector<std::string> segundo, const bool ehPersonagem) {
        if (ehPersonagem) {
            Entidades::Entidade* personagem = nullptr;
            Entidades::Entidade* arma = nullptr;
            if (ID == IDs::IDs::jogador) {
                if (pJogador != nullptr) {
                    std::cout << "ERRO::pJogador ja existe" << std::endl;
                    exit(1);
                }
                pJogador = new Player::Jogador(primeiro);
                if (pJogador == nullptr) {
                    std::cout << "ERRO::Fase nao foi possivel criar jogador" << std::endl;
                    exit(1);
                }
                Item::Arma* espadaJogador = new Item::Arma(IDs::IDs::espada_jogador, segundo);
                if (espadaJogador == nullptr) {
                    std::cout << "Fase::nao foi possivel criar espada do jogador" << std::endl;
                    exit(1);
                }
                pJogador->setArma(espadaJogador);
                personagem = static_cast<Entidades::Entidade*>(this->pJogador);
                arma = static_cast<Entidades::Entidade*>(espadaJogador);
            }
            else {
                if (pJogador == nullptr) {
                    std::cout << "ERRO::Fase o ponteiro do jogador eh nullptr" << std::endl;
                    exit(1);
                }
                if (ID == IDs::IDs::Lobo) {
                    Inimigos::Lobo* Lobo = new Inimigos::Lobo(primeiro, this->pJogador);
                    if (Lobo == nullptr) {
                        std::cout << "Fase::Lobo eh nullptr" << std::endl;
                        exit(1);
                    }
                    Item::Arma* espadaEsqueleto = new Item::Arma(IDs::IDs::espada_inimigo, segundo);
                    if (espadaEsqueleto == nullptr) {
                        std::cout << "Fase::nao foi possivel criar espada Lobo" << std::endl;
                        exit(1);
                    }
                    Lobo->setArma(espadaEsqueleto);
                    personagem = static_cast<Entidades::Entidade*>(Lobo);
                    arma = static_cast<Entidades::Entidade*>(espadaEsqueleto);
                }
                else if (ID == IDs::IDs::Demonio) {
                    Inimigos::Demonio* Demonio = new Inimigos::Demonio(primeiro, this->pJogador);
                    if (Demonio == nullptr) {
                        std::cout << "Fase::Demonio eh nullptr" << std::endl;
                        exit(1);
                    }
                    Item::Projetil* projetil = new Item::Projetil(segundo, static_cast<Personagens::Personagem*>(Demonio));
                    if (projetil == nullptr) {
                        std::cout << "Fase::projetil eh nullptr" << std::endl;
                        exit(1);
                    }
                    personagem = static_cast<Entidades::Entidade*>(Demonio);
                    arma = static_cast<Entidades::Entidade*>(projetil);
                }
                else if (ID == IDs::IDs::Orc) {
                    Inimigos::Orc* Orc = new Inimigos::Orc(primeiro, pJogador);
                    if (Orc == nullptr) {
                        std::cout << "Fase::Orc eh nullptr" << std::endl;
                        exit(1);
                    }
                    personagem = static_cast<Entidades::Entidade*>(Orc);
                }
                else {
                    std::cout << "Fase::o ID da entidade eh invalido" << std::endl;
                    exit(1);
                }
            }
            if (personagem != nullptr) {
                listaPersonagens->addEntidade(personagem);
                if (arma != nullptr) {
                    listaPersonagens->addEntidade(arma);
                }
            }
        }
        else if (ID == IDs::IDs::plataforma) {
            Obstaculo::Plataforma* plataforma = new Obstaculo::Plataforma(primeiro);
            if (plataforma == nullptr) {
                std::cout << "Fase::nao foi possivel criar plataforma" << std::endl;
                exit(1);
            }
            listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(plataforma));
        }
        else if (ID == IDs::IDs::plataforma_movel) {
            Obstaculo::PlataformaMovel* plataformaMovel = new Obstaculo::PlataformaMovel(primeiro);
            if (plataformaMovel == nullptr) {
                std::cout << "Fase::nao foi possivel criar plataforma movel, pois o ponteiro eh invalido" << std::endl;
                exit(1);
            }
            listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(plataformaMovel));
        }
        else if (ID == IDs::IDs::caixa) {
            Obstaculo::Caixa* caixa = new Obstaculo::Caixa(primeiro);
            if (caixa == nullptr) {
                std::cout << "Fase::nao foi possivel criar caixa" << std::endl;
                exit(1);
            }
            listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(caixa));
        }

        else if (ID == IDs::IDs::vida) {
            Item::Vida* vida = new Item::Vida(primeiro);
            if (vida == nullptr) {
                std::cout << "Fase::nao foi possivel criar vida" << std::endl;
                exit(1);
            }
            listaPersonagens->addEntidade(static_cast<Entidades::Entidade*>(vida));
        }

        else if (ID == IDs::IDs::espinho) {
            Obstaculo::Espinho* espinho = new Obstaculo::Espinho(primeiro);
            if (espinho == nullptr) {
                std::cout << "Fase::nao foi possivel criar espinhos" << std::endl;
                exit(1);
            }
            listaObstaculos->addEntidade(static_cast<Entidades::Entidade*>(espinho));
        }
        else {
            std::cout << "ERRO::nao foi possivel criar entidade, pois o id eh invalido" << std::endl;
            exit(1);
        }
    }

    Player::Jogador* Fase::getJogador() {
        for (int i = 0; i < listaPersonagens->getTam(); i++) {
            Entidades::Entidade* ent = listaPersonagens->operator[](i);
            if (ent->getID() == IDs::IDs::jogador) {
                return dynamic_cast<Player::Jogador*>(ent);
            }
        }
        return nullptr;
    }


    void Fase::mudarEstadoObservador() {
        observadorFase->mudarEstadoAtivar();
    }

    /*void Fase::mudarFase(const IDs::IDs ID_Fase) {
        observadorFase->setFase(this);
        if (getJogador() == nullptr && pJogador != nullptr) {
            listaPersonagens->addEntidade(static_cast<Entidades::Entidade*>(pJogador), 0);
            listaPersonagens->addEntidade(static_cast<Entidades::Entidade*>(pJogador->getArma()), 1);
            if (ID_Fase != IDs::IDs::vazio) {
                std::vector<Entidades::Entidade*> entidades = listaObstaculos->getEntidades(IDs::IDs::porta);
                if (entidades.size() <= 0) {
                    std::cout << "ERRO::mudar fase, pois nao ha portas nesta fase" << std::endl;
                    exit(1);
                }
                for (int i = 0; i < entidades.size(); i++) {
                    Entidades::Obstaculo::Porta* porta = dynamic_cast<Entidades::Obstaculo::Porta*>(entidades[i]);
                    if (porta->getIDFase() == ID_Fase) {
                        sf::Vector2f pos(porta->getPos());
                        sf::Vector2f tam(porta->getTam());
                        pJogador->setPos(sf::Vector2f(pos.x + tam.x / 2.0f - pJogador->getTam().x / 2.0f, pos.y));
                        pGrafico->atualizarCamera(pJogador->getPos(), pJogador->getTam());
                        fundo.atualizarPosicao();
                        pGrafico->setLimiteCamera(limiteCamera);
                        return;
                    }
                }
            }
        }
    }*/


    void Fase::removerJogadorLista() {
        if (getJogador() != nullptr && pJogador != nullptr) {
            listaPersonagens->removerEntidade(static_cast<Entidades::Entidade*>(pJogador), false);
            listaPersonagens->removerEntidade(static_cast<Entidades::Entidade*>(pJogador->getArma()), false);
        }
    }

    void Fase::desenhar() {
        fundo.executar();
        pGrafico->desenhaElemento(textoPontuacao.getTexto());
        pGrafico->desenhaElemento(textoTempo.getTexto());
        listaObstaculos->desenharEntidades();
        listaPersonagens->desenharEntidades();
    }

    const unsigned int Fase::getPontuacaoJogador() const {
        return pontuacaoJogador;
    }

    void Fase::setPontuacao(const unsigned int pontuacaoJogador) {
        this->pontuacaoJogador = pontuacaoJogador;
        std::string pontos = std::to_string(this->pontuacaoJogador);
        while (pontos.size() < 5) {
            std::string aux = pontos;
            pontos = '0' + aux;
        }
        textoPontuacao.setString("Pontos: " + pontos);
    }

    void Fase::atualizarTempo() {
        //atualiza posi��o e o tempo
        tempo += pGrafico->getTempo();
        if (tempo >= 1.0f) {
            tempo = 0.0f;
            std::string stringCortada = textoTempo.getString().substr(6);
            std::string novaString = "Tempo ";
            //int doisPontos = stringCortada.find(":");
            int minutos = std::stoi(stringCortada.substr(0, 2));
            int segundos = std::stoi(stringCortada.substr(3, 5));
            if (segundos >= 59) {
                minutos++;
                segundos = 0;
                //novaString += std::to_string(minutos)
            }
            else {
                segundos++;
            }
            if (minutos < 10) {
                novaString += "0" + std::to_string(minutos);
            }
            else {
                novaString += std::to_string(minutos);
            }
            if (segundos < 10) {
                novaString += ":0" + std::to_string(segundos);
            }
            else {
                novaString += ":" + std::to_string(segundos);
            }
            textoTempo.setString(novaString);
        }
        sf::Vector2f posFundo(pGrafico->getCamera().getCenter());
        textoTempo.setPos(sf::Vector2f(posFundo.x - textoTempo.getTam().x / 2.0f + 20.0f, posFundo.y - pGrafico->getTamJanela().y / 2.0f + 10.0f));
        pGrafico->desenhaElemento(textoTempo.getTexto());
    }

    void Fase::atualizarPontuacao() {
        sf::Vector2f posFundo(pGrafico->getCamera().getCenter());
        sf::Vector2f tamJanela(pGrafico->getTamJanela());
        textoPontuacao.setPos(sf::Vector2f(posFundo.x - tamJanela.x / 2.0f + 20.0f, posFundo.y - tamJanela.y / 2.0f + 10.0f));
        pGrafico->desenhaElemento(textoPontuacao.getTexto());
    }

    const std::string Fase::salvar() {
        std::string linha = "";
        linha += std::to_string(static_cast<int>(ID)) + ' ';
        linha += 10;
        linha += std::to_string(this->pontuacaoJogador) + ' ';
        linha += 10;
        linha += textoTempo.getString();
        return linha;
    }

    const std::vector<std::string> Fase::salvarEntidades() {
        std::vector<std::string> linhas;
        for (int i = 0; i < listaPersonagens->getTam(); i++) {
            Entidades::Entidade* entidade = listaPersonagens->operator[](i);
            if (entidade != nullptr) {
                std::string linha = entidade->salvar();
                linhas.push_back(linha);
            }
        }
        for (int i = 0; i < listaObstaculos->getTam(); i++) {
            Entidades::Entidade* entidade = listaObstaculos->operator[](i);
            if (entidade != nullptr) {
                std::string linha = entidade->salvar();
                linhas.push_back(linha);
            }
        }
        return linhas;
    }

    void Fase::setLimiteCamera(sf::IntRect limiteCamera) {
        this->limiteCamera = limiteCamera;
    }

    const sf::IntRect Fase::getLimiteCamera() const {
        return limiteCamera;
    }

    void Fase::executar() {
        pJogador = getJogador();
        if (pJogador) {
            //atualiza fundo
            fundo.executar();

            //atualizar camera
            pGrafico->atualizarCamera(pJogador->getPos(), pJogador->getTam());

            //atualiza e desenha entidades
            listaObstaculos->executar();
            listaPersonagens->executar();

            atualizarTempo();
            atualizarPontuacao();

            //verifica colis�o
            pColisao->executar();
        }
        else {
            observadorFase->notificarJogadorMorreu();
            pJogador = nullptr;
        }
    }

}