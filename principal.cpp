#include <iostream>
#include <thread>

//#include "testes.hpp"

#include "principal.h"


principal::principal(){;
    jogo = new c_jogo;

	janela = new c_interfaceJogo("Chess", jogo, BRANCO);

	janela->desenhar_janela();
    return;
}









