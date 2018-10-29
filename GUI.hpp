#ifndef GUI_HPP
#define GUI_HPP

#include <atomic>
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

#warning Verificar o que e usado em todas as interfaces e usar heranca
class c_interface {
	protected:
		sf::RenderWindow *Janela;
		std::vector<sf::Texture> Texturas;
		std::list<sf::Sprite> Sprites;
		bool Desenhar;
		void carregar_texturas(std::vector<std::string> _Imagens);
		void ajustar_sprites();
		virtual void posicionar_sprites() = 0;
		
	public:
		c_interface(std::string _Titulo = "", unsigned _Altura = 0, unsigned _Largura = 0, bool Vsync = false);
		virtual void event_handler(sf::Event _Event) = 0;
		void desenhar_janela();
	
};

class c_interfaceJogo {
	private:
		// Ponteiro para o jogo que deverá ser mostrado
		c_jogo *JogoMostrado;
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
		// Carrega cada sprite a partir das imagens
		void carregar_texturas();
		// Ajusta tamanho da tela para não distorcer imagens após redimensionar janela
		void ajustar_sprites();
		// Desenha pecas na tela baseado no estado retornado por _JogoMostrado
		void atualizar_posicao();
		void localizar_clique(unsigned _x, unsigned _y);
		void posicionar_movimentos();
		void posicionar_pecas(std::map<short int, s_idpeca> _Estado);
		void executar_movimentos();
		void escolher_promocao();
		std::atomic<e_cor> CorPromocao;
		std::atomic<e_peca> TipoPromocao;
		c_posicao PosicaoPromocao;
		void posicionar_indicador_xeque();
		
	public:
		c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, e_cor Lado);								// Construtor com tamanho de tela relativo
		c_interfaceJogo(std::string _Titulo, c_jogo *_JogoMostrado, e_cor Lado, int _Altura, int _Largura);		// Construtor com tamanho de tela absoluto
		~c_interfaceJogo();
		void desenhar_janela();
	
};

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
		void mostrar_janela();
	
};

#endif
