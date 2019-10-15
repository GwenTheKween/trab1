#include "avaliador.h"
#include "bfs.h"
#include "dfs.h"
/*
 * incluir outras buscas
 */
#include "labirinto.h"

#include <ctime>

avaliador::~avaliador(){}
avaliador::avaliador(){}


double avaliador::tempoDecorrido(Search *busca){
    clock_t inicio = clock();
    busca->executar();
    return (clock()-inicio) / CLOCKS_PER_SEC;
}

void avaliador::operator()(){
    
}


