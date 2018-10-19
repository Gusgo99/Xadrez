#include <iostream>
#include <list>

#include "pecas.hpp"
#include "tabuleiro.hpp"

c_posicao::c_posicao(short int _x, short int _y) {
	x = _x;
	y = _y;

	return;
}


c_posicao::c_posicao(e_dir _Direcao, short int _Distancia) {
	x = 0;
	y = 0;

	if((_Direcao & N) != 0) {
		y = _Distancia;

	}
	else if((_Direcao & S) != 0) {
		y = -_Distancia;

	}

	if((_Direcao & E) != 0) {
		x = _Distancia;

	}
	else if((_Direcao & O) != 0) {
		x = -_Distancia;

	}

	return;
}

void c_posicao::set_x(short int _x) {
	x = _x;

	return;
}
void c_posicao::set_y(short int _y) {
	y = _y;

	return;
}

short int c_posicao::get_x() {
	return x;
}

short int c_posicao::get_y() {
	return y;
}

bool c_posicao::validar() {
	return ((x > 0) && (x <= 8) && (y > 0) && (y <= 8));
}

c_posicao c_posicao::operator+(c_posicao &_temp) {
	return c_posicao(_temp.get_x() + x, _temp.get_y() + y);
}

void c_posicao::operator+=(c_posicao &_temp) {
	x += _temp.get_x();
	y += _temp.get_y();

}

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

bool c_posicao::operator==(c_posicao &_temp) {
	return ((x == _temp.get_x()) && (y == _temp.get_y()));
}

bool c_posicao::operator!=(c_posicao &_temp) {
	return ((x != _temp.get_x()) || (y != _temp.get_y()));
}

short int c_posicao::operator!() {
	if(validar()) {
		return (10 * x) + y;

	}
	else {
		return 0;

	}
}

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


c_peca::c_peca(e_cor _Cor, c_posicao _Posicao) {
	Cor = _Cor;
	Posicao = _Posicao;

	return;
}

c_peca::~c_peca() {


	return;
}

e_cor c_peca::get_cor() {
	return Cor;
}

void c_peca::marcar_posicao(std::map<short int, e_peca> *_Estado) {
	if(_Estado != nullptr) {
		(*_Estado)[!Posicao] = IDPeca;
		
	}
	
	return;
}

void c_peca::atualizar_posicao(c_posicao _Posicao) {
	if(_Posicao.validar()) {
		Posicao = _Posicao;

	}

	return;
}

std::list<c_movimento> c_peca::listar_movimentos(std::map<short int, e_peca> _Estado) {
	std::list<c_movimento> _Movimentos = encontrar_movimentos(_Estado);
	std::list<c_movimento> _Capturas = encontrar_capturas(_Estado);
	std::list<c_movimento> _Especiais = encontrar_especiais(_Estado);
	
	_Movimentos.splice(_Movimentos.end(), _Capturas);
	_Movimentos.splice(_Movimentos.end(), _Especiais);
	
	return _Movimentos;
}

std::list<c_movimento> c_peca::encontrar_movimentos(std::map<short int, e_peca> _Estado) {
	std::list<c_movimento> _Movimentos;
	
	for(auto i: Direcoes) {
		for(auto j = 1; j != DistMov[i]; j++) {
			c_posicao _NovaPosicao(i, j);
			_NovaPosicao += Posicao;
			if(!_NovaPosicao.validar()) break;
			if(_Estado[!_NovaPosicao] != VAZIO) break;
			
			_Movimentos.push_back(Posicao >> _NovaPosicao);
			
		}
	}
		
	return _Movimentos;
}

std::list<c_movimento> c_peca::encontrar_capturas(std::map<short int, e_peca> _Estado) {
	std::list<c_movimento> _Movimentos;
	
	for(auto i: Direcoes) {
		for(auto j = 1; j != DistCome[i]; j++) {
			c_posicao _NovaPosicao(i, j);
			_NovaPosicao += Posicao;
			if(!_NovaPosicao.validar()) break;
			
			if(_Estado[!_NovaPosicao] != VAZIO) {
				if((_Estado[!_NovaPosicao] >> 4) != Cor) {
					_Movimentos.push_back(Posicao >> _NovaPosicao);
					
				}
			}
		}
	}
	
	return _Movimentos;
}


bool c_peca::ameacando_rei(std::map<short int, e_peca> _Estado) {
	std::list<c_movimento> _Capturas = encontrar_capturas(_Estado);
	c_posicao _PosRei;
	
	// Calcular posicao do rei
	
	for(auto i: _Capturas) {
		if(i.get_fim() == _PosRei) {
			return true;
			
		}
		
	}
	
	return false;
}

c_posicao c_peca::get_posicao() {
	return Posicao;
}
