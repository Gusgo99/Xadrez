#include <iostream>
#include <thread>

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
	
	if(a == b) {
		std::cout << "a == b" << std::endl;
		
	}
	
	if(a != b) {
		std::cout << "a != b" << std::endl;
		
	}
	
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
	
	std::cout << "Iniciando teste de direcao:" << std::endl;
	
	a = c_posicao(4, 4);
	
	b = c_posicao(N, 1);
	
	std::cout << "Posicao a: (" << a.get_x() << ", " << a.get_y() << ")" << std::endl;
	
	b += a;
	
	std::cout << "Distancia 1 na direcao N: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	b = c_posicao(S, 1);
	
	b = a + b;
	
	std::cout << "Distancia 1 na direcao S: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	b = c_posicao(E, 1);
	
	b = a + b;
	
	std::cout << "Distancia 1 na direcao E: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	b = c_posicao(O, 1);
	
	b = a + b;
	
	std::cout << "Distancia 1 na direcao O: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	b = c_posicao(NE, 1);
	
	b = a + b;
	
	std::cout << "Distancia 1 na direcao NE: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	b = c_posicao(NO, 1);
	
	b = a + b;
	
	std::cout << "Distancia 1 na direcao NO: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	b = c_posicao(SE, 1);
	
	b = a + b;
	
	std::cout << "Distancia 1 na direcao SE: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	b = c_posicao(SO, 1);
	
	b = a + b;
	
	std::cout << "Distancia 1 na direcao SO: (" << b.get_x() << ", " << b.get_y() << ")" << std::endl;
	
	return;
}

void testar_movimento() {
	
	return;
}

void testar_interface_jogo() {
	c_jogo jogo;
	
	c_interfaceJogo teste("Chess", nullptr, BRANCO);
	
	teste.desenhar_janela();
	
	return;
}