#ifndef PRINCIPAL_HPP
#define PRINCIPAL_HPP

#include "GUI.hpp"
#include "tabuleiro.hpp"

class c_principal {
	private:
		c_tabuleiro Tabuleiro;
		c_interfaceJogo *interface;
	
	public:
		c_principal();
		~c_principal();
	
};

#endif
