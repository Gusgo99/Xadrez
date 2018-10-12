#include <iostream>

#include "testes.hpp"
#include "GUI.hpp"
#include "IA.hpp"
#include "pecas.hpp"
#include "tabuleiro.hpp"

void testar_posicao() {
	std::cout << "Iniciando testes da classe c_posicao" << std::endl;
	
	auto x = 0, y = 0;
	c_posicao a;
	c_posicao b;
	
	do {
		std::cout << "Digite a posicao a: ";
		std::cin >> x >> y;
		
		a = c_posicao(x, y);
		
		if(a.validar()) {
			std::cout << "Posicao digitada: (" << a.get_x() << ", " << a.get_y() << ")" << std::endl;
			std::cout << "Codigo da posicao: " << !a << std::endl;
			
		}
		else {
			std::cout << "Posicao digitada e invalida" << std::endl;
			
		}
		
	} while(!a.validar());
	
	do {
		std::cout << "Digite a posicao b: ";
		std::cin >> x >> y;
		
		b = c_posicao(x, y);
		
		if(b.validar()) {
			std::cout << "Posicao digitada: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
			std::cout << "Codigo da posicao: " << !b << std::endl;
			
		}
		else {
			std::cout << "Posicao digitada e invalida" << std::endl;
			
		}
		
	} while(!b.validar());
	
	std::cout << "Os dois pontos " << (a == b ? "" : "nao ") << "sao iguais" << std::endl;
	
	std::cout << "Distancia entre pontos: " << (b - a) << std::endl;
	
	std::cout << "Composicao de movimento a >> b" << std::endl;
	
	c_movimento mov = a >> b;
	
	std::cout << "Posicao de saida: (" << mov.get_inicio().get_x() << ", " << mov.get_inicio().get_y() << ")" << std::endl;
	
	std::cout << "Posicao de chegada: (" << mov.get_fim().get_x() << ", " << mov.get_fim().get_y() << ")" << std::endl;
	
	std::cout << "Composicao de movimento a << b" << std::endl;
	
	mov = a << b;
	
	std::cout << "Posicao de saida: (" << mov.get_inicio().get_x() << ", " << mov.get_inicio().get_y() << ")" << std::endl;
	
	std::cout << "Posicao de chegada: (" << mov.get_fim().get_x() << ", " << mov.get_fim().get_y() << ")" << std::endl;
	
	std::cout << "Teste de copia de posicao a = b" << std::endl;
	
	a = b;
	
	std::cout << "Posicao b: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;

	std::cout << "Posicao a: (" << a.get_x() << ", " << a.get_y() << ")" << std::endl;

	std::cout << "Teste de copia de validade:" << std::endl;
	
	b = c_posicao(0, 15);
	
	a = b;
	
	std::cout << "b(Invalido): " << (b.validar() ? "Valido" : "Invalido") << std::endl;
	
	std::cout << "a(Invalido): " << (a.validar() ? "Valido" : "Invalido") << std::endl;
	
	b = c_posicao(1, 1);
	
	a = b;
	
	std::cout << "b(Valido): " << (b.validar() ? "Valido" : "Invalido") << std::endl;
	
	std::cout << "a(Valido): " << (a.validar() ? "Valido" : "Invalido") << std::endl;
	
	return;
}

void testar_movimento() {
	
	return;
}