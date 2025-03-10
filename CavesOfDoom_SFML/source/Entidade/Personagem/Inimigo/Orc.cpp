#include "../../../../headers/Entidade/Personagem/Inimigo/Orc.hpp"


namespace Entidades {

    namespace Personagens {

        namespace Inimigos {

            Orc::Orc(const sf::Vector2f pos, const int nivel, Player::Jogador* jogador) :
                Inimigo(
                    pos,
                    sf::Vector2f(TAMANHO_ORC_X, TAMANHO_ORC_Y),
                    jogador,
                    IDs::IDs::Orc,
                    TEMPO_ORC_MORRER,
                    2.0f,
                    EXPERIENCIA_ORC* nivel * 0.5f
                ), raiva(false), tempoRaiva(0.0f)
            {
                this->nivel.setNivel(nivel);
                this->pontos = PONTOS_ORC;
                inicializarAnimacao();
                inicializarNivel();
            }

            Orc::Orc(const std::vector<std::string> atributos, Player::Jogador* jogador) :
                Inimigo(
                    sf::Vector2f(0.0f, 0.0f),
                    sf::Vector2f(TAMANHO_ORC_X, TAMANHO_ORC_Y),
                    jogador,
                    IDs::IDs::Orc,
                    TEMPO_ORC_MORRER,
                    2.0f,
                    EXPERIENCIA_ORC
                )
            {
                this->pontos = PONTOS_ORC;
                try {
                    const sf::Vector2f posAtual = sf::Vector2f(std::stof(atributos[1]), std::stof(atributos[2]));
                    const sf::Vector2f tamAtual = sf::Vector2f(std::stof(atributos[3]), std::stof(atributos[4]));
                    const sf::Vector2f velFinalAtual = sf::Vector2f(std::stof(atributos[5]), std::stof(atributos[6]));
                    const bool andandoAtual = atributos[7] == "1";
                    const bool paraEsquerdaAtual = atributos[8] == "1";
                    const bool levandoDanoAtual = atributos[9] == "1";
                    const bool atacandoAtual = atributos[10] == "1";
                    const bool morrendoAtual = atributos[11] == "1";
                    const float vidaAtual = std::stof(atributos[12]);
                    const float tempoDanoAtual = std::stof(atributos[13]);
                    const float tempoMorrerAtual = std::stof(atributos[14]);
                    const float dtAtual = std::stof(atributos[15]);
                    const float nivelAtual = std::stoi(atributos[16]);
                    const float experienciaAtual = std::stof(atributos[17]);
                    const short moveAleatorioAtual = std::stol(atributos[18]);
                    const float tempoMoverAtual = std::stof(atributos[19]);
                    const float tempoAtacarAtual = std::stof(atributos[20]);
                    const std::string imgAtual = atributos[21];
                    const unsigned int quadroAtual = std::stoi(atributos[22]);
                    const float tempoTotalAtual = std::stof(atributos[23]);
                    const bool raivaAtual = atributos[24] == "1";
                    const float tempoRaivaAtual = std::stof(atributos[25]);

                    setPos(posAtual);
                    setTam(tamAtual);
                    setVelFinal(velFinalAtual);
                    this->andando = andandoAtual;
                    this->paraEsquerda = paraEsquerdaAtual;
                    this->levandoDano = levandoDanoAtual;
                    this->atacando = atacandoAtual;
                    this->morrendo = morrendoAtual;
                    this->vida = vidaAtual;
                    this->tempoDano = tempoDanoAtual;
                    this->tempoMorrer = tempoMorrerAtual;
                    this->dt = dtAtual;
                    inicializarNivel();
                    nivel.setNivel(nivelAtual);
                    nivel.addExp(experienciaAtual);
                    this->moveAleatorio = moveAleatorioAtual;
                    this->tempoMover = tempoMoverAtual;
                    this->tempoAtacar = tempoAtacarAtual;
                    this->raiva = raivaAtual;
                    this->tempoRaiva = tempoRaivaAtual;

                    inicializarAnimacao();
                    animacao.setImgAtual(imgAtual);
                    animacao.setQuadroAtual(quadroAtual);
                    animacao.setTempoTotal(tempoTotalAtual);
                }
                catch (const std::exception& e)
                {
                    std::cerr << e.what() << std::endl;
                    podeRemover = true;
                }

            }

            Orc::~Orc() {

            }

            void Orc::inicializarAnimacao() {
                const sf::Vector2f origin = sf::Vector2f(tam.x / 12.0f, tam.y / 10.0f);
                animacao.addAnimacao("imagens/Orc/StoppedOrc.png", "PARADO", 12, 0.12f, sf::Vector2f(1.7f, 2.0f), origin);
                animacao.addAnimacao("imagens/Orc/RunOrc.png", "ANDA", 7, 0.15f, sf::Vector2f(1.7f, 2.0f), origin);
                animacao.addAnimacao("imagens/Orc/DeathOrc.png", "MORRE", 28, 0.10f, sf::Vector2f(1.7f, 2.0f), origin);
                animacao.addAnimacao("imagens/Orc/AttackOrc.png", "ATACA", 16, 0.15f, sf::Vector2f(1.7f, 2.0f), sf::Vector2f(tam.x / 3.0f, tam.y / 4.0f));
                corPadrao = corpo.getFillColor();
                if (raiva) {
                    corpo.setFillColor(sf::Color(180, 0, 0));
                }
            }

            void Orc::inicializarNivel() {
                textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                textoNivel.setTamanhoBorda(2);
                if (arma != nullptr) {
                    setArma(arma);
                    arma->setDano(this->nivel.getForca());
                }
            }

            void Orc::atualizarRaiva() {
                if (raiva) {
                    tempoRaiva += pGrafico->getTempo();
                    if (tempoRaiva > 8.0f) {
                        tempoRaiva = 0.0f;
                        corpo.setFillColor(corPadrao);
                        raiva = false;
                    }
                }
            }

            void Orc::atualizarAnimacao() {
                if (morrendo) {
                    animacao.atualizar(paraEsquerda, "MORRE");
                    tempoMorrer += pGrafico->getTempo();
                    if (tempoMorrer > tempoAnimacaoMorrer) {
                        podeRemover = true;
                        tempoMorrer = 0.0f;
                        if (arma != nullptr) {
                            arma->remover();
                        }
                    }
                }
                else if (atacando) {
                    animacao.atualizar(paraEsquerda, "ATACA");
                }
                else if (andando) {
                    animacao.atualizar(paraEsquerda, "ANDA");
                }
                else {
                    animacao.atualizar(paraEsquerda, "PARADO");
                }
            }

            void Orc::tomarDano(const float dano) {
                if (!levandoDano) {
                    levandoDano = true;
                    if (!raiva && rand() % 2 == 1) {
                        corpo.setFillColor(sf::Color(180, 0, 0));
                        raiva = true;
                    }
                    vida -= dano * (dano / (dano + nivel.getDefesa()));
                    if (vida <= 0.0f) {
                        morrendo = true;
                        vida = 0.0f;
                        if (arma != nullptr) {
                            arma->remover();
                        }
                    }
                    tempoDano = 0.0f;
                }
            }

            const std::string Orc::salvar() {
                std::string linha = salvarInimigo();
                linha += std::to_string(raiva) + ' ';
                linha += std::to_string(tempoRaiva);
                return linha;
            }

            void Orc::atualizarTempoAtacar() {
                if (atacando && (raiva || !levandoDano)) {
                    tempoAtacar += pGrafico->getTempo();
                    if (tempoAtacar > tempoAnimacaoAtacar) {
                        atacando = false;
                        arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                        tempoAtacar = 0.0f;
                    }
                    else if (tempoAtacar > tempoAnimacaoAtacar / 1.5f) {
                        arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                    }
                    else if (tempoAtacar > tempoAnimacaoAtacar / 1.7f) {
                        sf::Vector2f posEspada = (paraEsquerda ? sf::Vector2f(pos.x - arma->getTam().x / 2.0f, pos.y) : sf::Vector2f(pos.x + tam.x / 2.0f, pos.y));
                        arma->setPos(posEspada);
                    }
                }
                else if (levandoDano && !raiva) {
                    tempoAtacar = 0.0f;
                    atacando = false;
                    arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                }
                atualizarRaiva();
            }

            void Orc::moveInimigo() {
                if ((raiva || !levandoDano) && !morrendo && !atacando) {
                    sf::Vector2f posJogador = jogador->getPos();
                    sf::Vector2f posInimigo = getPos();
                    if (fabs(posJogador.x - posInimigo.x) <= RAIO_PERSEGUIR_X && fabs(posJogador.y - posInimigo.y) <= RAIO_PERSEGUIR_Y) {
                        if (posJogador.x - posInimigo.x > 0.0f) {
                            andar(false);
                        }
                        else {
                            andar(true);
                        }
                    }
                    else {
                        atualizaMovimentoAleatorio();
                    }
                }
                else {
                    tempoMover = 0.0f;
                }
            }

        }

    }

}