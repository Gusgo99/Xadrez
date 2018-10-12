#ifndef PECAS_HPP
#define PECAS_HPP

class c_movimento;
class c_posicao;

class c_peca;
class c_bispo;
class c_peao;
class c_cavalo;
class c_rei;
class c_torre;

#include <array>
#include <list>

#include "tabuleiro.hpp"

enum e_dir {NO, N, NE, E, SE, S, SO, O};
enum e_pontuacao {PEAO = 1, CAVALO = 3, BISPO = 3, TORRE = 5, RAINHA = 9, REI = 1000};
enum e_cor {SEMCOR, BRANCO, PRETO};

// Classe responsavel por guardar a posicao de cada peca
class c_posicao {
	private:
		short int x;
		short int y;
		bool valido;
		
	public:
		c_posicao(short int _x = 0, short int _y = 0);
		short int get_x();
		short int get_y();
		short int operator-(c_posicao &_temp);
		bool operator==(c_posicao &_temp);
		short int operator!();
		c_movimento operator>>(c_posicao &_temp);
		c_movimento operator<<(c_posicao &_temp);
		bool validar();
		
};

class c_jogo;

// Classe responsavel por guardar posicao inicial e final de um movimento e executar o movimento
class c_movimento {
	private:
		c_posicao PosInicial;
		c_posicao PosFinal;
		
	public:
		c_movimento(c_posicao _PosInicial = c_posicao(0, 0), c_posicao _PosFinal = c_posicao(0, 0));
		c_posicao get_inicio();
		c_posicao get_fim();
		
};

// Classe base para todas as pecas
class c_peca {
	private:
		std::array<unsigned short int, 8> DistMov;
		std::array<unsigned short int, 8> DistCome;
		e_pontuacao Pontuacao;
		c_posicao Posicao;
		e_cor Cor;
	
	public:
		c_peca(e_cor _cor);
		~c_peca();
		std::list<c_movimento> encontrar_movimentos();
		std::list<c_movimento> encontrar_capturas();
		virtual std::list<c_movimento> encontrar_especiais() = 0;
		bool ameacando_rei();
		e_cor get_cor();
		c_posicao get_posicao();
		void atualizar_posicao(c_posicao _Posicao);
		
	
};

class c_bispo : public c_peca {
	private:
	
	public:
		std::list<c_movimento> encontrar_especiais();
	
	
};

class c_rei : public c_peca {
	private:
		unsigned NumJogadas;
		void jogar(std::array<unsigned short int, 2> _Posicao);
	
	public:
		std::list<c_movimento> encontrar_especiais();
		
};

class c_peao : public c_peca {
	private:
		unsigned NumJogadas;
		
	public:
		void jogar(std::array<unsigned short int, 2> Posicao);
		void promocao();
		std::list<c_movimento> encontrar_especiais();
		
	
};

class c_torre : public c_peca {
	private:
		unsigned NumJogadas;
	
	public:
		unsigned short int get_num_jogadas();
		std::list<c_movimento> encontrar_especiais();
	
};

class c_cavalo : public c_peca {
	private:
		
		
	public:
		std::list<c_movimento> encontrar_especiais();
		
		
	
};

#endif
