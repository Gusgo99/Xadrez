#include <map>
#include <vector>

#include <SFML\Graphics.hpp>

#include <iostream>

#include "GUI.hpp"
#include "pecas.hpp"
#include "tabuleiro.hpp"
#include "utilidades.hpp"

#define LADOTABULEIRO 1080
#define LADOPECA 135

// Indice onde estao os sprites no vector Sprites
enum e_numSprite {	TABULEIRO,
					CASAVERMELHA,
					CASAVERDE,
					CASAAZUL,
					REIPRETO, REIBRANCO,
					PEAOPRETO, PEAOBRANCO,
					RAINHAPRETO, RAINHABRANCO,
					BISPOPRETO, BISPOBRANCO,
					TORREPRETO, TORREBRANCO,
					CAVALOPRETO, CAVALOBRANCO,
					NUMSPRITES};

// Caminho ate imagens do jogo
const std::array<std::string, NUMSPRITES> IMAGENS = {	"./resources/tabuleiro.png",
														"./resources/tab_quad_red.png",
														"./resources/tab_quad_ver.png",
														"./resources/tab_quad_azu.png",
														"./resources/rei_preto.png", "./resources/rei_branco.png",
														"./resources/peao_preto.png", "./resources/peao_branco.png",
														"./resources/rainha_preto.png", "./resources/rainha_branco.png",
														"./resources/bispo_preto.png", "./resources/bispo_branco.png",
														"./resources/torre_preto.png", "./resources/torre_branco.png",
														"./resources/cavalo_preto.png", "./resources/cavalo_branco.png"};

c_interfaceJogo::c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, e_cor _Lado, int _Altura, int _Largura) {
	JogoMostrado = _JogoMostrado;
	Lado = _Lado;
	
	Largura = _Largura;
	Altura = _Altura;
	
	janela = new sf::RenderWindow(sf::VideoMode(Largura, Altura), _Titulo);
	
	carregar_texturas();
	
	s_imagempeca _Temp;
	
	_Temp.Sprite = sf::Sprite(Texturas[TABULEIRO]);
	_Temp.Posicao = c_posicao();
	
	Sprites.push_back(_Temp);
	
	ajustar_sprites();
	
	PosXTabuleiro = 0;
	PosYTabuleiro = 0;
	
	return;
}

c_interfaceJogo::c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, e_cor _Lado) {
	JogoMostrado = _JogoMostrado;
	Lado = _Lado;
	
	Largura = menor(sf::VideoMode::getDesktopMode().height, sf::VideoMode::getDesktopMode().width) * 0.75;
	Altura = Largura;
	
	janela = new sf::RenderWindow(sf::VideoMode(Largura, Altura), _Titulo);
	
	carregar_texturas();
	
	s_imagempeca _Temp;
	
	_Temp.Sprite = sf::Sprite(Texturas[TABULEIRO]);
	_Temp.Posicao = c_posicao();
	
	Sprites.push_back(_Temp);
	
	ajustar_sprites();
	
	PosXTabuleiro = 0;
	PosYTabuleiro = 0;
	
	return;
}

void c_interfaceJogo::carregar_texturas() {
	for(auto i: IMAGENS) {
		sf::Texture _Textura;
		if(!_Textura.loadFromFile(i)) {
			std::cout << "Erro ao carregar arquivo " << i << std::endl;
			continue;
			
		}
		Texturas.push_back(_Textura);
		
	}
	
	return;
}

void c_interfaceJogo::ajustar_sprites() {
	for(auto &i: Sprites) {
		i.Sprite.setScale(menor(Altura, Largura) / float(8 * LADOPECA), menor(Altura, Largura) / float(8 * LADOPECA));
		
	}
	
	Sprites.front().Sprite.setScale(menor(Altura, Largura) / float(LADOTABULEIRO), menor(Altura, Largura) / float(LADOTABULEIRO));
	
	return;
}

void c_interfaceJogo::posicionar_movimentos() {
	for(auto i: MovimentosDisponiveis) {
		int _PosX, _PosY;
		if(Lado == PRETO) {
			_PosX = i.get_fim().get_x() - 1;
			_PosY = i.get_fim().get_y() -  1;
			
			_PosX = 7 - _PosX;
			
			_PosX *= menor(Altura, Largura) / 8;
			_PosY *= menor(Altura, Largura) / 8;
			
			_PosX -= PosXTabuleiro;
			_PosY -= PosYTabuleiro;
			
		}
		else {
			_PosX = i.get_fim().get_x() - 1;
			_PosY = i.get_fim().get_y() -  1;
			
			_PosY = 7 - _PosY;
			
			_PosX *= menor(Altura, Largura) / 8;
			_PosY *= menor(Altura, Largura) / 8;
			
			_PosX += PosXTabuleiro;
			_PosY += PosYTabuleiro;
		
		}
		s_imagempeca _Temp;
		_Temp.Sprite.setPosition(_PosX, _PosY);
		switch(i.get_tipo()) {
			case SIMPLES:
				_Temp.Sprite.setTexture(Texturas[CASAAZUL]);
				_Temp.Sprite.setColor(sf::Color(0xFF, 0xFF, 0xFF, 0xFF));
				_Temp.Cor = SEMCOR;
				_Temp.Posicao = i.get_fim();
				Sprites.push_back(_Temp);
				break;
				
			case CAPTURA:
				_Temp.Sprite.setTexture(Texturas[CASAVERMELHA]);
				_Temp.Cor = SEMCOR;
				_Temp.Posicao = i.get_fim();
				Sprites.push_back(_Temp);
				break;
				
			case ESPECIAL:
				_Temp.Sprite.setTexture(Texturas[CASAVERDE]);
				_Temp.Cor = SEMCOR;
				_Temp.Posicao = i.get_fim();
				Sprites.push_back(_Temp);
				break;
			
		}
		
		
	}
	
	return;
}

void c_interfaceJogo::posicionar_pecas(std::map<short int, s_idpeca> _Estado) {
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
		
		s_imagempeca _Temp;
		
		if(i.second.Cor == BRANCO) {
			switch(i.second.Peca) {
				case PEAO:
					_Temp.Sprite.setTexture(Texturas[PEAOBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					Sprites.push_back(_Temp);
					break;
					
				case CAVALO:
					_Temp.Sprite.setTexture(Texturas[CAVALOBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					Sprites.push_back(_Temp);
					break;
					
				case BISPO:
					_Temp.Sprite.setTexture(Texturas[BISPOBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					Sprites.push_back(_Temp);
					break;
					
				case TORRE:
					_Temp.Sprite.setTexture(Texturas[TORREBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					Sprites.push_back(_Temp);
					break;
					
				case RAINHA:
					_Temp.Sprite.setTexture(Texturas[RAINHABRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					Sprites.push_back(_Temp);
					break;
					
				case REI:
					_Temp.Sprite.setTexture(Texturas[REIBRANCO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = BRANCO;
					Sprites.push_back(_Temp);
					break;
				
			}
		}
		else if(i.second.Cor == PRETO) {
			switch(i.second.Peca) {
				case PEAO:
					_Temp.Sprite.setTexture(Texturas[PEAOPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					Sprites.push_back(_Temp);
					break;
					
				case CAVALO:
					_Temp.Sprite.setTexture(Texturas[CAVALOPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					Sprites.push_back(_Temp);
					break;
					
				case BISPO:
					_Temp.Sprite.setTexture(Texturas[BISPOPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					Sprites.push_back(_Temp);
					break;
					
				case TORRE:
					_Temp.Sprite.setTexture(Texturas[TORREPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					Sprites.push_back(_Temp);
					break;
					
				case RAINHA:
					_Temp.Sprite.setTexture(Texturas[RAINHAPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					Sprites.push_back(_Temp);
					break;
					
				case REI:
					_Temp.Sprite.setTexture(Texturas[REIPRETO]);
					_Temp.Sprite.setPosition(_PosX, _PosY);
					_Temp.Posicao = c_posicao(i.first);
					_Temp.Cor = PRETO;
					Sprites.push_back(_Temp);
					break;
				
			}
		}
		if(!PosicaoSelecionada == i.first) {
			Sprites.back().Sprite.setColor(sf::Color(0x60, 0x60, 0xFF, 0xFF));
			
		}
	}
	
	return;
}

void c_interfaceJogo::atualizar_posicao() {
	std::map<short int, s_idpeca> _Estado;

	if(JogoMostrado != nullptr) {
		_Estado = JogoMostrado -> get_estado();
		
	}
	else {																// Mostra somente o estado inicial do tabuleiro se o jogo nao for passado
		s_idpeca temp;
		
		temp.Cor = BRANCO;
		temp.Peca = PEAO;
		
		_Estado[12] = temp;
		_Estado[22] = temp;
		_Estado[32] = temp;
		_Estado[42] = temp;
		_Estado[52] = temp;
		_Estado[62] = temp;
		_Estado[72] = temp;
		_Estado[82] = temp;
		
		temp.Peca = TORRE;
		
		_Estado[11] = temp;
		_Estado[81] = temp;
		
		temp.Peca = CAVALO;
		
		_Estado[21] = temp;
		_Estado[71] = temp;
		
		temp.Peca = BISPO;
		
		_Estado[31] = temp;
		_Estado[61] = temp;
		
		temp.Peca = RAINHA;
		
		_Estado[41] = temp;
		
		temp.Peca = REI;
		
		_Estado[51] = temp;
		
		temp.Cor = PRETO;
		temp.Peca = PEAO;
		
		_Estado[13] = temp;
		_Estado[27] = temp;
		_Estado[33] = temp;
		_Estado[47] = temp;
		_Estado[57] = temp;
		_Estado[67] = temp;
		_Estado[77] = temp;
		_Estado[87] = temp;
		
		temp.Peca = TORRE;
		
		_Estado[18] = temp;
		_Estado[88] = temp;
		
		temp.Peca = CAVALO;
		
		_Estado[28] = temp;
		_Estado[78] = temp;
		
		temp.Peca = BISPO;
		
		_Estado[38] = temp;
		_Estado[68] = temp;
		
		temp.Peca = RAINHA;
		
		_Estado[48] = temp;
		
		temp.Peca = REI;
		
		_Estado[58] = temp;
		
	}
	
	while(Sprites.size() > 1) {
		Sprites.pop_back();
		
	}
	
	janela -> draw(Sprites.front().Sprite);
	
	posicionar_movimentos();
	
	posicionar_pecas(_Estado);
	
	ajustar_sprites();
	
	return;
}

void c_interfaceJogo::localizar_clique(unsigned _x, unsigned _y) {
	PosicaoSelecionada = c_posicao();
	atualizar_posicao();
	for(auto i: Sprites) {
		if(&i != &Sprites.front()) {
			if(i.Sprite.getGlobalBounds().contains(_x, _y)) {
				if(i.Cor == Lado) {
					PosicaoSelecionada = i.Posicao;
					i.Sprite.setColor(sf::Color(0x60, 0x60, 0xFF, 0xFF));
				
				}
			}
		}
	}
	
	if(PosicaoSelecionada.validar() && (JogoMostrado != nullptr)) {
		//MovimentosDisponiveis = JogoMostrado -> get_movimentos(!PosicaoSelecionada);
		
	}
	
	MovimentosDisponiveis.clear();
	
	if(PosicaoSelecionada.validar()) {
		c_posicao a(2, 2);
		c_posicao b(2, 3);
		
		MovimentosDisponiveis.push_back(a >> b);
		
		b = c_posicao(2, 4);
		
		MovimentosDisponiveis.push_back(a >> b);
		
		b = c_posicao(3, 3);
		
		MovimentosDisponiveis.push_back(a >> b);
		MovimentosDisponiveis.back().set_tipo(CAPTURA);
		
		b = c_posicao(1, 3);
		
		MovimentosDisponiveis.push_back(a >> b);
		MovimentosDisponiveis.back().set_tipo(CAPTURA);
		
		b = c_posicao(2, 8);
		
		MovimentosDisponiveis.push_back(a >> b);
		MovimentosDisponiveis.back().set_tipo(ESPECIAL);
		
	}
	
	return;
}

void c_interfaceJogo::desenhar_janela() {
	atualizar_posicao();
	
	while(janela -> isOpen()) {
		sf::Event _Event;
        while (janela -> pollEvent(_Event)) {
            switch(_Event.type) {
				case sf::Event::Closed:
					janela -> close();
					break;
					
				case sf::Event::MouseButtonPressed:
					localizar_clique(_Event.mouseButton.x, _Event.mouseButton.y);
					break;
					
				case sf::Event::Resized:
					Largura = _Event.size.width;
					Altura = _Event.size.height;
					
					janela -> setView(sf::View(sf::Vector2f(Largura / 2, Altura / 2), sf::Vector2f(Largura, Altura)));
					
					ajustar_sprites();
					atualizar_posicao();
					break;
					
			}
        }
		
		janela -> clear();
		
		atualizar_posicao();
		
		for(auto i: Sprites) {
			janela -> draw(i.Sprite);
			
		}
		
		janela -> display();
		
	}
	
}
