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
		
	public:
		c_jogo();
		c_jogo(c_jogo *_original);
		salvar_jogo();
		carregar_jogo();
		void operator+(c_movimento &_movimento);
		std::map<short int, s_idpeca> get_estado();
		
};

#endif
