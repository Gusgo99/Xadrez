#ifndef TABULEIRO_HPP
#define TABULEIRO_HPP

class c_tabuleiro;
class c_movimento;

#include <map>

#include "pecas.hpp"

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_tabuleiro:
 *
 * Responsavel por:
 *
 * - Armazenar ponteiros para cada peca no jogo;
 * - Verificar condicao do jogo(Xeque, promocao, mate);
 * - Executar movimentos;
 * - Disponibilizar informacoes sobre o estado atual do jogo;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_tabuleiro {
	private:
		// Aponta para cada instancia das pecas
		std::map<short int, c_peca*> Tabuleiro;
		// Ponteiro para o rei branco
		c_peca *ReiBranco;
		// Ponteiro para o rei preto
		c_peca *ReiPreto;
		// Indica turno atual
		unsigned Turno;
		// Indica se um peao pode realizar uma promocao
		bool Promocao;
		// Indica que uma peca esta em xeque
		bool Xeque;
		// Indica que o jogo terminou
		bool Mate;
		// Posicao onde esta a peca que ameaca o rei
		c_posicao PosicaoAmeaca;
		// Posicao do rei ameacado
		c_posicao PosicaoAmeacado;
		// Insere peca no tabuleiro
		template<typename T>
		void inserir_peca(c_posicao _Posicao, e_cor _Cor);
		// Executa verificacao do estado atual para encontrar xeque
		void verificar_xeque();
		// Executa verificacao do estado do argumento para encontrar xeque
		void verificar_xeque(std::map<short int, s_idpeca> _Estado);
		// Verifica se o jogo terminou
		void verificar_mate();
		// Carrega posicao das pecas de um arquivo
		void carregar_pecas(std::string _nomeArquivo);

	public:
		// Contrutor do jogo
		c_tabuleiro();
		// Destrutor
		~c_tabuleiro();
		// Funcoes para executar movimentos
		void operator+=(c_movimento &_Movimento);
		void operator+=(c_captura &_Movimento);
		void operator+=(c_roque &_Movimento);
		void operator+=(c_promocao &_Movimento);
		// Retorna estado atual do jogo
		std::map<short int, s_idpeca> get_estado();
		// Retorna movimentos disponiveis a serem realizados em dada posicao
		std::list<c_movimento*> get_movimentos(c_posicao _Posicao);
		// Verifica se o jogo esta em xeque
		bool get_xeque();
		// Verifica se o jogo terminou
		bool get_mate();
		// Verifica se um peao pode realizar uma promocao
		bool get_promocao();
		// Retorna o turno atual (BRANCO ou PRETO)
		e_cor get_turno();
		// Retorna posicao da peca que esta ameacando um dos reis
		c_posicao get_posicao_ameaca();
		// Retorna posicao do rei ameacado
		c_posicao get_posicao_ameacado();

};

#endif
