#ifndef GUI_HPP
#define GUI_HPP

#include <SFML\Graphics.hpp>

#include "tabuleiro.hpp"

#define LADOBRANCAS false
#define LADOPRETAS true

class c_interfaceJogo {
	private:
		c_jogo *JogoMostrado;
		bool Lado;
		sf::RenderWindow *janela;
		std::list<sf::Sprite> Sprites;
		int Altura;
		int Largura;
		void carregar_sprites();
		std::list<sf::Sprite>::iterator selec = Sprites.begin();
		
	public:
		c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, bool _Lado, int _Altura, int _Largura);
		//void carregar_tabuleiro();
		void desenhar_janela();
	
};

#endif