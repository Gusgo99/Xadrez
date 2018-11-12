#include <iostream>
#include <thread>

#include "testes.hpp"
#include "GUI.hpp"
#include "IA.hpp"
#include "pecas.hpp"
#include "tabuleiro.hpp"
#include "principal.h"

principal::principal(){;
    c_jogo jogo;

	c_interfaceJogo janela("Chess", &jogo, BRANCO);

	janela.desenhar_janela();
    return;
}









