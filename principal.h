#ifndef PRINCIPAL_H_INCLUDED
#define PRINCIPAL_H_INCLUDED

#include "principal.h"
#include "GUI.hpp"
#include "IA.hpp"
#include "pecas.hpp"
#include "tabuleiro.hpp"


class principal{
    private:
        c_jogo *jogo;
        c_interfaceJogo *janela;

    public:
        principal();
        ~principal();
};







#endif // PRINCIPAL_H_INCLUDED
