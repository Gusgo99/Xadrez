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


c_roque::c_roque(c_posicao _PosInicial, c_posicao _PosFinal, c_posicao _PosInicial2, c_posicao _PosFinal2){
    TipoMovimento = ESPECIAL;
    PosInicial=_PosInicial;
    PosFinal=_PosFinal;
    PosInicial2=PosInicial2;
    PosFinal2=PosFinal2;
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
	Posicao = _Posicao;

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

std::list<c_movimento> c_peca::listar_movimentos(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento> _Movimentos = encontrar_movimentos(_Estado);
	std::list<c_movimento> _Capturas = encontrar_capturas(_Estado);
	std::list<c_movimento> _Especiais = encontrar_especiais(_Estado);

	_Movimentos.splice(_Movimentos.end(), _Capturas);
	_Movimentos.splice(_Movimentos.end(), _Especiais);

	return _Movimentos;
}

std::list<c_movimento> c_peca::encontrar_movimentos(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento> _Movimentos;

	for(auto i: Direcoes) {
		for(auto j = 1; j != DistMov[i]; j++) {
			c_posicao _NovaPosicao(i, j);
			_NovaPosicao += Posicao;
			if(!_NovaPosicao.validar()) break;
			if(_Estado[!_NovaPosicao].Peca != VAZIO) break;

			_Movimentos.push_back(Posicao >> _NovaPosicao);

		}
	}

	return _Movimentos;
}

std::list<c_movimento> c_peca::encontrar_capturas(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento> _Movimentos;

	for(auto i: Direcoes) {
		for(auto j = 1; j != DistCome[i]; j++) {
			c_posicao _NovaPosicao(i, j);
			_NovaPosicao += Posicao;
			if(!_NovaPosicao.validar()) break;

			if(_Estado[!_NovaPosicao].Peca != VAZIO) {
				if(_Estado[!_NovaPosicao].Cor == IDPeca.Cor) break;
				_Movimentos.push_back(Posicao >> _NovaPosicao);

			}
		}
	}

	return _Movimentos;
}



//#####################################################
            //sub classe peca
//#####################################################

//bispo
c_bispo::c_bispo(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {

    DistMov[N]  = 0;
    DistMov[NE] = 8;
    DistMov[E]  = 0;
    DistMov[SE] = 8;
    DistMov[S]  = 0;
    DistMov[SO] = 8;
    DistMov[O]  = 0;
    DistMov[NO] = 8;

    DistCome = DistMov;
    IDPeca.Peca = BISPO;//BISPO eh um enum
    Posicao = _Posicao;
    IDPeca.Cor = _Cor;

    return;
}



//reinha
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
    Posicao = _Posicao;
    IDPeca.Cor = _Cor;

    return;
}

//rei
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
    Posicao = _Posicao;
    IDPeca.Cor = _Cor;
    IDPeca.NumJogadas=0;
    Ameacado=false;

    return;
}


bool c_peca::ameacando_rei(std::map<short int, s_idpeca> _Estado) {
	std::list<c_movimento> _Capturas = encontrar_capturas(_Estado);

	for(auto i: _Capturas) {
		if((_Estado[!(i.get_fim())].Peca == REI) && (_Estado[!(i.get_fim())].Cor == IDPeca.Cor)) {
			return true;

		}
	}

	return false;
}

c_posicao c_peca::get_posicao() {
	return Posicao;
}

std::list<c_movimento> c_rei::encontrar_especiais() {

    //implementar

    return std::list<c_movimento>();
}
//torre

c_torre::c_torre(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {

    DistMov[N]  = 8;
    DistMov[NE] = 0;
    DistMov[E]  = 8;
    DistMov[SE] = 0;
    DistMov[S]  = 8;
    DistMov[SO] = 0;
    DistMov[O]  = 8;
    DistMov[NO] = 0;

    DistCome = DistMov;
    IDPeca.Peca = TORRE;//eh um enum
    Posicao = _Posicao;
    IDPeca.Cor = _Cor;
    IDPeca.NumJogadas=0;

    return;
}
//###############################################################
//###############################################################
//###############################################################

std::list<c_movimento> c_torre::encontrar_especiais(std::map<short int, s_idpeca> _Estado) {//##########
    //roquei
    std::list<c_movimento> _Movimentos;
    c_movimento *_aux;
    bool _zero_movimento=false;


    if(get_NumJogadas() == 0){//ja moveu a torre?
        if(IDPeca.Cor == BRANCO){//a peca e branca?
            if(_Estado[51].Peca == REI && _Estado[51].NumJogadas == 0){//o rei  branco esta na posicao e nao foi movido?
                _zero_movimento = true;
            }else return _Movimentos; //o rei branco moveu e nao retona nada
        }else// preta?
            if(_Estado[58].Peca == REI && _Estado[58].NumJogadas == 0){//o rei preto esta na posicao e nao foi movido?
                _zero_movimento = true;
            }else return _Movimentos; //o rei preto moveu e nao retona nada
    }else{
        return _Movimentos;//a torre moveu e nao retoena dana
    }

    if(_zero_movimento){
    //verifica se não tem nada no caminho
        if(get_posicao().get_x() == 1){ //roque grande?
            if(IDPeca.Cor == BRANCO){//branco
                if(_Estado[21].Peca == VAZIO && _Estado[31].Peca == VAZIO && _Estado[41].Peca == VAZIO){
                    _aux = new c_roque(Posicao,c_posicao(4,1),c_posicao(5,1),c_posicao(2,1));
                }else return _Movimentos;//tem coisa no meio do rei e da torre banco
            }else{//preto?
                if(_Estado[28].Peca == VAZIO && _Estado[38].Peca == VAZIO && _Estado[48].Peca == VAZIO){
                    _aux = new c_roque(Posicao,c_posicao(4,8),c_posicao(5,8),c_posicao(2,8));
                }else return _Movimentos;// tem coisa no meio do rei e da torre  preto
            }
        }else{//roque pqqueno
            if(IDPeca.Cor == BRANCO){//branco
                if(_Estado[61].Peca == VAZIO && _Estado[71].Peca == VAZIO){//meio vazio?
                    _aux = new c_roque(Posicao,c_posicao(6,1),c_posicao(5,1),c_posicao(7,1));
                }else return _Movimentos;
            }else{//preto
                if(_Estado[68].Peca == VAZIO && _Estado[78].Peca == VAZIO){
                    _aux = new c_roque(Posicao,c_posicao(6,8),c_posicao(5,8),c_posicao(7,8));
                }else return _Movimentos;
            }
        }// verificou se o meio esta vazio

        _Movimentos.push_back (*_aux);
    }
    return _Movimentos;
}



//###############################################################
//###############################################################
//###############################################################

//peao

c_peao::c_peao(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {

    DistMov[N]  = 0;
    DistMov[NE] = 0;
    DistMov[E]  = 0;
    DistMov[SE] = 0;
    DistMov[S]  = 0;
    DistMov[SO] = 0;
    DistMov[O]  = 0;
    DistMov[NO] = 0;

    DistCome = DistMov;

    IDPeca.Peca = PEAO;//eh um enum
    Posicao = _Posicao;
    IDPeca.Cor = _Cor;
    IDPeca.NumJogadas=0;

    if(_Cor==BRANCO){
        DistMov[N]=1;
        DistCome[NE]=1;
        DistCome[NO]=1;
    }else{
        DistMov[S]=1;
        DistCome[SE]=1;
        DistCome[SO]=1;
    }


    return;
}

std::list<c_movimento> c_peao::encontrar_especiais() {

    //implementar

    return std::list<c_movimento>();
}

//cavalo

c_cavalo::c_cavalo(e_cor _Cor, c_posicao _Posicao) : c_peca(_Cor, _Posicao) {

    DistMov[N]  = 0;
    DistMov[NE] = 0;
    DistMov[E]  = 0;
    DistMov[SE] = 0;
    DistMov[S]  = 0;
    DistMov[SO] = 0;
    DistMov[O]  = 0;
    DistMov[NO] = 0;

    DistCome = DistMov;

    IDPeca.Peca = CAVALO;//eh um enum
    Posicao = _Posicao;
    IDPeca.Cor = _Cor;


    return;
}

std::list<c_movimento> c_cavalo::encontrar_especiais() {

    //implementar

    return std::list<c_movimento>();
}

