#include "GUI.hpp"
#include "tabuleiro.hpp"

#include "principal.hpp"

c_principal::c_principal() {
	c_tabuleiro jogo;
	
	c_interfaceJogo interface("Chess", &jogo, BRANCO);
	
	interface.desenhar_janela();
	
	return;
}
