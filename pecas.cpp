#include <iostream>
#include <list>

#include "pecas.hpp"
#include "tabuleiro.hpp"

c_posicao::c_posicao(short int _x, short int _y) {
	x = _x;
	y = _y;

	return;
}

// Construtor para criar posicoes relativas(Nao validas)
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

// Verifica se a posicao e valida (Dentro da grade 8x8)
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

// Verifica se duas posicoes nao sao iguais
bool c_posicao::operator!=(c_posicao &_temp) {
	return ((x != _temp.get_x()) || (y != _temp.get_y()));
}

// Retorna uma chave para mapear o tabuleiro
short int c_posicao::operator!() {
	if(validar()) {
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

void c_peca::atualizar_posicao(c_posicao _Posicao) {
	if(_Posicao.validar()) {
		Posicao = _Posicao;

	}

	return;
}

std::list<c_movimento> c_peca::encontrar_movimentos() {
	std::list<c_movimento> _Movimentos;

	return _Movimentos;
}

/*std::list<c_movimento> encontrar_capturas();
bool ameacando_rei();
e_cor get_cor();
c_posicao get_posicao();
void atualizar_posicao(c_posicao _Posicao);*/

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
    Pontuacao = BISPO;//BISPO eh um enum
    Posicao = _Posicao;
    Cor = _Cor;

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
    Pontuacao = RAINHA;//eh um enum
    Posicao = _Posicao;
    Cor = _Cor;

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
    Pontuacao = REI;//eh um enum
    Posicao = _Posicao;
    Cor = _Cor;
    NumJogadas=0;

    return;
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
    Pontuacao = TORRE;//eh um enum
    Posicao = _Posicao;
    Cor = _Cor;
    NumJogadas=0;

    return;
}

std::list<c_movimento> c_torre::encontrar_especiais() {

    //implementar

    return std::list<c_movimento>();
}

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

    Pontuacao = PEAO;//eh um enum
    Posicao = _Posicao;
    Cor = _Cor;
    NumJogadas=0;

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

    Pontuacao = CAVALO;//eh um enum
    Posicao = _Posicao;
    Cor = _Cor;


    return;
}

std::list<c_movimento> c_cavalo::encontrar_especiais() {

    //implementar

    return std::list<c_movimento>();
}

