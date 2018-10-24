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

bool c_jogo::get_xeque() {
    return Xeque;
}

/*std::map<short int, s_idpeca> get_estado() {
	std::map<short int, s_idpeca> _Estado;

	for(auto i: Tabuleiro) {
		if(i != nullptr) {
			i.marcar_posicao(&_Estado);

		}
	}

	return _Estado;
}*/
