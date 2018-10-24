#include <iostream>
#include <list>

#include "pecas.hpp"
#include "tabuleiro.hpp"

// Constantes com posicoes relativas do movimento do cavalo
const std::array<c_posicao, 8> MOVIMENTOSCAVALO = {
c_posicao(2, 1),
c_posicao(2, -1),
c_posicao(1, 2),
c_posicao(1, -2),
c_posicao(-2, 1),
c_posicao(-2, -1),
c_posicao(-1, 2),
c_posicao(-1, -2)};

c_posicao::c_posicao(short int _ID) {
	x = _ID / 10;
	y = _ID % 10;
	
}

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

void c_posicao::set_xy(short int _x, short int _y){
    x = _x;
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

	return;
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
	return c_movimento(c_posicao(x, y), _temp, SIMPLES);
}

c_movimento c_posicao::operator<<(c_posicao &_temp) {
	return c_movimento(_temp, c_posicao(x, y), SIMPLES);
}

c_movimento::c_movimento(c_posicao _PosInicial, c_posicao _PosFinal) {
	if(_PosInicial.validar() && _PosFinal.validar()) {
		PosInicial = _PosInicial;
		PosFinal = _PosFinal;
		TipoMovimento = SIMPLES;

	}
	else {
		//Verificar o que fazer em caso de movimento invalido

	}

	return;
}

c_movimento::c_movimento(c_posicao _PosInicial, c_posicao _PosFinal, e_movimento _TipoMovimento) {
	if(_PosInicial.validar() && _PosFinal.validar()) {
		PosInicial = _PosInicial;
		PosFinal = _PosFinal;
		TipoMovimento = _TipoMovimento;

	}
	else {
		//Verificar o que fazer em caso de movimento invalido

	}

	return;
}

c_roque::c_roque(e_cor _Cor, bool _Tipo) {
    Cor = _Cor;
	Tipo = _Tipo;
	
    return;
}

e_cor c_roque::get_cor() {
	return Cor;
}

bool c_roque::get_tipo() {
	return Tipo;
}

void c_roque::set_cor(e_cor _Cor) {
	Cor = _Cor;
	
	return;
}

void c_roque::set_tipo(bool _Tipo) {
	Tipo = _Tipo;
	
	return;
}

c_posicao c_movimento::get_inicio() {
	return PosInicial;
}

c_posicao c_movimento::get_fim() {
	return PosFinal;
}

void c_movimento::set_tipo(e_movimento _TipoMovimento) {
	TipoMovimento = _TipoMovimento;

	return;
}

e_movimento c_movimento::get_tipo() {
	return TipoMovimento;
}

c_peca::c_peca(e_cor _Cor, c_posicao _Posicao) {
	IDPeca.Cor = _Cor;
	IDPeca.NumJogadas = 0;
	Posicao = _Posicao;
	
	for(auto &i: DistCome) {
		i.second = 0;
		
	}
	DistMov = DistCome;

	for(auto &i: DistCome) {
		i.second = 0;

	}

	for(auto &i: DistMov) {
		i.second = 0;

	}

	return;
}

c_peca::~c_peca() {
	return;
}

e_cor c_peca::get_cor() {
	return IDPeca.Cor;
}

e_peca c_peca::get_peca(){
    return IDPeca.Peca;
}

void c_peca::marcar_posicao(std::map<short int, s_idpeca> *_Estado) {
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

std::list<c_movimento*> c_peca::listar_movimentos(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento*> _Movimentos = encontrar_movimentos(_Estado);
	std::list<c_movimento*> _Capturas = encontrar_capturas(_Estado);
	std::list<c_movimento*> _Especiais = encontrar_especiais(_Estado);
	
	_Movimentos.splice(_Movimentos.end(), _Capturas);
	_Movimentos.splice(_Movimentos.end(), _Especiais);

	return _Movimentos;
}

std::list<c_movimento*> c_peca::encontrar_movimentos(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento*> _Movimentos;

	for(auto i: Direcoes) {
		for(auto j = 1; j <= DistMov[i]; j++) {
			c_posicao _NovaPosicao(i, j);
			_NovaPosicao += Posicao;
			if(!_NovaPosicao.validar()) break;
			if(_Estado[!_NovaPosicao].Peca != VAZIO) break;
			
			_Movimentos.push_back(new c_movimento(Posicao, _NovaPosicao, SIMPLES));

		}
	}

	return _Movimentos;
}

std::list<c_movimento*> c_peca::encontrar_capturas(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento*> _Movimentos;

	for(auto i: Direcoes) {
		for(auto j = 1; j <= DistCome[i]; j++) {
			c_posicao _NovaPosicao(i, j);
			_NovaPosicao += Posicao;
			if(!_NovaPosicao.validar()) break;

			if(_Estado[!_NovaPosicao].Peca != VAZIO) {
				if(_Estado[!_NovaPosicao].Cor == IDPeca.Cor) break;
				
				_Movimentos.push_back(new c_movimento(Posicao, _NovaPosicao, CAPTURA));
				break;

			}
		}
	}

	return _Movimentos;
}

//#####################################################
            // Sub classes das pecas
//#####################################################

// Construtor bispo
c_bispo::c_bispo(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {
    DistMov[NE] = 8;
    DistMov[SE] = 8;
    DistMov[SO] = 8;
    DistMov[NO] = 8;

    DistCome = DistMov;
    IDPeca.Peca = BISPO;//BISPO eh um enum

    return;
}

// Construtor rainha
c_rainha::c_rainha(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {
    DistMov[N]  = 8;
    DistMov[NE] = 8;
    DistMov[E]  = 8;
    DistMov[SE] = 8;
    DistMov[S]  = 8;
    DistMov[SO] = 8;
    DistMov[O]  = 8;
    DistMov[NO] = 8;

    DistCome = DistMov;
    IDPeca.Peca = RAINHA;//eh um enum

    return;
}

// Construtor rei
c_rei::c_rei(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {
    DistMov[N]  = 1;
    DistMov[NE] = 1;
    DistMov[E]  = 1;
    DistMov[SE] = 1;
    DistMov[S]  = 1;
    DistMov[SO] = 1;
    DistMov[O]  = 1;
    DistMov[NO] = 1;

    DistCome = DistMov;
    IDPeca.Peca = REI;//eh um enum
    Ameacado = false;

    return;
}

// Verifica se alguma peca ameaca o rei
bool c_peca::ameacando_rei(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento*> _Capturas = encontrar_capturas(_Estado);

	for(auto i: _Capturas) {
		if(_Estado[!(i -> get_fim())].Peca == REI) {
			return true;

		}
	}

	return false;
}

c_posicao c_peca::get_posicao() {
	return Posicao;
}

std::list<c_movimento*> c_rei::encontrar_especiais(std::map<short int, s_idpeca> _Estado) {
//encontra o roque do rei

    c_movimento *_aux;
    std::list<c_movimento*> _Movimento;

    /*if(IDPeca.NumJogadas != 0)//o rei moveu?
        return _Movimento;

    if(IDPeca.Cor == BRANCO){//REI BRANCO

        if(_Estado[!c_posicao(1, 1)].Cor == BRANCO && _Estado[!c_posicao(1, 1)].Peca == TORRE){//roque grande?
            if((_Estado[!c_posicao(2, 1)].Peca == VAZIO) && (_Estado[!c_posicao(3, 1)].Peca == VAZIO) && (_Estado[!c_posicao(4, 1)].Peca == VAZIO)) {//tem peca no caminho?
                _aux = new c_roque(BRANCO, ROQUEMAIOR);
                (*_aux).set_tipo(ESPECIAL);
                _Movimento.push_back(*_aux);}
        }

        if((_Estado[!c_posicao(8, 1)].Cor == BRANCO) && (_Estado[!c_posicao(8, 1)].Peca == TORRE)) {//roque pequeno?
            if(_Estado[!c_posicao(6, 1)].Peca == VAZIO && _Estado[!c_posicao(7, 1)].Peca == VAZIO){//tem peca no caminho?
                _aux = new c_roque(BRANCO, ROQUEMENOR);
                (*_aux).set_tipo(ESPECIAL);
                _Movimento.push_back(*_aux);}
        }


    }else{//REI PRETO

        if((_Estado[!c_posicao(1, 8)].Cor == PRETO) && (_Estado[!c_posicao(1, 8)].Peca == TORRE)) {//roque grande?
            if((_Estado[!c_posicao(2, 8)].Peca == VAZIO) && (_Estado[!c_posicao(3, 8)].Peca == VAZIO) && (_Estado[!c_posicao(4, 8)].Peca == VAZIO)) {//tem peca no caminho?
                _aux = new c_roque(PRETO, ROQUEMAIOR);
                (*_aux).set_tipo(ESPECIAL);
                _Movimento.push_back(*_aux);}

        }

        if((_Estado[!c_posicao(8, 8)].Cor == PRETO) && (_Estado[!c_posicao(8, 8)].Peca == TORRE)) {//roque pequeno?
            if((_Estado[!c_posicao(6, 8)].Peca == VAZIO) && (_Estado[!c_posicao(7, 8)].Peca == VAZIO)) {//tem peca no caminho?
                _aux = new c_roque(PRETO, ROQUEMENOR);
                (*_aux).set_tipo(ESPECIAL);
                _Movimento.push_back(*_aux);}
        }

    }*/

    return _Movimento;
}

// Construtor da torre
c_torre::c_torre(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {
    DistMov[N]  = 8;
    DistMov[E]  = 8;
    DistMov[S]  = 8;
    DistMov[O]  = 8;

    DistCome = DistMov;
    IDPeca.Peca = TORRE;//eh um enum
    IDPeca.NumJogadas = 0;

    return;
}

// Construtor do peao
c_peao::c_peao(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {

    IDPeca.Peca = PEAO;								//eh um enum

    if(_Cor == BRANCO) {
        DistMov[N] = 2;
        DistCome[NE] = 1;
        DistCome[NO] = 1;
    }
	else {
        DistMov[S] = 2;
        DistCome[SE] = 1;
        DistCome[SO] = 1;
    }

    return;
}

std::list<c_movimento*> c_peao::encontrar_especiais(std::map<short int, s_idpeca> _Estado) {
    return std::list<c_movimento*>();
}

// Construtor cavalo:
c_cavalo::c_cavalo(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {
    IDPeca.Peca = CAVALO;//eh um enum

    return;
}

std::list<c_movimento*> c_cavalo::encontrar_movimentos(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento*> _Movimentos;
	
	for(auto i: MOVIMENTOSCAVALO) {
		c_posicao _NovaPosicao = Posicao + i;
		if(!_NovaPosicao.validar()) continue;
		if(_Estado[!_NovaPosicao].Peca == VAZIO) {
			_Movimentos.push_back(new c_movimento(Posicao, _NovaPosicao, SIMPLES));
			
		}
	}


    return _Movimentos;
}

std::list<c_movimento*> c_cavalo::encontrar_capturas(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento*> _Movimentos;
	
	for(auto i: MOVIMENTOSCAVALO) {
		c_posicao _NovaPosicao = Posicao + i;
		if(!_NovaPosicao.validar()) continue;
		if(_Estado[!_NovaPosicao].Peca != VAZIO) {
			if(_Estado[!_NovaPosicao].Cor != IDPeca.Cor) {
			_Movimentos.push_back(new c_movimento(Posicao, _NovaPosicao, CAPTURA));
				
			}			
		}
	}

    return _Movimentos;
}

std::list<c_movimento*> c_cavalo::listar_movimentos(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento*> _Movimentos = encontrar_movimentos(_Estado);
	std::list<c_movimento*> _Capturas = encontrar_capturas(_Estado);
	std::list<c_movimento*> _Especiais = encontrar_especiais(_Estado);

	_Movimentos.splice(_Movimentos.end(), _Capturas);
	_Movimentos.splice(_Movimentos.end(), _Especiais);

	return _Movimentos;
}
