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
		std::vector<sf::Sprite> Sprites;
		int Altura;
		int Largura;
		int PosXTabuleiro;
		int PosYTabuleiro;
		void carregar_sprites();
		void ajustar_pecas();
		void desenhar_pecas();
		
	public:
		c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, bool _Lado, int _Altura, int _Largura);
		void desenhar_janela();
	
};

#endif