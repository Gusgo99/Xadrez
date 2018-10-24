#include <iostream>

#include "tabuleiro.hpp"
#include "utilidades.hpp"
#include "pecas.hpp"

c_jogo::c_jogo() {
	for(auto i: Tabuleiro) {
		i.second = nullptr;
		
	}
	
	for(auto i = 1; i <= 8; i++) {
		inserir_peca<c_peao>(c_posicao(i, 2), BRANCO);
		inserir_peca<c_peao>(c_posicao(i, 7), PRETO);
		
	}
	
	inserir_peca<c_torre>(c_posicao(1, 1), BRANCO);
	inserir_peca<c_torre>(c_posicao(8, 1), BRANCO);
	inserir_peca<c_torre>(c_posicao(1, 8), PRETO);
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
	inserir_peca<c_rei>(c_posicao(5, 1), BRANCO);
	inserir_peca<c_rei>(c_posicao(5, 8), PRETO);
	
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
	if(_Posicao.validar()) {
		if(Tabuleiro[!_Posicao] != nullptr) {
			return Tabuleiro[!_Posicao] -> listar_movimentos(get_estado());
			
		}
	}
	
	return std::list<c_movimento*>();
}

template<class _Peca>
void c_jogo::inserir_peca(c_posicao _Posicao, e_cor _Cor) {
	Tabuleiro[!_Posicao] = new _Peca(_Cor, _Posicao);
	
	return;
}

void c_jogo::operator+=(c_movimento &_Movimento) {
	switch(_Movimento.get_tipo()) {
		case SIMPLES:
		case CAPTURA:
			if(_Movimento.get_inicio().validar() && _Movimento.get_fim().validar()) {
				if(Tabuleiro[!_Movimento.get_fim()] != nullptr) {
					delete Tabuleiro[!_Movimento.get_fim()];
					
				}
				Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
				Tabuleiro[!_Movimento.get_inicio()] = nullptr;
				Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim());
				
			}
			break;
			
		case ROQUEMENOR:
			if(_Movimento.get_inicio().validar() && _Movimento.get_fim().validar()) {
				c_posicao _Temp = c_posicao(E, 3);
				c_posicao _PosicaoInicialTorre = _Movimento.get_inicio() + _Temp;
				_Temp = c_posicao(E, 1);
				c_posicao _NovaPosicaoTorre = _Movimento.get_inicio() + _Temp;
				Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
				Tabuleiro[!_NovaPosicaoTorre] = Tabuleiro[!_PosicaoInicialTorre];
				Tabuleiro[!_Movimento.get_inicio()] = nullptr;
				Tabuleiro[!_PosicaoInicialTorre] = nullptr;
				Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim());
				Tabuleiro[!_NovaPosicaoTorre] -> atualizar_posicao(_NovaPosicaoTorre);
				
			}
			break;
			
		case ROQUEMAIOR:
			if(_Movimento.get_inicio().validar() && _Movimento.get_fim().validar()) {
				c_posicao _Temp = c_posicao(O, 4);
				c_posicao _PosicaoInicialTorre = _Movimento.get_inicio() + _Temp;
				_Temp = c_posicao(O, 1);
				c_posicao _NovaPosicaoTorre = _Movimento.get_inicio() + _Temp;
				Tabuleiro[!_Movimento.get_fim()] = Tabuleiro[!_Movimento.get_inicio()];
				Tabuleiro[!_NovaPosicaoTorre] = Tabuleiro[!_PosicaoInicialTorre];
				Tabuleiro[!_Movimento.get_inicio()] = nullptr;
				Tabuleiro[!_PosicaoInicialTorre] = nullptr;
				Tabuleiro[!_Movimento.get_fim()] -> atualizar_posicao(_Movimento.get_fim());
				Tabuleiro[!_NovaPosicaoTorre] -> atualizar_posicao(_NovaPosicaoTorre);
				
			}
			break;
			
		case PROMOCAO:
			
			break;
			
	}
	
	return;
}
