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

c_interfaceJogo::c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, bool _Lado, int _Altura, int _Largura) {
	JogoMostrado = _JogoMostrado;
	Lado = _Lado;
	Largura = _Largura;
	Altura = _Altura;
	
	janela = new sf::RenderWindow(sf::VideoMode(Largura, Altura), _Titulo);
	
	carregar_sprites();
	
	Sprites.front().setScale(menor(Altura, Largura) / float(LADOTABULEIRO), menor(Altura, Largura) / float(LADOTABULEIRO));
	
	PosXTabuleiro = 0;
	PosYTabuleiro = 0;
	
	return;
}

void c_interfaceJogo::carregar_sprites() {
	sf::Texture *_Textura = nullptr;
	sf::Sprite _NovaSprite;
	
	for(auto i: IMAGENS) {
		_Textura = new sf::Texture;
		
		if(!_Textura -> loadFromFile(i)) {
			std::cout << "Erro ao carregar arquivo " << i << std::endl;
			continue;
			
		}
		_Textura -> setSmooth(true);
		_NovaSprite.setTexture(*_Textura);
		Sprites.push_back(_NovaSprite);
		
		ajustar_pecas();
		
	}
	
	return;
}

void c_interfaceJogo::ajustar_pecas() {
	for(auto &i: Sprites) {
		i.setScale(menor(Altura, Largura) / float(8 * LADOPECA), menor(Altura, Largura) / float(8 * LADOPECA));
		
	}
	
	Sprites.front().setScale(menor(Altura, Largura) / float(LADOTABULEIRO), menor(Altura, Largura) / float(LADOTABULEIRO));
	
	return;
}

void c_interfaceJogo::desenhar_pecas() {
	std::map<short int, s_idpeca> _Estado;

	if(JogoMostrado != nullptr) {
		_Estado = JogoMostrado -> get_estado();
		
	}
	else {																// Somente mostra o estado inicial do tabuleiro se o jogo nao for passado
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
		
		_Estado[17] = temp;
		_Estado[27] = temp;
		_Estado[37] = temp;
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
	
	janela -> draw(Sprites[TABULEIRO]);
	
	for(auto &i: _Estado) {
		int _PosX, _PosY;
		if(Lado) {
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
			
			_PosX -= PosXTabuleiro;
			_PosY -= PosYTabuleiro;
		
		}
		
		if(i.second.Cor == BRANCO) {
			switch(i.second.Peca) {
				case PEAO:
					Sprites[PEAOBRANCO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[PEAOBRANCO]);
					break;
					
				case CAVALO:
					Sprites[CAVALOBRANCO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[CAVALOBRANCO]);
					break;
					
				case BISPO:
					Sprites[BISPOBRANCO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[BISPOBRANCO]);
					break;
					
				case TORRE:
					Sprites[TORREBRANCO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[TORREBRANCO]);
					break;
					
				case RAINHA:
					Sprites[RAINHABRANCO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[RAINHABRANCO]);
					break;
					
				case REI:
					Sprites[REIBRANCO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[REIBRANCO]);
					break;
				
			}
		}
		else if(i.second.Cor == PRETO) {
			switch(i.second.Peca) {
				case PEAO:
					Sprites[PEAOPRETO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[PEAOPRETO]);
					break;
					
				case CAVALO:
					Sprites[CAVALOPRETO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[CAVALOPRETO]);
					break;
					
				case BISPO:
					Sprites[BISPOPRETO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[BISPOPRETO]);
					break;
					
				case TORRE:
					Sprites[TORREPRETO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[TORREPRETO]);
					break;
					
				case RAINHA:
					Sprites[RAINHAPRETO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[RAINHAPRETO]);
					break;
					
				case REI:
					Sprites[REIPRETO].setPosition(_PosX, _PosY);
					janela -> draw(Sprites[REIPRETO]);
					break;
				
			}
		}
	}
	
	return;
}

void c_interfaceJogo::desenhar_janela() {
	while(janela -> isOpen()) {
		
		sf::Event _Event;
        while (janela -> pollEvent(_Event)) {
            switch(_Event.type) {
				case sf::Event::Closed:
					janela -> close();
					break;
					
				case sf::Event::MouseButtonPressed:
					std::cout << "Do something!!\n";
					break;
					
				case sf::Event::Resized:
					Largura = _Event.size.width;
					Altura = _Event.size.height;
					
					janela -> setView(sf::View(sf::Vector2f(Largura / 2, Altura / 2), sf::Vector2f(Largura, Altura)));
					
					ajustar_pecas();
					break;
					
				
			}
			
        }
		
		janela -> clear();
		
		desenhar_pecas();
		
		janela -> display();
		
	}
	
}