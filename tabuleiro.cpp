#include <iostream>

#include "tabuleiro.hpp"
#include "utilidades.hpp"
#include "pecas.hpp"

c_posicao::c_posicao(short int _x, short int _y) {
	if((_x > 0) && (_x <= 8) && (_y > 0) && (_y <= 8)) {
		x = _x;
		y = _y;
		valido = true;
		
	}
	else {
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

bool c_posicao::validar() {
	return valido;
}

// Retorna a distancia entre duas posicoes(Ignora se nao houver alinhamento diagonal, vertical ou horizontal entre as posicoes)
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
	
	return 15;
}

bool c_posicao::operator==(c_posicao &_temp) {
	return ((x == _temp.get_x()) && (y == _temp.get_y()));
}

c_movimento c_posicao::operator>>(c_posicao &_temp) {
	return c_movimento(c_posicao(x, y), _temp);
}

c_movimento c_posicao::operator<<(c_posicao &_temp) {
	return c_movimento(_temp, c_posicao(x, y));
}

c_movimento::c_movimento(c_posicao _inicial, c_posicao _final) {
	if(_inicial.validar() && _final.validar()) {
		inicial = _inicial;
		final = _final;
		
	}
	else {
		//Verificar o que fazer em caso de movimento invalido
		
	}
	
	return;
}

// Implementar como o movimento deve ser realizado
void c_movimento::executar_movimento(c_jogo *_estado) {
	if(_estado != nullptr) {
		
		
	}
	
	return;
}

c_posicao c_movimento::get_inicial() {
	return inicial;
}

c_posicao c_movimento::get_final() {
	return final;
}

void testar_posicao() {
	c_posicao a(2, 3);
	c_posicao b(3, 2);
	
	short int dist = b - a;
	
	std::cout << "Distancia de (2, 3) ate (3, 2): " << dist << std::endl;
	
	c_movimento mov = a >> b;
	
	std::cout << "Inicial: (" << mov.get_inicial().get_x() << ", " << mov.get_inicial().get_y() << ")" << std::endl;
	
	std::cout << "Final: (" << mov.get_final().get_x() << ", " << mov.get_final().get_y() << ")" << std::endl;
	
}

void testar_movimento() {
	
	return;
}