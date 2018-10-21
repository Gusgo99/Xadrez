#include <array>
#include <SFML\Graphics.hpp>
#include <iostream>

#include "GUI.hpp"
#include "tabuleiro.hpp"
#include "utilidades.hpp"

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
	
	Sprites.front().scale(menor(Altura, Largura) / float(1082), menor(Altura, Largura) / float(1082));
	
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
		_NovaSprite.setTexture(*_Textura);
		Sprites.push_back(_NovaSprite);
		
		selec = Sprites.begin();
		
	}
	
	return;
}

/*void c_interfaceJogo::carregar_tabuleiro() {
	sf::Texture *TextTabuleiro = new sf::Texture;
	sf::Sprite Tabuleiro;
	
	TextTabuleiro -> setSmooth(true);
	
	if(!TextTabuleiro -> loadFromFile(TABULEIRO)) {
		std::cout << "Erro" << std::endl;
		
	}
	
	Tabuleiro.scale(menor(Altura, Largura) / float(1082), menor(Altura, Largura) / float(1082));
	
	Tabuleiro.setTexture(*TextTabuleiro);
	
	Desenhos.push_back(Tabuleiro);
	
	return;
}*/

void c_interfaceJogo::desenhar_janela() {
	while(janela -> isOpen()) {
		
		sf::Event event;
        while (janela -> pollEvent(event)) {
            switch(event.type) {
				case sf::Event::Closed:
					janela -> close();
					break;
					
				case sf::Event::MouseButtonPressed:
					if(event.mouseButton.x > Largura / 2) {
						selec++;
						if(selec == Sprites.end()) {
							selec = Sprites.begin();
							
						}
					}
					else {
						if(selec == Sprites.begin()) {
							selec = Sprites.end();
							
						}
						selec--;
					}
					break;
					
				
			}
			
        }
		
		janela -> clear();
		
		janela -> draw(*selec);
		
		/*for(auto i: Sprites) {
			janela -> draw(i);
			
		}*/
		
		janela -> display();
		
	}
	
}