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

enum e_dir {N = 0x01, S = 0x02, E = 0x04, O = 0x08, NE = 0x05, SE = 0x06, NO = 0x09, SO = 0x0A};
enum e_pontuacao {PEAO = 1, CAVALO = 3, BISPO = 3, TORRE = 5, RAINHA = 9, REI = 1000};
enum e_cor {SEMCOR, BRANCO, PRETO};

// Classe responsavel por guardar a posicao de cada peca
class c_posicao {
	private:
		short int x;
		short int y;

	public:
		c_posicao(short int _x = 0, short int _y = 0);
		c_posicao(e_dir _Direcao, short int _Distancia);
		c_posicao operator+(c_posicao &_temp);
		void operator+=(c_posicao &_temp);
		short int operator-(c_posicao &_temp);
		bool operator==(c_posicao &_temp);
		bool operator!=(c_posicao &_temp);
		short int operator!();
		c_movimento operator>>(c_posicao &_temp);
		c_movimento operator<<(c_posicao &_temp);
		void set_x(short int _x);
		void set_y(short int _y);
		short int get_x();
		short int get_y();
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


//#####################################################
            //classe peca
//#####################################################

class c_peca {
	protected:
		std::array<unsigned short int, 8> DistMov;//cada indice representa uma direcao, e o valor a quantidade de movimento
		std::array<unsigned short int, 8> DistCome;
		e_pontuacao Pontuacao;
		c_posicao Posicao;
		e_cor Cor;

	public:
		c_peca(e_cor _Cor = SEMCOR, c_posicao _Posicao = c_posicao(0, 0));
		~c_peca();
		std::list<c_movimento> encontrar_movimentos();
		std::list<c_movimento> encontrar_capturas();
		virtual std::list<c_movimento> encontrar_especiais() = 0;
		bool ameacando_rei();
		e_cor get_cor();
		c_posicao get_posicao();
		void atualizar_posicao(c_posicao _Posicao);


};

//#####################################################
            //sub classe peca
//#####################################################

class c_bispo : public c_peca {
	private:

	public:
		c_bispo(e_cor _Cor, c_posicao _Posicao);
		std::list<c_movimento> encontrar_especiais(){return std::list<c_movimento>();};


};

class c_rainha : public c_peca {
	private:

	public:
		c_rainha(e_cor _Cor, c_posicao _Posicao);
		std::list<c_movimento> encontrar_especiais(){return std::list<c_movimento>();};


};

class c_rei : public c_peca {
	private:
		unsigned NumJogadas;
		void jogar(std::array<unsigned short int, 2> _Posicao);

	public:
	    c_rei(e_cor _Cor, c_posicao _Posicao);
		std::list<c_movimento> encontrar_especiais();

};

class c_peao : public c_peca {
	private:
		unsigned NumJogadas;

	public:
	    c_peao(e_cor _Cor, c_posicao _Posicao);
		void jogar(std::array<unsigned short int, 2> Posicao);
		void promocao();
		std::list<c_movimento> encontrar_especiais();


};

class c_torre : public c_peca {
	private:
		unsigned NumJogadas;

	public:
	    c_torre(e_cor _Cor, c_posicao _Posicao);
		unsigned short int get_num_jogadas();
		std::list<c_movimento> encontrar_especiais();

};

class c_cavalo : public c_peca {
	private:


	public:
	    c_cavalo(e_cor _Cor, c_posicao _Posicao);
		std::list<c_movimento> encontrar_especiais();

};

#endif
