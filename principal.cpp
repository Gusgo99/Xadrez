#include "principal.hpp"

c_principal::c_principal() {
	interface = new c_interfaceJogo(std::string("Chess"), &Tabuleiro, BRANCO);
	
	interface -> desenhar_janela();
	
	return;
}

c_principal::~c_principal() {
	delete interface;
	
	return;
}