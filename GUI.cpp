#include <map>
#include <vector>
#include <chrono>

#include <SFML/Graphics.hpp>

#include <iostream>

#include "GUI.hpp"
#include "pecas.hpp"
#include "tabuleiro.hpp"
#include "utilidades.hpp"

#define LADOTABULEIRO 1080
#define LADOPECA 135

// Indice onde estao os sprites no vector Sprites
enum e_numSprite {
	TABULEIRO,
	CASAMOVIMENTO,
	REIPRETO, REIBRANCO,
	PEAOPRETO, PEAOBRANCO,
	RAINHAPRETO, RAINHABRANCO,
	BISPOPRETO, BISPOBRANCO,
	TORREPRETO, TORREBRANCO,
	CAVALOPRETO, CAVALOBRANCO,
	XEQUEMATE,
	NUMSPRITES};
	
// Caminho ate imagens do jogo
const std::array<std::string, NUMSPRITES> IMAGENS = {
	"./resources/tabuleiro.png",
	"./resources/tab_quad.png",
	"./resources/rei_preto.png", "./resources/rei_branco.png",
	"./resources/peao_preto.png", "./resources/peao_branco.png",
	"./resources/rainha_preto.png", "./resources/rainha_branco.png",
	"./resources/bispo_preto.png", "./resources/bispo_branco.png",
	"./resources/torre_preto.png", "./resources/torre_branco.png",
	"./resources/cavalo_preto.png", "./resources/cavalo_branco.png",
	"./resources/xeque_mate.png"};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Construtores e destrutores da classe c_interfaceJogo
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

c_interfaceJogo::c_interfaceJogo(const std::string _Titulo, c_tabuleiro *_JogoMostrado, const e_cor _Lado, const int _Altura, const int _Largura) {
	JogoMostrado = _JogoMostrado;
	Lado = _Lado;

	MovimentoEscolhido = nullptr;

	Largura = _Largura;
	Altura = _Altura;

	Janela = new sf::RenderWindow(sf::VideoMode(Largura, Altura), _Titulo, sf::Style::Close | sf::Style::Titlebar);

	carregar_texturas();

	SpriteTabuleiro.setTexture(Texturas[TABULEIRO]);

	ajustar_sprites();

	PosXTabuleiro = 0;
	PosYTabuleiro = 0;

	return;
}

c_interfaceJogo::c_interfaceJogo(const std::string _Titulo, c_tabuleiro *_JogoMostrado, const e_cor _Lado) {
	JogoMostrado = _JogoMostrado;
	Lado = _Lado;

	MovimentoEscolhido = nullptr;

	Largura = menor(sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().width) * 0.75;
	Altura = Largura;

	Janela = new sf::RenderWindow(sf::VideoMode(Largura, Altura), _Titulo, sf::Style::Close | sf::Style::Titlebar);

	carregar_texturas();
	
	XequeMate = true;

	SpriteTabuleiro.setTexture(Texturas[TABULEIRO]);

	ajustar_sprites();

	PosXTabuleiro = 0;
	PosYTabuleiro = 0;

	return;
}

c_interfaceJogo::~c_interfaceJogo() {
	Janela -> close();

	delete Janela;
	Janela = nullptr;

	SpritesBrancas.clear();
	SpritesPretas.clear();
	SpritesMovimentos.clear();

	Texturas.clear();

	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Metodos publicos da classe c_interfaceJogo
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void c_interfaceJogo::desenhar_janela() {
	atualizar_posicao();

	while(Janela -> isOpen()) {
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
		
		sf::Event _Event;
        while(Janela -> pollEvent(_Event)) {
            switch(_Event.type) {
				case sf::Event::Closed:
					Janela -> close();
					break;

				case sf::Event::MouseButtonPressed:
					if(!JogoMostrado -> get_promocao()) {
						localizar_clique(_Event.mouseButton.x, _Event.mouseButton.y);

					}
					break;

				case sf::Event::Resized:
					Largura = _Event.size.width;
					Altura = _Event.size.height;

					Janela -> setView(sf::View(sf::Vector2f(Largura / 2, Altura / 2), sf::Vector2f(Largura, Altura)));

					ajustar_sprites();
					atualizar_posicao();
					break;

				default:
					break;


			}
        }

		executar_movimentos();
		atualizar_posicao();
		
		Janela -> clear();

		Janela -> draw(SpriteTabuleiro);

		for(auto i: SpritesBrancas) {
			Janela -> draw(i.Sprite);

		}

		for(auto i: SpritesPretas) {
			Janela -> draw(i.Sprite);

		}

		for(auto i: SpritesXeque) {
			Janela -> draw(i);

		}

		for(auto i: SpritesMovimentos) {
			Janela -> draw(i.Sprite);

		}
		
		if(XequeMate) {
			Janela -> draw(ImagemMate);
			
		}


		Janela -> display();

	}

	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Metodos privados da classe c_interfaceJogo
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void c_interfaceJogo::carregar_texturas() {
	for(auto i: IMAGENS) {
		sf::Texture _Textura;
		if(!_Textura.loadFromFile(i)) {
			std::clog << "log: Erro ao carregar arquivo " << i << std::endl;
			continue;

		}
		Texturas.push_back(_Textura);

	}
	
	ImagemMate.setTexture(Texturas[XEQUEMATE]);
	ImagemMate.setScale(0.70f, 0.70f);
	ImagemMate.setOrigin(400, 150);
	ImagemMate.setPosition(Largura / 2, Altura / 2);

	return;
}

void c_interfaceJogo::ajustar_sprites() {
	for(auto &i: SpritesBrancas) {
		i.Sprite.setScale(menor(Altura, Largura) / float(8 * LADOPECA), menor(Altura, Largura) / float(8 * LADOPECA));

	}
	for(auto &i: SpritesPretas) {
		i.Sprite.setScale(menor(Altura, Largura) / float(8 * LADOPECA), menor(Altura, Largura) / float(8 * LADOPECA));

	}
	for(auto &i: SpritesMovimentos) {
		i.Sprite.setScale(menor(Altura, Largura) / float(8 * LADOPECA), menor(Altura, Largura) / float(8 * LADOPECA));

	}
	for(auto &i: SpritesXeque) {
		i.setScale(menor(Altura, Largura) / float(8 * LADOPECA), menor(Altura, Largura) / float(8 * LADOPECA));

	}

	SpriteTabuleiro.setScale(menor(Altura, Largura) / float(LADOTABULEIRO), menor(Altura, Largura) / float(LADOTABULEIRO));

	return;
}

void c_interfaceJogo::atualizar_posicao() {//atualiza o mapa de s_idpeca
	std::map<short int, s_idpeca> _Estado;

	if(JogoMostrado != nullptr) {
		_Estado = JogoMostrado -> get_estado();

	}

	SpritesBrancas.clear();
	SpritesPretas.clear();

	posicionar_movimentos();

	posicionar_pecas(_Estado);

	posicionar_indicador_xeque();

	ajustar_sprites();

	return;
}

void c_interfaceJogo::localizar_clique(const unsigned _x, const unsigned _y) {
	PosicaoSelecionada = c_posicao();
	atualizar_posicao();
	
	if(!XequeMate) {
		if(JogoMostrado -> get_turno() == BRANCO) {
			for(auto &i: SpritesBrancas) {
				if(i.Sprite.getGlobalBounds().contains(_x, _y)) {
						PosicaoSelecionada = i.Posicao;
						i.Sprite.setColor(sf::Color(0x60, 0x60, 0xFF, 0xFF));
						break;

				}
			}
		}
		else {
			for(auto &i: SpritesPretas) {
				if(i.Sprite.getGlobalBounds().contains(_x, _y)) {
						PosicaoSelecionada = i.Posicao;
						i.Sprite.setColor(sf::Color(0x60, 0x60, 0xFF, 0xFF));
						break;
				}
			}
		}

		MovimentoEscolhido = nullptr;
		for(auto i: SpritesMovimentos) {
			if(i.Sprite.getGlobalBounds().contains(_x, _y)) {
				MovimentoEscolhido = i.Movimento;
				break;

			}
		}

		if(PosicaoSelecionada.validar() && (JogoMostrado != nullptr)) {
			MovimentosDisponiveis = JogoMostrado -> get_movimentos(!PosicaoSelecionada);

		}
		else {
			MovimentosDisponiveis.clear();

		}
	}

	return;
}

void c_interfaceJogo::posicionar_movimentos() { // Ainda não desenha
	SpritesMovimentos.clear();
	
	for(auto i: MovimentosDisponiveis) { // Vai correr na lista de movimentos
		int _PosX, _PosY;
		if(Lado == PRETO) {
			_PosX = i -> get_fim().get_x() - 1;
			_PosY = i -> get_fim().get_y() -  1;

			_PosX = 7 - _PosX; // Por causa do movimento invertido

			_PosX *= menor(Altura, Largura) / 8; // Divide o tamnho t atela por 8
			_PosY *= menor(Altura, Largura) / 8;

			_PosX -= PosXTabuleiro;
			_PosY -= PosYTabuleiro;

		}
		else { // BRANCO
			_PosX = i -> get_fim().get_x() - 1;
			_PosY = i -> get_fim().get_y() -  1;

			_PosY = 7 - _PosY; // Por causa das coordenada

			_PosX *= menor(Altura, Largura) / 8;
			_PosY *= menor(Altura, Largura) / 8;

			_PosX += PosXTabuleiro;
			_PosY += PosYTabuleiro;

		}
		s_imgmov _Temp;
		_Temp.Sprite.setPosition(_PosX, _PosY);
		_Temp.Sprite.setTexture(Texturas[CASAMOVIMENTO]);
		_Temp.Movimento = i;
		SpritesMovimentos.push_back(_Temp);
		if(dynamic_cast<c_roque*>(i)) {
			SpritesMovimentos.back().Sprite.setColor(sf::Color(0x00, 0xFF, 0x00, 0xFF));

		}
		else if(dynamic_cast<c_promocao*>(i)) {
			SpritesMovimentos.back().Sprite.setColor(sf::Color(0x00, 0xFF, 0x00, 0xFF));

		}
		else if(dynamic_cast<c_captura*>(i)) {
			SpritesMovimentos.back().Sprite.setColor(sf::Color(0xFF, 0x00, 0x00, 0xFF));

		}
		else {
			SpritesMovimentos.back().Sprite.setColor(sf::Color(0x00, 0x00, 0xFF, 0xFF));

		}

	}//fim do for

	return;
}

void c_interfaceJogo::posicionar_pecas(const std::map<short int, s_idpeca> _Estado) {
	for(auto &i: _Estado) {
		int _PosX, _PosY;
		if(Lado == PRETO) {
			_PosX = (i.first - 10) / 10;
			_PosY = (i.first -  1) % 10;

			_PosX = 7 - _PosX;

			_PosX *= menor(Altura, Largura) / 8;
			_PosY *= menor(Altura, Largura) / 8;

			_PosX -= PosXTabuleiro;
			_PosY -= PosYTabuleiro;

		}
		else {
			_PosX = (i.first - 10) / 10;
			_PosY = (i.first -  1) % 10;

			_PosY = 7 - _PosY;

			_PosX *= menor(Altura, Largura) / 8;
			_PosY *= menor(Altura, Largura) / 8;

			_PosX += PosXTabuleiro;
			_PosY += PosYTabuleiro;

		}

		s_imgpeca _Temp;

		if(i.second.Cor == BRANCO) {//procura qual peca e pra desenhar
			switch(i.second.Peca) {
				case PEAO:
					_Temp.Sprite.setTexture(Texturas[PEAOBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					SpritesBrancas.push_back(_Temp);
					break;

				case CAVALO:
					_Temp.Sprite.setTexture(Texturas[CAVALOBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					SpritesBrancas.push_back(_Temp);
					break;

				case BISPO:
					_Temp.Sprite.setTexture(Texturas[BISPOBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					SpritesBrancas.push_back(_Temp);
					break;

				case TORRE:
					_Temp.Sprite.setTexture(Texturas[TORREBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					SpritesBrancas.push_back(_Temp);
					break;

				case RAINHA:
					_Temp.Sprite.setTexture(Texturas[RAINHABRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					SpritesBrancas.push_back(_Temp);
					break;

				case REI:
					_Temp.Sprite.setTexture(Texturas[REIBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					SpritesBrancas.push_back(_Temp);
					break;
					
				default:
					break;

			}
			SpritesBrancas.back().Sprite.setColor(sf::Color(0xE0, 0xE0, 0xE0, 0xFF));
			if((!PosicaoSelecionada) == i.first) {
				SpritesBrancas.back().Sprite.setColor(sf::Color(0x60, 0x60, 0xFF, 0xFF));

			}
		}
		else if(i.second.Cor == PRETO) {
			switch(i.second.Peca) {
				case PEAO:
					_Temp.Sprite.setTexture(Texturas[PEAOPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					SpritesPretas.push_back(_Temp);
					break;

				case CAVALO:
					_Temp.Sprite.setTexture(Texturas[CAVALOPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					SpritesPretas.push_back(_Temp);
					break;

				case BISPO:
					_Temp.Sprite.setTexture(Texturas[BISPOPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					SpritesPretas.push_back(_Temp);
					break;

				case TORRE:
					_Temp.Sprite.setTexture(Texturas[TORREPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					SpritesPretas.push_back(_Temp);
					break;

				case RAINHA:
					_Temp.Sprite.setTexture(Texturas[RAINHAPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					SpritesPretas.push_back(_Temp);
					break;

				case REI:
					_Temp.Sprite.setTexture(Texturas[REIPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					SpritesPretas.push_back(_Temp);
					break;
					
				default:
					break;

			}
			if((!PosicaoSelecionada) == i.first) {
				SpritesPretas.back().Sprite.setColor(sf::Color(0x60, 0x60, 0xFF, 0xFF));

			}
		}
	}

	return;
}

void c_interfaceJogo::executar_movimentos() {
	if(JogoMostrado != nullptr) {
		if(MovimentoEscolhido != nullptr) {
			if(dynamic_cast<c_roque*>(MovimentoEscolhido)) {
				*JogoMostrado += *dynamic_cast<c_roque*>(MovimentoEscolhido);

			}
			else if(dynamic_cast<c_promocao*>(MovimentoEscolhido)) {
				*JogoMostrado += *dynamic_cast<c_promocao*>(MovimentoEscolhido);

			}
			else if(dynamic_cast<c_captura*>(MovimentoEscolhido)) {
				*JogoMostrado += *dynamic_cast<c_captura*>(MovimentoEscolhido);

			}
			else {
				*JogoMostrado += *MovimentoEscolhido;

			}
			
			PosicaoSelecionada = c_posicao();
			
			XequeMate = JogoMostrado -> get_mate();

			if(JogoMostrado -> get_promocao()) {
				PosicaoPromocao = MovimentoEscolhido -> get_fim();
				JanelaPromocao = new std::thread(c_interfaceJogo::escolher_promocao, this);

			}
			for(auto &i: MovimentosDisponiveis) {
				delete i;

			}
			MovimentosDisponiveis.clear();
			delete MovimentoEscolhido;
			MovimentoEscolhido = nullptr;
			SpritesMovimentos.clear();
		}
	}

	return;
}

void c_interfaceJogo::escolher_promocao() {
	if(JogoMostrado -> get_turno() == BRANCO) {
		CorPromocao.store(PRETO);
		
	}
	else {
		CorPromocao.store(BRANCO);
		
	}
	TipoPromocao.store(VAZIO);
	
	c_interfacePromocao tela(&TipoPromocao, &CorPromocao);

	tela.mostrar_janela();

	MovimentoEscolhido = new c_promocao(PosicaoPromocao, TipoPromocao.load());

	JanelaPromocao = nullptr;

	return;
}

void c_interfaceJogo::posicionar_indicador_xeque() {
	SpritesXeque.clear();

	if(JogoMostrado != nullptr) {
		if(JogoMostrado -> get_xeque()) {
			int _PosX, _PosY;
			if(Lado == PRETO) {
				_PosX = JogoMostrado -> get_posicao_ameaca().get_x() - 1;
				_PosY = JogoMostrado -> get_posicao_ameaca().get_y() - 1;

				_PosX = 7 - _PosX; // Por causa do movimento invertido

				_PosX *= menor(Altura, Largura) / 8; // Divide o tamnho da tela por 8
				_PosY *= menor(Altura, Largura) / 8;

				_PosX -= PosXTabuleiro;
				_PosY -= PosYTabuleiro;

			}
			else { // BRANCO
				_PosX = JogoMostrado -> get_posicao_ameaca().get_x() - 1;
				_PosY = JogoMostrado -> get_posicao_ameaca().get_y() -  1;

				_PosY = 7 - _PosY; // Por causa das coordenada

				_PosX *= menor(Altura, Largura) / 8;
				_PosY *= menor(Altura, Largura) / 8;

				_PosX += PosXTabuleiro;
				_PosY += PosYTabuleiro;

			}

			SpritesXeque.push_back(sf::Sprite(Texturas[CASAMOVIMENTO]));
			SpritesXeque.back().setPosition(_PosX, _PosY);
			SpritesXeque.back().setColor(sf::Color(0xFF, 0xF2, 0x00, 0xFF));


			if(Lado == PRETO) {
				_PosX = JogoMostrado -> get_posicao_ameacado().get_x() - 1;
				_PosY = JogoMostrado -> get_posicao_ameacado().get_y() - 1;

				_PosX = 7 - _PosX; // Por causa do movimento invertido

				_PosX *= menor(Altura, Largura) / 8; // Divide o tamnho da tela por 8
				_PosY *= menor(Altura, Largura) / 8;

				_PosX -= PosXTabuleiro;
				_PosY -= PosYTabuleiro;

			}
			else { // BRANCO
				_PosX = JogoMostrado -> get_posicao_ameacado().get_x() - 1;
				_PosY = JogoMostrado -> get_posicao_ameacado().get_y() -  1;

				_PosY = 7 - _PosY; // Por causa das coordenada

				_PosX *= menor(Altura, Largura) / 8;
				_PosY *= menor(Altura, Largura) / 8;

				_PosX += PosXTabuleiro;
				_PosY += PosYTabuleiro;

			}

			SpritesXeque.push_back(sf::Sprite(Texturas[CASAMOVIMENTO]));
			SpritesXeque.back().setPosition(_PosX, _PosY);
			SpritesXeque.back().setColor(sf::Color(0xFF, 0xF2, 0x00, 0xFF));

		}

	}

	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Construtores e destrutores da classe c_interfacePromocao
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

c_interfacePromocao::c_interfacePromocao(std::atomic<e_peca> *_Selecionado, std::atomic<e_cor> *_Cor) {
	Selecionado = _Selecionado;
	Cor = _Cor;

	Janela = new sf::RenderWindow(sf::VideoMode(540, 135), "Promocao", sf::Style::Close | sf::Style::Titlebar);
	Janela -> setVerticalSyncEnabled(true);

	carregar_texturas();

	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Metodos publicos da classe c_interfacePromocao
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void c_interfacePromocao::mostrar_janela() {
	while(Janela -> isOpen()) {
		sf::Event _Event;
        while (Janela -> pollEvent(_Event)) {
            switch(_Event.type) {
				case sf::Event::Closed:
					Janela -> close();
					break;

				case sf::Event::MouseButtonPressed:
					localizar_clique(_Event.mouseButton.x, _Event.mouseButton.y);
					break;

				case sf::Event::Resized:
					Janela -> setView(sf::View(sf::Vector2f(_Event.size.width / 2, _Event.size.height / 2), sf::Vector2f(_Event.size.width, _Event.size.height)));

					ajustar_sprites();
					posicionar_pecas();
					break;

				default:
					break;

			}
        }

		posicionar_pecas();

		Janela -> clear();

		for(auto i: Sprites) {
			Janela -> draw(i.Sprite);

		}

		Janela -> display();

	}

	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Metodos privados da classe c_interfacePromocao
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void c_interfacePromocao::carregar_texturas() {
	for(auto i: IMAGENS) {
		sf::Texture _Textura;
		if(!_Textura.loadFromFile(i)) {
			std::clog << "log: Erro ao carregar arquivo " << i << std::endl;
			continue;

		}
		Texturas.push_back(_Textura);

	}

	return;
}

void c_interfacePromocao::posicionar_pecas() {
	Sprites.clear();

	if(Cor -> load() == BRANCO) {
		s_sprites _Temp;
		_Temp.Sprite.setTexture(Texturas[RAINHABRANCO]);
		_Temp.Sprite.setPosition(0, 0);
		_Temp.IDSprite = RAINHA;
		Sprites.push_back(_Temp);
		_Temp.Sprite.setTexture(Texturas[BISPOBRANCO]);
		_Temp.Sprite.setPosition(135, 0);
		_Temp.IDSprite = BISPO;
		Sprites.push_back(_Temp);
		_Temp.Sprite.setTexture(Texturas[TORREBRANCO]);
		_Temp.Sprite.setPosition(270, 0);
		_Temp.IDSprite = TORRE;
		Sprites.push_back(_Temp);
		_Temp.Sprite.setTexture(Texturas[CAVALOBRANCO]);
		_Temp.Sprite.setPosition(405, 0);
		_Temp.IDSprite = CAVALO;
		Sprites.push_back(_Temp);

	}
	else {
		s_sprites _Temp;
		_Temp.Sprite.setTexture(Texturas[RAINHAPRETO]);
		_Temp.Sprite.setPosition(0, 0);
		_Temp.IDSprite = RAINHA;
		Sprites.push_back(_Temp);
		_Temp.Sprite.setTexture(Texturas[BISPOPRETO]);
		_Temp.Sprite.setPosition(135, 0);
		_Temp.IDSprite = BISPO;
		Sprites.push_back(_Temp);
		_Temp.Sprite.setTexture(Texturas[TORREPRETO]);
		_Temp.Sprite.setPosition(270, 0);
		_Temp.IDSprite = TORRE;
		Sprites.push_back(_Temp);
		_Temp.Sprite.setTexture(Texturas[CAVALOPRETO]);
		_Temp.Sprite.setPosition(405, 0);
		_Temp.IDSprite = CAVALO;
		Sprites.push_back(_Temp);

	}

	ajustar_sprites();

	return;
}

void c_interfacePromocao::ajustar_sprites() {
	float _Lado = menor(Janela -> getView().getSize().x, Janela -> getView().getSize().y);

	for(auto &i: Sprites) {
		i.Sprite.setScale(_Lado / LADOPECA, _Lado / LADOPECA);

	}

	return;
}

void c_interfacePromocao::localizar_clique(const unsigned _x, const unsigned _y) {
	for(auto &i: Sprites) {
		if(i.Sprite.getGlobalBounds().contains(_x, _y)) {
			Selecionado -> store((e_peca)i.IDSprite);
			Janela -> close();

			break;

		}
	}

	return;
}
