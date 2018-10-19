#include <iostream>

#include "tabuleiro.hpp"
#include "utilidades.hpp"
#include "pecas.hpp"

c_jogo::c_jogo() {
	for(auto i = 1; i != 9; i++) {
		for(auto j = 1; j != 9; j++) {
			Tabuleiro[!c_posicao(i, j)] = nullptr;
			
		}
	}
	
}

/*std::map<short int, e_peca> c_tabuleiro::get_estado() {
	std::map<short int, e_peca> _Estado;
	
	for(auto i: Tabuleiro) {
		if(i != nullptr) {
			i.marcar_posicao(&_Estado);
			
		}
	}
	
	return _Estado;
}*/