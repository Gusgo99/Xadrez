#ifndef GUI_HPP
#define GUI_HPP

#include <atomic>
#include <thread>
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

struct s_sprites {
	sf::Sprite Sprite;
	unsigned IDSprite;
	
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_interfaceJogo:
 *
 * Responsavel por:
 *
 * - Interface grafica do jogo;
 * - Verificar objetos selecionados;
 * - Executar movimentos selecionados;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_interfaceJogo {
	private:
		// Ponteiro para o jogo que deverá ser mostrado
		c_tabuleiro *JogoMostrado;
		// Thread que roda a janela de promocao
		std::thread *JanelaPromocao;
		// Define lado que o tabuleiro será visto
		e_cor Lado;
		// Ponteiro para a instancia da janela
		sf::RenderWindow *Janela;
		// Texturas de cada peca
		std::vector<sf::Texture> Texturas;
		sf::Sprite SpriteTabuleiro;
		std::list<s_imgpeca> SpritesBrancas;
		std::list<s_imgpeca> SpritesPretas;
		std::list<s_imgmov> SpritesMovimentos;
		std::list<sf::Sprite> SpritesXeque;
		sf::Sprite ImagemMate;
		c_posicao PosicaoSelecionada;
		std::list<c_movimento*> MovimentosDisponiveis;
		c_movimento *MovimentoEscolhido;
		// Largura da janela
		int Altura;
		// Altura da janela
		int Largura;
		// Posição em X do tabuleiro dentro da janela
		int PosXTabuleiro;
		// Posição em Y do tabuleiro dentro da janela
		int PosYTabuleiro;
		std::atomic<e_cor> CorPromocao;
		std::atomic<e_peca> TipoPromocao;
		c_posicao PosicaoPromocao;
		bool XequeMate;
		// Carrega cada sprite a partir das imagens
		void carregar_texturas();
		// Ajusta tamanho da tela para não distorcer imagens após redimensionar janela
		void ajustar_sprites();
		// Desenha pecas na tela baseado no estado retornado por _JogoMostrado
		void atualizar_posicao();
		void localizar_clique(const unsigned _x, const unsigned _y);
		void posicionar_movimentos();
		void posicionar_pecas(const std::map<short int, s_idpeca> _Estado);
		void executar_movimentos();
		void escolher_promocao();
		void posicionar_indicador_xeque();
		
	public:
		// Construtor com tamanho de tela relativo
		c_interfaceJogo(const std::string _Titulo = "", c_tabuleiro *_JogoMostrado = nullptr, const e_cor Lado = BRANCO);
		// Construtor com tamanho de tela absoluto
		c_interfaceJogo(const std::string _Titulo, c_tabuleiro *_JogoMostrado, const e_cor Lado, const int _Altura, const int _Largura);
		~c_interfaceJogo();
		void desenhar_janela();
	
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_interfaceJogo:
 *
 * Responsavel por:
 *
 * - Interface grafica de escolha de peca da promocao
 * - Verificar objetos selecionados;
 * - Informar para c_interfaceJogo qual a peca selecionada
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_interfacePromocao {
	private:
		sf::RenderWindow *Janela;
		std::atomic<e_peca> *Selecionado;
		std::atomic<e_cor> *Cor;
		std::vector<sf::Texture> Texturas;
		std::list<s_sprites> Sprites;
		void carregar_texturas();
		void posicionar_pecas();
		void ajustar_sprites();
		void localizar_clique(unsigned _x, unsigned _y);
		
	public:
		c_interfacePromocao(std::atomic<e_peca> *_Selecionado, std::atomic<e_cor> *_Cor);
		~c_interfacePromocao() {}
		void mostrar_janela();
	
};

#endif
