#include <iostream>
#include <thread>

#include "GUI.hpp"
#include "IA.hpp"
#include "pecas.hpp"
#include "tabuleiro.hpp"

#include "testes.hpp"

int main() {
	//testar_promocao();
	
	std::thread teste(testar_interface_jogo);
	teste.join();

	return 0;
}
