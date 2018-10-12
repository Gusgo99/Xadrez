#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

class c_jogo;
class c_posicao;
class c_movimento;

#include <array>

#include "pecas.hpp"

class c_jogo {
	private:
		unsigned Turno;
		unsigned JogadasRestantes;
		
	public:
		std::array<std::array<c_peca*, 8>, 8> Tabuleiro;
		c_jogo();
		c_jogo(c_jogo *_original);
		salvar_jogo();
		carregar_jogo();
		
		
};

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
		c_movimento operator>>(c_posicao &_temp);
		c_movimento operator<<(c_posicao &_temp);
		bool validar();
		
};

class c_movimento {
	private:
		c_posicao inicial;
		c_posicao final;
		short int TipoMovimento;
		
	public:
		c_movimento(c_posicao _inicial = c_posicao(0, 0), c_posicao _final = c_posicao(0, 0));
		void executar_movimento(c_jogo *_estado);
		c_posicao get_inicial();
		c_posicao get_final();
		
};

// Funcoes de teste das classes
void testar_posicao();
void testar_movimento();

#endif