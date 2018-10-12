#include <iostream>
#include <list>

#include "pecas.hpp"
#include "tabuleiro.hpp"

c_peca::c_peca(e_cor _Cor) {
	Cor = _Cor;
	
	return;
}

c_peca::~c_peca() {
	
	
	return;
}

std::list<c_movimento> c_peca::encontrar_movimentos() {
	
	
}

e_cor c_peca::get_cor() {
	return Cor;
}