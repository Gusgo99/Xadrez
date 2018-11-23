#ifndef PECAS_HPP
#define PECAS_HPP

#include <array>
#include <list>
#include <map>

class c_movimento;
class c_captura;
class c_roque;
class c_promocao;
class c_posicao;

class c_peca;
class c_bispo;
class c_peao;
class c_cavalo;
class c_rei;
class c_torre;

enum e_dir {
	N = 0x01,
	S = 0x02,
	E = 0x04,
	O = 0x08,
	NE = N | E,
	SE = S | E,
	NO = N | O,
	SO = S | O};

// Define tipo e constantes para cores das pecas
enum e_cor {SEMCOR, BRANCO, PRETO};

// Define tipo e constantes para pecas do jogo
enum e_peca {VAZIO, PEAO, CAVALO, BISPO, TORRE, RAINHA, REI};

// Armazena cor e tipo da peca
struct s_idpeca {
	s_idpeca() {Cor = SEMCOR; Peca = VAZIO; NumJogadas = 0;}
	e_cor Cor;
	e_peca Peca;
    unsigned NumJogadas;

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_posicao:
 *
 * Responsavel por:
 *
 * - Armazenar posicao de cada peca;
 * - Verificar se a posicao e valida;
 * - Gerar chave para encontrar a peca em determinada posicao
 * dentro dos mapas;
 * - Compor movimentos;
 * - Gerar novas posicoes a partir de posicoes relativas;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
class c_posicao {
	private:
		short int x;
		short int y;

	public:
		c_posicao(const short int _ID = 0);
		c_posicao(const short int _x, short int _y);
		c_posicao(const e_dir _Direcao, const short int _Distancia);
		~c_posicao() {}
		// Geram uma nova posicao a partir de uma segunda posicao relativa
		c_posicao operator+(c_posicao &_temp);
		void operator+=(c_posicao &_temp);
		
		// Verifica se as posicoes sao as mesmas
		bool operator==(c_posicao &_temp);
		// Verifica se as posicoes sao diferentes
		bool operator!=(c_posicao &_temp);
		// Retorna uma chave para facilitar o mapeamento do tabuleiro
		short int operator!();
		// Compoem movimentos
		const c_movimento operator>>(c_posicao &_temp);
		const c_movimento operator<<(c_posicao &_temp);
		
		short int get_x();
		short int get_y();
		void set_x(const short int _x);
		void set_y(const short int _y);
		void set_xy(const short int _x, short int _y);
		// Verifica se a posicao esta dentro do tabuleiro
		bool validar();

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_movimento:
 *
 * Responsavel por:
 *
 * - Armazenar posicao de saida e destino da peca;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_movimento {
	protected:
		// Posicao de onde a peca saira
		c_posicao PosInicial;
		// Posicao para onde a peca ira
		c_posicao PosFinal;
		// Posicao de onde a torre saira
		c_posicao PosInicialTorre;
		// Posicao para onde a torre ira
		c_posicao PosFinalTorre;

	public:
		// Construtor
		c_movimento(const c_posicao _PosInicial = c_posicao(0, 0), const c_posicao _PosFinal = c_posicao(0, 0));
		virtual ~c_movimento() {}
		c_posicao get_inicio();
		c_posicao get_fim();
		c_posicao get_inicio_torre();
		c_posicao get_fim_torre();
		void set_inicio(c_posicao _PosInicial);
		void set_fim(c_posicao _PosFinal);
		void set_inicio_torre(c_posicao _PosInicial);
		void set_fim_torre(c_posicao _PosFinal);

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_captura:
 *
 * Responsavel por:
 *
 * - Armazenar posicao de saida e destino da peca;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_captura : public c_movimento {
	private:
	public:
		// Construtor da captura
		c_captura(c_posicao _PosInicial = c_posicao(0, 0), c_posicao _PosFinal = c_posicao(0, 0)) : c_movimento(_PosInicial, _PosFinal) {};
		~c_captura() {};

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_roque:
 *
 * Responsavel por:
 *
 * - Armazenar posicao de saida e destino do rei e da torre;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_roque : public c_movimento {
	public:
		// Construtor
		c_roque(const c_posicao _PosInicial, const c_posicao _PosFinal, c_posicao _PosInicialTorre, const c_posicao _PosFinalTorre);
		~c_roque() {};

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_promocao:
 *
 * Responsavel por:
 *
 * - Armazenar posicao de saida e destino da peca;
 * - Armazenar novo tipo do peao apos a promocao;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_promocao : public c_movimento {
	protected:
		// Tipo da nova peca (BISPO, TORRE, RAINHA, CAVALO)
		e_peca NovaPeca;

	public:
		// Construtor
		c_promocao(const c_posicao _PosInicial, const e_peca _NovaPeca);
		e_peca get_nova_peca();
		void set_nova_peca(const e_peca _NovaPeca);
		~c_promocao() {}

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe c_peca:
 *
 * Responsavel por:
 *
 * - Listar possiveis movimentos da peca;
 * - Armazenar posicao atual da peca;
 * - Armazenar numero de movimentos realizados;
 * - Verificar se a peca ameaca o rei inimigo;
 * - Marcar posicao da peca no estado;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
class c_peca {
	protected:
		// Distancia maxima que a peca pode se mover em cada direcao
		std::map<e_dir, short int> DistMov;
		// Distancia maxima que a peca pode comer em cada direcao
		std::map<e_dir, short int> DistCome;
		// Identificacao da peca (Tipo e cor)
		s_idpeca IDPeca;
		// Posicao da peca no tabuleiro
		c_posicao Posicao;
		// Calcula possiveis movimentos
		virtual std::list<c_movimento*> encontrar_movimentos(std::map<short int, s_idpeca> _Estado);
		// Calcula possiveis capturas
		virtual std::list<c_movimento*> encontrar_capturas(std::map<short int, s_idpeca> _Estado);
		
	public:
		c_peca(const e_cor _Cor = SEMCOR, const c_posicao _Posicao = c_posicao(0, 0));
		virtual ~c_peca();
		// Lista movimentos possiveis
		virtual std::list<c_movimento*> listar_movimentos(const std::map<short int, s_idpeca> _Estado);
		// Verifica se a peca esta ameacando o rei inimigo
		bool ameacando_rei(std::map<short int, s_idpeca> _Estado);
		// Realiza a atualizacao da posicao apos realizar o movimento
		virtual bool atualizar_posicao(const c_posicao _Posicao);
		// Faz com que cada peca marque sua posicao no tabuleiro
		void marcar_posicao(std::map<short int, s_idpeca> *_Estado);
		
		s_idpeca get_ID();
		e_cor get_cor();
		e_peca get_peca();
		c_posicao get_posicao();
		unsigned get_num_jogadas();
};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Especializacoes da classe peca:
 *
 * Classes implementadas:
 *
 * - c_peao;
 * - c_torre;
 * - c_cavalo;
 * - c_bispo;
 * - c_rainha;
 * - c_rei;
 *
 * Funcoes das classes:
 * - Ajustar atributos de acordo com o tipo da peca;
 * - Adicionar movimentos especiais a lista de movimentos
 * disponiveis;
 * - Alterar movimentos retornados(c_cavalo);
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe derivada c_peca:
 *
 * Responsavel por:
 *
 * - Atributos alterados de acordo com o movimento do peao;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
class c_peao : public c_peca {
	public:
	    c_peao(const e_cor _Cor, const c_posicao _Posicao);
		~c_peao() {}
		bool atualizar_posicao(const c_posicao _Posicao);

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe derivada c_torre:
 *
 * Responsavel por:
 *
 * - Atributos alterados de acordo com o movimento da torre;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
class c_torre : public c_peca {
	public:
	    c_torre(const e_cor _Cor, const c_posicao _Posicao);
		~c_torre() {}

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe derivada c_cavalo:
 *
 * Responsavel por:
 *
 * - Funcoes de movimentos redefinidas de acordo com os
 * movimentos do cavalo;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_cavalo : public c_peca {
	private:
		std::list<c_movimento*> encontrar_movimentos(std::map<short int, s_idpeca> _Estado);
	    std::list<c_movimento*> encontrar_capturas(std::map<short int, s_idpeca> _Estado);

	public:
	    c_cavalo(e_cor _Cor, c_posicao _Posicao);
		~c_cavalo() {}
		std::list<c_movimento*> listar_movimentos(std::map<short int, s_idpeca> _Estado);

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe derivada c_bispo:
 *
 * Responsavel por:
 *
 * - Atributos alterados de acordo com o movimento do bispo;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

class c_bispo : public c_peca {
	public:
		c_bispo(e_cor _Cor, c_posicao _Posicao);
		~c_bispo() {}


};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe derivada c_rainha:
 *
 * Responsavel por:
 *
 * - Atributos alterados de acordo com o movimento da rainha;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
class c_rainha : public c_peca {
	public:
		c_rainha(e_cor _Cor, c_posicao _Posicao);
		~c_rainha() {}

};

/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
 *
 * Classe derivada c_rei:
 *
 * Responsavel por:
 *
 * - Atributos alterados de acordo com o movimento do rei;
 * - Roque adicionado a lista de movimentos retornados;
 *
 * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */
 
class c_rei : public c_peca {
	private:
		std::list<c_movimento*> encontrar_especiais(std::map<short int, s_idpeca> _Estado);

	public:
	    c_rei(e_cor _Cor, c_posicao _Posicao);
		~c_rei() {}
		std::list<c_movimento*> listar_movimentos(std::map<short int, s_idpeca> _Estado);
};

#endif
