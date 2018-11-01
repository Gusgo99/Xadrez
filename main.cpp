#include <iostream>
#include <thread>

#include "testes.hpp"

int main() {
	std::thread teste(testar_interface_jogo);
	teste.join();

	return 0;
}
