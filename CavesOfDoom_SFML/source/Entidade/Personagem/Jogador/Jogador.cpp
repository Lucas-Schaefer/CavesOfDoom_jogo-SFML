#include "../../../../headers/Entidade/Personagem/Jogador/Jogador.hpp"
#include "../../../../headers/Observador/ObservadorJogador.hpp"
#include "../../../../headers/Entidade/Personagem/Inimigo/Inimigo.hpp"
#include "../../../../headers/Entidade/Item/Vida.hpp"
#include "../../../../headers/Entidade/Item/Projetil.hpp"
#include "../../../../headers/Entidade/Obstaculo/Espinho.hpp"

#include <cmath>


namespace Entidades {

    namespace Personagens {

        namespace Player {

            Jogador::Jogador(const sf::Vector2f pos, Item::Arma* arma) :
                Personagem(pos, sf::Vector2f(TAMANHO_JOGADOR_X, TAMANHO_JOGADOR_Y), VELOCIDADE_JOGADOR, IDs::IDs::jogador, TEMPO_JOGADOR_MORRER, TEMPO_JOGADOR_TOMARDANO),
                noChao(false), observadorJogador(new Observador::ObservadorJogador(this)),
                textoExp(pGrafico->carregarFonte("fonte/menuColocacao.ttf"), "", 20),
                jogador2(false)
            {
                this->pontos = 0;
                if (observadorJogador == nullptr) {
                    std::cout << "ERROR::Entidade::Personagem::Jogador::Jogador::nao foi possivel criar um observador para o jogador" << std::endl;
                    exit(1);
                }
                inicializarAnimacao();
                inicializarBarraVida();
                inicializarBarraXP();
                inicializarNivel();
                inicializarExp();

                if (arma != nullptr) {
                    setArma(arma);
                    arma->setDano(nivel.getForca());
                }

                pGrafico->setLimiteObjeto(sf::IntRect(pos.x, pos.y, tam.x, tam.y));
            }

            Jogador::Jogador(const std::vector<std::string> atributos) :
                Personagem(pos, sf::Vector2f(TAMANHO_JOGADOR_X, TAMANHO_JOGADOR_Y), VELOCIDADE_JOGADOR, IDs::IDs::jogador, TEMPO_JOGADOR_MORRER, TEMPO_JOGADOR_TOMARDANO),
                noChao(false), observadorJogador(new Observador::ObservadorJogador(this)),
                textoExp(pGrafico->carregarFonte("fonte/menuColocacao.ttf"), "", 20)
            {
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
                    const bool noChaoAtual = atributos[18] == "1";
                    const std::string imgAtual = atributos[21];
                    const unsigned int quadroAtual = std::stoi(atributos[22]);
                    const float tempoTotalAtual = std::stof(atributos[23]);
                    const unsigned int pontosAtual = std::stoi(atributos[24]);

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
                    this->pontos = pontosAtual;
                    nivel.setNivel(nivelAtual);
                    nivel.addExp(experienciaAtual);
                    inicializarNivel();
                    this->noChao = noChaoAtual;

                    inicializarAnimacao();
                    inicializarBarraVida();
                    inicializarBarraXP();
                    inicializarExp();
                    animacao.setImgAtual(imgAtual);
                    animacao.setQuadroAtual(quadroAtual);
                    animacao.setTempoTotal(tempoTotalAtual);

                    pGrafico->setLimiteObjeto(sf::IntRect(pos.x, pos.y, tam.x, tam.y));
                }
                catch (const std::exception& e) {
                    std::cerr << e.what() << std::endl;
                    podeRemover = true;
                }
            }

            Jogador::~Jogador() {
                if (observadorJogador) {
                    delete(observadorJogador);
                    observadorJogador = nullptr;
                }
                if (tuboBarraVida.getTexture()) {
                    delete(tuboBarraVida.getTexture());
                }

                if (barraVida.getTexture()) {
                    delete(barraVida.getTexture());
                }

                if (tuboBarraXP.getTexture()) {
                    delete(tuboBarraXP.getTexture());
                }

                if (barraXP.getTexture()) {
                    delete(barraXP.getTexture());
                }
            }

            void Jogador::inicializarBarraVida() {
                sf::Vector2f tamTubo = sf::Vector2f(BARRA_VIDA_JOGADOR_X, BARRA_VIDA_JOGADOR_Y);
                tuboBarraVida.setSize(tamTubo);
                barraVida.setSize(tamTubo);
                sf::Texture* texturaVida = new sf::Texture();
                sf::Texture* texturaBarra = new sf::Texture();
                texturaVida->loadFromFile("imagens/Jogador/VidaJogador.png");
                texturaBarra->loadFromFile("/BarraVida.png");
                barraVida.setTexture(texturaVida);
                tuboBarraVida.setTexture(texturaBarra);
            }

            void Jogador::inicializarBarraXP() {
                sf::Vector2f tamTubo = sf::Vector2f(BARRA_VIDA_JOGADOR_X, BARRA_VIDA_JOGADOR_Y);
                tuboBarraXP.setSize(tamTubo);
                sf::Texture* texturaXP = new sf::Texture();
                sf::Texture* texturaBarra = new sf::Texture();
                texturaXP->loadFromFile("imagens/Jogador/XPJogador.png");
                texturaBarra->loadFromFile("imagens/Jogador/BarraXP.png");
                barraXP.setTexture(texturaXP);
                tuboBarraXP.setTexture(texturaBarra);
            }

            void Jogador::inicializarExp() {
                std::string expAtual = std::to_string(nivel.getExp());
                expAtual = expAtual.substr(0, expAtual.find(".") + 2);
                std::string expProxNivel = std::to_string(nivel.getExpProxNivel());
                expProxNivel = expProxNivel.substr(0, expProxNivel.find(".") + 2);
                textoExp.setString(expAtual + "/" + expProxNivel);
                textoExp.setTamanhoBorda(2);
            }


            void Jogador::inicializarAnimacao() {
                if (getJogador2() == true)
                {
                    const sf::Vector2f origin = sf::Vector2f(tam.x / 2.5f, tam.y / 2.1f);
                    animacao.addAnimacao("imagens/Jogador/RunJogador2.png", "ANDA", 10, 0.12f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/AttackJogador2.png", "ATACA", 10, 0.065f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/StoppedJogador2.png", "PARADO", 10, 0.15f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/JumpJogador2.png", "PULA", 3, 0.15f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/FallJogador2.png", "CAI", 3, 0.15f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/DeathJogador2.png", "MORRE", 10, 0.10f, sf::Vector2f(5, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/HitJogador2.png", "TOMADANO", 1, 0.5f, sf::Vector2f(6, 2), origin);
                }
                else {
                    const sf::Vector2f origin = sf::Vector2f(tam.x / 2.5f, tam.y / 2.1f);
                    animacao.addAnimacao("imagens/Jogador/RunJogador.png", "ANDA", 10, 0.12f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/AttackJogador.png", "ATACA", 10, 0.065f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/StoppedJogador.png", "PARADO", 10, 0.15f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/JumpJogador.png", "PULA", 3, 0.15f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/FallJogador.png", "CAI", 3, 0.15f, sf::Vector2f(6, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/DeathJogador.png", "MORRE", 10, 0.10f, sf::Vector2f(5, 2), origin);
                    animacao.addAnimacao("imagens/Jogador/HitJogador.png", "TOMADANO", 1, 0.5f, sf::Vector2f(6, 2), origin);
                }
            }

            void Jogador::atualizarBarraVida() {
                sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                sf::Vector2f tamJanela = pGrafico->getTamJanela();
                sf::Vector2f posBarra = sf::Vector2f(posJanela.x - tamJanela.x / 2.0f + 10.0f, posJanela.y + tamJanela.y / 2.0f - 30.0f);
                tuboBarraVida.setPosition(posBarra);
                barraVida.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 40.0f) * (vida / 100.0f), BARRA_VIDA_JOGADOR_Y - 13.0f));
                barraVida.setPosition(sf::Vector2f(posBarra.x + 7.0f, posBarra.y + tuboBarraVida.getSize().y / 2.0f - barraVida.getSize().y / 2.0f));
            }

            void Jogador::atualizarBarraXP() {
                sf::Vector2f posJanela = pGrafico->getCamera().getCenter();
                sf::Vector2f tamJanela = pGrafico->getTamJanela();
                sf::Vector2f posBarra = sf::Vector2f(posJanela.x + tamJanela.x / 2.0f - tuboBarraXP.getSize().x - 10.0f, posJanela.y + tamJanela.y / 2.0f - 30.0f);
                tuboBarraXP.setPosition(posBarra);
                barraXP.setSize(sf::Vector2f((BARRA_VIDA_JOGADOR_X - 40.0f) * (nivel.getExp() / nivel.getExpProxNivel()), BARRA_VIDA_JOGADOR_Y - 13.0f));
                barraXP.setPosition(sf::Vector2f(posBarra.x + tuboBarraXP.getSize().x - barraXP.getSize().x - 7.0f, posBarra.y + tuboBarraXP.getSize().y / 2.0f - barraXP.getSize().y / 2.0f));
            }

            void Jogador::atualizarExp() {
                sf::Vector2f posBarraXP(tuboBarraXP.getPosition());
                textoExp.setPos(sf::Vector2f(posBarraXP.x + tuboBarraXP.getSize().x - textoExp.getTam().x - 5.0f, posBarraXP.y - textoExp.getTam().y - 12.0f));
            }



            void Jogador::atualizarAnimacao() {
                if (morrendo) {
                    animacao.atualizar(paraEsquerda, "MORRE");
                    tempoMorrer += pGrafico->getTempo();
                    if (tempoMorrer > tempoAnimacaoMorrer) {
                        podeRemover = true;
                        tempoMorrer = 0.0f;
                    }
                }
                else if (!noChao && velFinal.y > 0.0f) {
                    animacao.atualizar(paraEsquerda, "CAI");
                }
                else if (!noChao) {
                    animacao.atualizar(paraEsquerda, "PULA");
                }
                else if (levandoDano) {
                    animacao.atualizar(paraEsquerda, "TOMADANO");
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

            void Jogador::inicializarNivel() {
                textoNivel.setTamFonte(20);
                textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                textoNivel.setTamanhoBorda(2);
                nivel.setForca(FORCA_JOGADOR);
                nivel.setDefesa(DEFESA_JOGADOR);
                nivel.setVitalidade(VITALIDADE_JOGADOR);
            }

            void Jogador::atualizarNivel() {
                sf::Vector2f posBarra = tuboBarraVida.getPosition();
                textoNivel.setPos(sf::Vector2f(posBarra.x + 5.0f, posBarra.y - textoNivel.getTam().y - 12.0f));
            }

            void Jogador::colisao(Entidade* outraEntidade, sf::Vector2f ds) {
                switch (outraEntidade->getID()) {
                case(IDs::IDs::plataforma):
                {

                }
                break;
                case(IDs::IDs::espada_inimigo):
                {
                    //std::cout << "Tomar dano do inimigo" << std::endl;
                    Item::Arma* arma = dynamic_cast<Item::Arma*>(outraEntidade);
                    tomarDano(arma->getDano());
                }
                break;
                case(IDs::IDs::Lobo):
                {
                    //empura inimigo
                    sf::Vector2f posInimigo = outraEntidade->getPos();
                    Inimigos::Inimigo* inimigo = dynamic_cast<Inimigos::Inimigo*>(outraEntidade);
                    if (pos.x < posInimigo.x) {
                        ds.x *= -1;
                    }
                    //bate no jogador
                    inimigo->parar();
                    inimigo->atacar(true);
                }
                break;
                case (IDs::IDs::vida):
                {
                    Item::Vida* vida = dynamic_cast<Item::Vida*>(outraEntidade);
                    setVida(vida->getVida());
                    vida->remover();
                }
                break;
                case(IDs::IDs::projetil_inimigo):
                {
                    Item::Projetil* projetil = dynamic_cast<Item::Projetil*>(outraEntidade);
                    tomarDano(projetil->getDano());
                    projetil->setColidiu(true);
                }
                break;

                case (IDs::IDs::espinho):
                {
                    Obstaculo::Espinho* espinho = dynamic_cast<Obstaculo::Espinho*>(outraEntidade);
                    tomarDano(espinho->getDano());
                    if (!morrendo) {
                        velFinal.y = -sqrt(2.0f * GRAVIDADE * TAMANHO_PULO);
                    }
                }
                break;

                }
            }

            void Jogador::pular() {
                if (noChao) {
                    velFinal.y = -sqrt(2.0f * GRAVIDADE * TAMANHO_PULO);
                    noChao = false;
                    atacando = false;
                }
            }

            const bool Jogador::getNoChao() const {
                return noChao;
            }

            const bool Jogador::getAndando() const {
                return andando;
            }


            void Jogador::podePular() {
                noChao = true;
            }

            void Jogador::mudarEstadoObservador() {
                observadorJogador->mudarEstadoAtivar();
            }


            void Jogador::addPontuacao(const unsigned int pontos) {
                this->pontos += pontos;
                observadorJogador->atualizarPontuacao(this->pontos);
            }

            void Jogador::addExperiencia(const float experiencia) {
                nivel.addExp(experiencia);
                textoNivel.setString("Lv." + std::to_string(nivel.getNivel()));
                inicializarExp();
            }

            void Jogador::setVida(const float vida) {
                this->vida += vida;
                if (this->vida > 100.0f) {
                    this->vida = 100.0f;
                }
            }

            const std::string Jogador::salvar() {
                std::string linha = salvarPersonagem();
                linha += std::to_string(noChao) + ' ';
                linha += animacao.getImgAtual() + ' ';
                linha += std::to_string(animacao.getQuadroAtual()) + ' ';
                linha += std::to_string(animacao.getTempoTotal()) + ' ';
                linha += std::to_string(pontos);
                return linha;
            }

            void Jogador::desenhar() {
                pGrafico->desenhaElemento(corpo);
                pGrafico->desenhaElemento(tuboBarraVida);
                pGrafico->desenhaElemento(barraVida);
                pGrafico->desenhaElemento(textoNivel.getTexto());
                pGrafico->desenhaElemento(tuboBarraXP);
                pGrafico->desenhaElemento(barraXP);
                pGrafico->desenhaElemento(textoExp.getTexto());
            }

            void Jogador::setJogador2(bool jog2)
            {
                jogador2 = jog2;
            }

            bool Jogador::getJogador2()
            {
                return jogador2;
            }

            void Jogador::atualizar() {

                atualizarPosicao();

                if (atacando) {
                    sf::Vector2f tamEspada = arma->getTam();
                    const float posY = pos.y;
                    sf::Vector2f posEspada = (paraEsquerda ? sf::Vector2f(pos.x - tamEspada.x, pos.y) : sf::Vector2f(pos.x + tam.x, pos.y));
                    arma->setPos(posEspada);
                }
                else {
                    arma->setPos(sf::Vector2f(-1000.0f, -1000.0f));
                }

                atualizarAnimacao();

                atualizarBarraVida();

                atualizarBarraXP();

                atualizarNivel();

                atualizarExp();

            }

        }

    }

}
