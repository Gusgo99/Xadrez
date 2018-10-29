#include <iostream>

#include "tabuleiro.hpp"
#include "utilidades.hpp"
#include "pecas.hpp"

c_jogo::c_jogo() {
	Promocao = false;
	Turno = 1;
	Xeque = false;
	PosicaoAmeaca = nullptr;
	PosicaoAmeacado = nullptr;

	for(auto i: Tabuleiro) {
		i.second = nullptr;

	}

	for(auto i = 1; i <= 8; i++) {
		//inserir_peca<c_peao>(c_posicao(i, 2), BRANCO);
		//inserir_peca<c_peao>(c_posicao(i, 7), PRETO);

	}

	inserir_peca<c_torre>(c_posicao(1, 1), BRANCO);
	inserir_peca<c_torre>(c_posicao(8, 1), BRANCO);
	/*inserir_peca<c_torre>(c_posicao(1, 8), PRETO);
	inserir_peca<c_torre>(c_posicao(8, 8), PRETO);

	inserir_peca<c_cavalo>(c_posicao(2, 1), BRANCO);
	inserir_peca<c_cavalo>(c_posicao(7, 1), BRANCO);
	inserir_peca<c_cavalo>(c_posicao(2, 8), PRETO);
	inserir_peca<c_cavalo>(c_posicao(7, 8), PRETO);

	inserir_peca<c_bispo>(c_posicao(3, 1), BRANCO);
	inserir_peca<c_bispo>(c_posicao(6, 1), BRANCO);
	inserir_peca<c_bispo>(c_posicao(3, 8), PRETO);
	inserir_peca<c_bispo>(c_posicao(6, 8), PRETO);

	inserir_peca<c_rainha>(c_posicao(4, 8), PRETO);
	inserir_peca<c_rainha>(c_posicao(4, 1), BRANCO);
	inserir_peca<c_rei>(c_posicao(5, 1), BRANCO);*/
	inserir_peca<c_rei>(c_posicao(5, 8), PRETO);

	ReiBranco = Tabuleiro[!c_posicao(5, 1)];
	ReiPreto = Tabuleiro[!c_posicao(5, 8)];

	return;
}

bool c_jogo::get_xeque() {
	return Xeque;
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

std::list<c_movimento*> c_jogo::get_movimentos(c_posicao _Posicao) {
	std::list<c_movimento*> _Movimentos;
	std::map<short int, s_idpeca> _Estado = get_estado();
	
	_Estado[!_Posicao].Cor = SEMCOR;
	_Estado[!_Posicao].Peca = VAZIO;

	if(_Posicao.validar()) {
		if(Tabuleiro[!_Posicao] != nullptr) {
			_Movimentos = Tabuleiro[!_Posicao] -> listar_movimentos(get_estado());
			
			for(auto i: _Movimentos) {
				_Estado[!(i -> get_fim())] = Tabuleiro[!_Posicao] -> get_ID();
				
				verificar_xeque(_Estado);
				
				if(Xeque) {
					if(i -> get_fim() != *PosicaoAmeaca) {
						_Movimentos.remove(i);
						
					}
					Xeque = false;
					
				}
				
				_Estado[!(i -> get_fim())].Peca = VAZIO;
				_Estado[!(i -> get_fim())].Cor = SEMCOR;
			}
		}
	}

	return _Movimentos;
}

template<typename _Peca>
void c_jogo::inserir_peca(c_posicao _Posicao, e_cor _Cor) {
	Tabuleiro[!_Posicao] = new _Peca(_Cor, _Posicao);

	return;
}

std::map<short int,bool> c_jogo::get_ameacas(e_cor _Cor){
    std::map<short int,bool> _Ameacas;

    for(auto i: Tabuleiro){
        if(i.second != nullptr){
            std::map<short int,bool> _AmeacasAux;
            _AmeacasAux = i.second -> encontrar_ameacas(get_estado());

            for(auto j: _AmeacasAux){

                if(j.second) j.second=true;

            }
        }
    }

    return _Ameacas;
}

void c_jogo::operator+=(c_movimento &_Movimento) {
	Turno++;

	Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_inicio()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim())) Promocao = true;

	verificar_xeque();

	return;
}

void c_jogo::operator+=(c_captura &_Movimento) {
	Turno++;

	delete Tabuleiro[!_Movimento.get_fim()];
	Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_inicio()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim())) Promocao = true;

	verificar_xeque();

	return;
}

void c_jogo::operator+=(c_roque &_Movimento) {
	Turno++;

	Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_inicio()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim())) Promocao = true;

	Tabuleiro[!_Movimento.get_fim_torre()] = Tabuleiro[!_Movimento.get_inicio_torre()];
	Tabuleiro[!_Movimento.get_inicio_torre()] = nullptr;
	if(Tabuleiro[!_Movimento.get_fim_torre()] -> atualizar_posicao(_Movimento.get_fim_torre())) Promocao = true;

	verificar_xeque();

	return;
}

void c_jogo::operator+=(c_promocao &_Movimento) {
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
			throw 20;
			break;

	}

	delete Tabuleiro[!_Movimento.get_inicio()];
	Tabuleiro[!_Movimento.get_fim()] = _Temp;

	verificar_xeque();

	return;
}

bool c_jogo::get_promocao() {
	return Promocao;
}

e_cor c_jogo::get_turno() {
	if((Turno % 2) == 1) {
		return BRANCO;

	}
	else {
		return PRETO;

	}

}

void c_jogo::verificar_xeque() {
	std::map<short int, s_idpeca> _Estado = get_estado();

	Xeque = false;
	delete PosicaoAmeaca;
	delete PosicaoAmeacado;
	PosicaoAmeaca = nullptr;
	PosicaoAmeacado = nullptr;

	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			if(i.second -> ameacando_rei(_Estado)) {
				Xeque = true;
				PosicaoAmeaca = new c_posicao(!(i.second -> get_posicao()));
				if(i.second -> get_cor() == BRANCO) {
					PosicaoAmeacado = new c_posicao(!(ReiPreto -> get_posicao()));

				}
				else {
					PosicaoAmeacado = new c_posicao(!(ReiBranco -> get_posicao()));

				}
				break;

			}
		}
	}

	return;
}

void c_jogo::verificar_xeque(std::map<short int, s_idpeca> _Estado) {
	Xeque = false;
	delete PosicaoAmeaca;
	delete PosicaoAmeacado;
	PosicaoAmeaca = nullptr;
	PosicaoAmeacado = nullptr;

	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			if(i.second -> ameacando_rei(_Estado)) {
				Xeque = true;
				PosicaoAmeaca = new c_posicao(!(i.second -> get_posicao()));
				if(i.second -> get_cor() == BRANCO) {
					PosicaoAmeacado = new c_posicao(!(ReiPreto -> get_posicao()));

				}
				else {
					PosicaoAmeacado = new c_posicao(!(ReiBranco -> get_posicao()));

				}
				break;

			}
		}
	}

	return;
}

c_posicao c_jogo::get_posicao_ameaca() {
	return *PosicaoAmeaca;
}

c_posicao c_jogo::get_posicao_ameacado() {
	return *PosicaoAmeacado;
}

bool c_jogo::verificar_mate() {
	for(auto i: Tabuleiro) {
		if(i.second != nullptr) {
			if(i.second -> get_cor() == get_turno()) {
				std::list<c_movimento*> _Movimentos = get_movimentos(!c_posicao(i.first));
				if(_Movimentos.size() != 0) {
					return false;
					
				}
				else {
					for(auto i: _Movimentos) {
						delete i;
						
					}
					_Movimentos.clear();
				}
			}
		}
	}
	
	return true;
}