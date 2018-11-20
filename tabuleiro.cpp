#include <fstream>
#include <iostream>

#include "tabuleiro.hpp"
#include "utilidades.hpp"
#include "pecas.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Construtores e destrutores da classe c_tabuleiro
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

c_tabuleiro::c_tabuleiro() {
	Promocao = false;
	Xeque = false;
	Mate = false;
	Turno = 1;
	PosicaoAmeaca = c_posicao();
	PosicaoAmeacado = c_posicao();

	for(auto &i: Tabuleiro) {
		i.second = nullptr;

	}
	
	carregar_pecas("resources/pecas.dat");
	
	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			if(i.second -> get_peca() == REI) {
				if(i.second -> get_cor() == BRANCO) {
					ReiBranco = i.second;
					
				}
				else {
					ReiPreto = i.second;
					
				}
				
			}
		}
	}

	return;
}

c_tabuleiro::~c_tabuleiro() {
	for(auto &i: Tabuleiro) {
		delete i.second;
		i.second = nullptr;
		
	}
	
	return;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Metodos publicos da classe c_tabuleiro
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

void c_tabuleiro::operator+=(c_movimento &_Movimento) {
	Turno++;

	Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_inicio()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim())) Promocao = true;
	
	verificar_mate();
	verificar_xeque();

	return;
}

void c_tabuleiro::operator+=(c_captura &_Movimento) {
	Turno++;

	delete Tabuleiro[!_Movimento.get_fim()];
	Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_inicio()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim())) Promocao = true;
	
	verificar_mate();
	verificar_xeque();

	return;
}

void c_tabuleiro::operator+=(c_roque &_Movimento) {
	Turno++;

	Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_inicio()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim())) Promocao = true;

	Tabuleiro[!_Movimento.get_fim_torre()] = Tabuleiro[!_Movimento.get_inicio_torre()];
	Tabuleiro[!_Movimento.get_inicio_torre()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim_torre()] -> atualizar_posicao(_Movimento.get_fim_torre())) Promocao = true;
	
	verificar_mate();
	verificar_xeque();

	return;
}

void c_tabuleiro::operator+=(c_promocao &_Movimento) {
	c_peca *_Temp = nullptr;

	Promocao = false;

	switch(_Movimento.get_nova_peca()) {
		case RAINHA:
			_Temp = new c_rainha(Tabuleiro[!_Movimento.get_inicio()] -> get_cor(), _Movimento.get_fim());
			break;

		case CAVALO:
			_Temp = new c_cavalo(Tabuleiro[!_Movimento.get_inicio()] -> get_cor(), _Movimento.get_fim());
			break;

		case TORRE:
			_Temp = new c_torre(Tabuleiro[!_Movimento.get_inicio()] -> get_cor(), _Movimento.get_fim());
			break;

		case BISPO:
			_Temp = new c_bispo(Tabuleiro[!_Movimento.get_inicio()] -> get_cor(), _Movimento.get_fim());
			break;

		default:
			break;

	}

	delete Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_fim()] = _Temp;
	
	verificar_mate();
	verificar_xeque();

	return;
}

std::map<short int, s_idpeca> c_tabuleiro::get_estado() {
	std::map<short int, s_idpeca> _Estado;

	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			i.second -> marcar_posicao(&_Estado);

		}
	}

	return _Estado;
}

std::list<c_movimento*> c_tabuleiro::get_movimentos(c_posicao _Posicao) {
	std::list<c_movimento*> _Movimentos;
	std::map<short int, s_idpeca> _Estado = get_estado();
	bool _Xeque = Xeque;
	
	_Estado[!_Posicao].Cor = SEMCOR;
	_Estado[!_Posicao].Peca = VAZIO;

	if(_Posicao.validar()) {
		if(Tabuleiro[!_Posicao] != nullptr) {
			_Movimentos = Tabuleiro[!_Posicao] -> listar_movimentos(get_estado());
			
			for(auto i: _Movimentos) {
				_Estado[!(i -> get_fim())] = Tabuleiro[!_Posicao] -> get_ID();
				verificar_xeque(_Estado);
				if(Xeque) {
					if(i -> get_fim() != PosicaoAmeaca) {
						_Movimentos.remove(i);
						
					}
					Xeque = false;
					
				}
				
				_Estado[!(i -> get_fim())].Peca = VAZIO;
				_Estado[!(i -> get_fim())].Cor = SEMCOR;
			}
		}
	}
	
	Xeque = _Xeque;

	return _Movimentos;
}

bool c_tabuleiro::get_xeque() {
	return Xeque;
}

bool c_tabuleiro::get_mate() {
	return Mate;
}

bool c_tabuleiro::get_promocao() {
	return Promocao;
}

e_cor c_tabuleiro::get_turno() {
	if((Turno % 2) == 1) {
		return BRANCO;

	}
	else {
		return PRETO;

	}
}

c_posicao c_tabuleiro::get_posicao_ameaca() {
	return PosicaoAmeaca;
}

c_posicao c_tabuleiro::get_posicao_ameacado() {
	return PosicaoAmeacado;
}

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 * 
 * Metodos privados da classe c_tabuleiro
 * 
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

template<typename _Peca>
void c_tabuleiro::inserir_peca(c_posicao _Posicao, e_cor _Cor) {
	Tabuleiro[!_Posicao] = new _Peca(_Cor, _Posicao);

	return;
}

void c_tabuleiro::verificar_xeque() {
	std::map<short int, s_idpeca> _Estado = get_estado();

	verificar_xeque(_Estado);

	return;
}

void c_tabuleiro::verificar_xeque(std::map<short int, s_idpeca> _Estado) {
	Xeque = false;

	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			if(i.second -> ameacando_rei(_Estado)) {
				Xeque = true;
				PosicaoAmeaca = i.second -> get_posicao();
				if(i.second -> get_cor() == BRANCO) {
					PosicaoAmeacado = ReiPreto -> get_posicao();

				}
				else {
					PosicaoAmeacado = ReiBranco -> get_posicao();

				}
				break;

			}
		}
	}

	return;
}

void c_tabuleiro::verificar_mate() {
	Mate = true;
	
	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			if(i.second -> get_cor() == get_turno()) {
				std::list<c_movimento*> _Movimentos = get_movimentos(!c_posicao(i.first));
				unsigned _Temp = _Movimentos.size();
				for(auto j: _Movimentos) {
					delete j;
					
				}
				_Movimentos.clear();
				
				if(_Temp != 0) {
					Mate = false;
					
				}
			}
		}
	}
	
	return;
}

void c_tabuleiro::carregar_pecas(std::string _nomeArquivo) {
	std::ifstream _arquivo(_nomeArquivo);
	
	if(_arquivo.is_open()) {
		int _NumPecas, _X, _Y, _Peca, _Cor;
		_arquivo >> _NumPecas;
		for(auto i = 0; i != _NumPecas; i++) {
			_arquivo >> _X >> _Y >> _Peca >> _Cor;
			switch(_Peca) {
				case PEAO:
					inserir_peca<c_peao>(c_posicao(_X, _Y), e_cor(_Cor));
					break;
					
				case TORRE:
					inserir_peca<c_torre>(c_posicao(_X, _Y), e_cor(_Cor));
					break;
					
				case CAVALO:
					inserir_peca<c_cavalo>(c_posicao(_X, _Y), e_cor(_Cor));
					break;
					
				case BISPO:
					inserir_peca<c_bispo>(c_posicao(_X, _Y), e_cor(_Cor));
					break;
					
				case RAINHA:
					inserir_peca<c_rainha>(c_posicao(_X, _Y), e_cor(_Cor));
					break;
					
				case REI:
					inserir_peca<c_rei>(c_posicao(_X, _Y), e_cor(_Cor));
					break;
					
				default:
					throw(15);
					break;
				
			}
		}
	}
	
	return;
}