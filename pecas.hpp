#ifndef PECAS_HPP
#define PECAS_HPP

#include <array>
#include <list>

class c_movimento;
class c_captura;
class c_roque;
class c_promocao;
class c_roque;
class c_posicao;

class c_peca;
class c_bispo;
class c_peao;
class c_cavalo;
class c_rei;
class c_torre;

enum e_dir {
	N = 0x01,
	S = 0x02,
	E = 0x04,
	O = 0x08,
	NE = N | E,
	SE = S | E,
	NO = N | O,
	SO = S | O};

enum e_cor {SEMCOR, BRANCO, PRETO};
enum e_peca {VAZIO, PEAO, CAVALO, BISPO, TORRE, RAINHA, REI};

// Armazena cor e tipo da peca
struct s_idpeca {
	s_idpeca() {Cor = SEMCOR; Peca = VAZIO; NumJogadas = 0;}
	e_cor Cor;
	e_peca Peca;
    unsigned NumJogadas;

};

#include "tabuleiro.hpp"

// Maneira simples de iterar por todas as direcoes
const std::array<e_dir, 8> Direcoes = {N, S, E, O, NE, SE, NO, SO};

// Classe responsavel por guardar a posicao de cada peca
class c_posicao {
	private:
		short int x;
		short int y;

	public:
		c_posicao(short int _ID = 0);
		c_posicao(short int _x, short int _y);
		c_posicao(e_dir _Direcao, short int _Distancia);
		c_posicao operator+(c_posicao &_temp);
		void operator+=(c_posicao &_temp);
		short int operator-(c_posicao &_temp);										// Retorna a distancia entre duas posicoes(Retorna 0 se nao houver alinhamento vertical, horizontal ou diagonal entre as posicoes)
		bool operator==(c_posicao &_temp);											// Verifica se duas posicoes sao iguais
		bool operator!=(c_posicao &_temp);											// Verifica se duas posicoes nao sao iguais
		short int operator!();														// Retorna uma chave para mapear o tabuleiro
		c_movimento operator>>(c_posicao &_temp);									// Compoem um movimento com os dois argumentos
		c_movimento operator<<(c_posicao &_temp);									// Compoem um movimento com os dois argumentos
		void set_x(short int _x);
		void set_y(short int _y);
		void set_xy(short int _x, short int _y);
		short int get_x();
		short int get_y();
		bool validar();																// Verifica se a posicao e valida (Dentro da grade 8x8)

};

class c_jogo;

// #####################################################
            // Classe movimento
// #####################################################
// Classe responsavel por guardar posicao inicial e final de um movimento e executar o movimento
class c_movimento {
	protected:
		c_posicao PosInicial;
		c_posicao PosFinal;

	public:
		c_movimento(c_posicao _PosInicial = c_posicao(0, 0), c_posicao _PosFinal = c_posicao(0, 0));
		virtual ~c_movimento() {}
		c_posicao get_inicio();
		c_posicao get_fim();
		void set_inicio(c_posicao _PosInicial);
		void set_fim(c_posicao _PosFinal);

};

class c_captura : public c_movimento {
	private:
	public:
		c_captura(c_posicao _PosInicial = c_posicao(0, 0), c_posicao _PosFinal = c_posicao(0, 0)) : c_movimento(_PosInicial, _PosFinal) {};

};

class c_roque : public c_movimento {
	protected:
		c_posicao PosInicialTorre;
		c_posicao PosFinalTorre;

	public:
		c_roque(c_posicao _PosInicial, c_posicao _PosFinal, c_posicao _PosInicialTorre, c_posicao _PosFinalTorre);
		void set_inicio_torre(c_posicao _PosInicial);
		void set_fim_torre(c_posicao _PosFinal);
		c_posicao get_inicio_torre();
		c_posicao get_fim_torre();

};

class c_promocao : public c_movimento {
	protected:
		e_peca NovaPeca;

	public:
	c_promocao(c_posicao _PosInicial, e_peca _NovaPeca);
		void set_nova_peca(e_peca _NovaPeca);
		e_peca get_nova_peca();

};

// #####################################################
            // Classe peca
// #####################################################

class c_peca {
	protected:
		// Distancia maxima que a peca pode se mover em cada direcao
		std::map<e_dir, short int> DistMov;
		// Distancia maxima que a peca pode comer em cada direcao
		std::map<e_dir, short int> DistCome;
		// Identificacao da peca (Tipo e cor)
		s_idpeca IDPeca;
		// Posicao da peca no tabuleiro
		c_posicao Posicao;
		// Calcula possiveis movimentos
		virtual std::list<c_movimento*> encontrar_movimentos(std::map<short int, s_idpeca> _Estado);
		// Calcula possiveis capturas
		virtual std::list<c_movimento*> encontrar_capturas(std::map<short int, s_idpeca> _Estado);
		// Calcula movimentos especiais
		virtual std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado) = 0;
		
	public:
		c_peca(e_cor _Cor = SEMCOR, c_posicao _Posicao = c_posicao(0, 0));
		~c_peca();
		// Lista movimentos possiveis
		virtual std::list<c_movimento*> listar_movimentos(std::map<short int, s_idpeca> _Estado);
		// Verifica se a peca esta ameacando o rei inimigo
		bool ameacando_rei(std::map<short int, s_idpeca> _Estado);
		// Verifica se a peca esta ameacando o rei inimigo
		bool ameacando_posicao(std::map<short int, s_idpeca> _Estado, c_posicao _posicao);
		// Realiza a atualizacao da posicao apos realizar o movimento
		virtual bool atualizar_posicao(c_posicao _Posicao);
		// Faz com que cada peca marque sua posicao no tabuleiro
		void marcar_posicao(std::map<short int, s_idpeca> *_Estado);
		s_idpeca get_ID();
		e_cor get_cor();
		e_peca get_peca();
		c_posicao get_posicao();
		unsigned get_num_jogadas();
        std::map<short int , bool> encontrar_ameacas(std::map<short int, s_idpeca> _Estado);
};

// #####################################################
            // Sub classes peca
// #####################################################

class c_bispo : public c_peca {
	private:
		std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado) {return std::list<c_movimento*>();};

	public:
		c_bispo(e_cor _Cor, c_posicao _Posicao);


};

class c_rainha : public c_peca {
	private:
		std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado) {return std::list<c_movimento*>();};

	public:
		c_rainha(e_cor _Cor, c_posicao _Posicao);

};

class c_rei : public c_peca {
	private:
        bool Ameacado;
	    std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado);

	public:
	    c_rei(e_cor _Cor, c_posicao _Posicao);
        bool get_ameacado(){return Ameacado;};
};

class c_peao : public c_peca {
	private:
		// Calcula movimentos especiais
		std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado) {return std::list<c_movimento*>();}

	public:
	    c_peao(e_cor _Cor, c_posicao _Posicao);
		bool atualizar_posicao(c_posicao _Posicao);

};

class c_torre : public c_peca {
	private:
		std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado) {return std::list<c_movimento*>();};

	public:
	    c_torre(e_cor _Cor, c_posicao _Posicao);

};

class c_cavalo : public c_peca {
	private:
		std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado) {return std::list<c_movimento*>();};
		std::list<c_movimento*> encontrar_movimentos(std::map<short int, s_idpeca> _Estado);
	    std::list<c_movimento*> encontrar_capturas(std::map<short int, s_idpeca> _Estado);

	public:
		std::list<c_movimento*> listar_movimentos(std::map<short int, s_idpeca> _Estado);
	    c_cavalo(e_cor _Cor, c_posicao _Posicao);

};

#endif
