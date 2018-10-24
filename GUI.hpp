#ifndef GUI_HPP
#define GUI_HPP

#include <SFML\Graphics.hpp>

#include "tabuleiro.hpp"

struct s_imgpeca {
	sf::Sprite Sprite;
	e_cor Cor;
	c_posicao Posicao;
	
};

struct s_imgmov {
	sf::Sprite Sprite;
	c_movimento *Movimento;
	
};

class c_interfaceJogo {
	private:
		c_jogo *JogoMostrado;																					// Ponteiro para o jogo que deverá ser mostrado
		e_cor Lado;																								// Define lado que o tabuleiro será visto
		sf::RenderWindow *janela;																				// Ponteiro para a instancia da janela
		std::vector<sf::Texture> Texturas;																		// Texturas de cada peca
		sf::Sprite SpriteTabuleiro;
		std::list<s_imgpeca> SpritesBrancas;
		std::list<s_imgpeca> SpritesPretas;
		std::list<s_imgmov> SpritesMovimentos;
		c_posicao PosicaoSelecionada;
		std::list<c_movimento> MovimentosDisponiveis;
		c_movimento *MovimentoEscolhido;
		int Altura;																								// Largura da janela
		int Largura;																							// Altura da janela
		int PosXTabuleiro;																						// Posição em X do tabuleiro dentro da janela
		int PosYTabuleiro;																						// Posição em Y do tabuleiro dentro da janela
		void carregar_texturas();																				// Carrega cada sprite a partir das imagens
		void ajustar_sprites();																					// Ajusta tamanho da tela para não distorcer imagens após redimensionar janela
		void atualizar_posicao();																				// Desenha pecas na tela baseado no estado retornado por _JogoMostrado
		void localizar_clique(unsigned _x, unsigned _y);
		void posicionar_movimentos();
		void posicionar_pecas(std::map<short int, s_idpeca> _Estado);
		void executar_movimentos();
		
	public:
		c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, e_cor Lado);								// Construtor com tamanho de tela relativo
		c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, e_cor Lado, int _Altura, int _Largura);		// Construtor com tamanho de tela absoluto
		~c_interfaceJogo();
		void desenhar_janela();
	
};

#endif
