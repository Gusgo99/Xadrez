#include <iostream>
#include <list>

#include "pecas.hpp"
#include "tabuleiro.hpp"

c_posicao::c_posicao(short int _x, short int _y) {
	if((_x > 0) && (_x <= 8) && (_y > 0) && (_y <= 8)) {
		x = _x;
		y = _y;
		valido = true;
		
	}
	else {
		x = 0;
		y = 0;
		valido = false;
		
	}
	
	return;
}

short int c_posicao::get_x() {
	return x;
}

short int c_posicao::get_y() {
	return y;
}

// Verifica se a posicao e valida (Dentro da grade 8x8)
bool c_posicao::validar() {
	return valido;
}

// Retorna a distancia entre duas posicoes(Retorna 0 se nao houver alinhamento vertical, horizontal ou diagonal entre as posicoes)
short int c_posicao::operator-(c_posicao &_temp) {
	if(_temp.get_x() == x) {
		return abs(_temp.get_y() - y);
		
	}
	else if(_temp.get_y() == y) {
		return abs(_temp.get_x() - x);
		
	}
	else if(abs(_temp.get_x() - x) == abs(_temp.get_y() - y)) {
		return abs(_temp.get_x() - x);
		
	}
	
	return 0;
}

// Verifica se duas posicoes sao iguais
bool c_posicao::operator==(c_posicao &_temp) {
	return ((x == _temp.get_x()) && (y == _temp.get_y()));
}

// Retorna uma chave para mapear o tabuleiro
short int c_posicao::operator!() {
	if(valido) {
		return (10 * x) + y;
		
	}
	else {
		return 0;
		
	}
}

// Compoem um movimento com os dois argumentos
c_movimento c_posicao::operator>>(c_posicao &_temp) {
	return c_movimento(c_posicao(x, y), _temp);
}

c_movimento c_posicao::operator<<(c_posicao &_temp) {
	return c_movimento(_temp, c_posicao(x, y));
}

c_movimento::c_movimento(c_posicao _PosInicial, c_posicao _PosFinal) {
	if(_PosInicial.validar() && _PosFinal.validar()) {
		PosInicial = _PosInicial;
		PosFinal = _PosFinal;
		
	}
	else {
		//Verificar o que fazer em caso de movimento invalido
		
	}
	
	return;
}

c_posicao c_movimento::get_inicio() {
	return PosInicial;
}

c_posicao c_movimento::get_fim() {
	return PosFinal;
}

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

void c_peca::atualizar_posicao(c_posicao _Posicao) {
	if(_Posicao.validar()) {
		Posicao = _Posicao;
		
	}
	
	return;
}
