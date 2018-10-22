#include <iostream>

#include "tabuleiro.hpp"
#include "utilidades.hpp"
#include "pecas.hpp"

c_jogo::c_jogo() {
	for(auto i = 1; i <= 8; i++) {
		for(auto j = 1; j <= 8; j++) {
			Tabuleiro[!c_posicao(i, j)] = nullptr;
			
		}
	}
	
	// Finalizar implementação dos contrutores e da função encontrar_especiais para retirar o comentario
	/*for(auto i = 1; i <= 8; i++) {
		Tabuleiro[!c_posicao(i, 2)] = new c_peao(BRANCO, c_posicao(i, 2));
		Tabuleiro[!c_posicao(i, 7)] = new c_peao(PRETO, c_posicao(i, 7));
		
	}
	
	Tabuleiro[!c_posicao(1, 1)] = new c_torre(BRANCO, c_posicao(1, 1));
	Tabuleiro[!c_posicao(8, 1)] = new c_torre(BRANCO, c_posicao(8, 1));
	Tabuleiro[!c_posicao(1, 8)] = new c_torre(PRETO, c_posicao(1, 8));
	Tabuleiro[!c_posicao(8, 8)] = new c_torre(PRETO, c_posicao(8, 8));
	
	Tabuleiro[!c_posicao(2, 1)] = new c_cavalo(BRANCO, c_posicao(2, 1));
	Tabuleiro[!c_posicao(7, 1)] = new c_cavalo(BRANCO, c_posicao(7, 1));
	Tabuleiro[!c_posicao(2, 8)] = new c_cavalo(PRETO, c_posicao(2, 8));
	Tabuleiro[!c_posicao(7, 8)] = new c_cavalo(PRETO, c_posicao(7, 8));
	
	Tabuleiro[!c_posicao(3, 1)] = new c_bispo(BRANCO, c_posicao(3, 1));
	Tabuleiro[!c_posicao(6, 1)] = new c_bispo(BRANCO, c_posicao(6, 1));
	Tabuleiro[!c_posicao(3, 8)] = new c_bispo(PRETO, c_posicao(3, 8));
	Tabuleiro[!c_posicao(6, 8)] = new c_bispo(PRETO, c_posicao(6, 8));
	
	Tabuleiro[!c_posicao(4, 1)] = new c_rainha(BRANCO, c_posicao(4, 1));
	Tabuleiro[!c_posicao(5, 1)] = new c_rei(BRANCO, c_posicao(5, 1));
	Tabuleiro[!c_posicao(4, 8)] = new c_rainha(PRETO, c_posicao(4, 8));
	Tabuleiro[!c_posicao(5, 8)] = new c_rei(PRETO, c_posicao(5, 8));*/
	
	return;
}

std::map<short int, s_idpeca> c_jogo::get_estado() {
	std::map<short int, s_idpeca> _Estado;
	
	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			i.second -> marcar_posicao(&_Estado);
			
		}
	}
	
	return _Estado;
}