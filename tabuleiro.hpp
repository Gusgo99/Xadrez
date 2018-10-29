#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

class c_jogo;
class c_movimento;

#include <array>
#include <map>

#include "pecas.hpp"

class c_jogo {
	private:
		std::map<short int, c_peca*> Tabuleiro;
		c_peca *ReiBranco;
		c_peca *ReiPreto;
		unsigned Turno;
		unsigned JogadasRestantes;
		bool Promocao;
		bool Xeque;
		template<typename T>
		void inserir_peca(c_posicao _Posicao, e_cor _Cor);
		void verificar_xeque();
		c_posicao *PosicaoAmeaca;
		c_posicao *PosicaoAmeacado;

	public:
		c_jogo();
		c_jogo(c_jogo *_original);
		salvar_jogo();
		carregar_jogo();
		void operator+=(c_movimento &_Movimento);
		void operator+=(c_captura &_Movimento);
		void operator+=(c_roque &_Movimento);
		void operator+=(c_promocao &_Movimento);
		std::map<short int, s_idpeca> get_estado();
		bool get_xeque();
		std::list<c_movimento*> get_movimentos(c_posicao _Posicao);
		std::map<short int,bool> get_ameacas(e_cor _Cor);
		bool get_promocao();
		e_cor get_turno();
		c_posicao get_posicao_ameaca();
		c_posicao get_posicao_ameacado();

};

#endif
