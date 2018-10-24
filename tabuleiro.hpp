#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

class c_jogo;
class c_movimento;

#include <array>
#include <map>

#include "pecas.hpp"

class c_jogo {
	private:
		std::map<short int, c_peca*> Tabuleiro;
		unsigned Turno;
		unsigned JogadasRestantes;
		bool Xeque;

	public:
		c_jogo();
		c_jogo(c_jogo *_original);
		salvar_jogo();
		carregar_jogo();
		void operator+=(c_movimento &_Movimento);
		void operator+=(c_roque &_Roque);
		std::map<short int, s_idpeca> get_estado();
		bool get_xeque();
		std::list<c_movimento> get_movimentos(c_posicao _Posicao);
		
};

#endif
