#include "avaliador.h"
/*
 * incluir outras buscas
 */
#include "labirinto.h"
#include "bfs.h"
#include "dfs.h"
#include "a_star.h"
#include "best_first_search.h"

#include <chrono>
#include <iostream>

avaliador::~avaliador(){}
avaliador::avaliador(){}


double avaliador::tempoDecorrido(Search *busca){
    std::chrono::time_point<std::chrono::high_resolution_clock> tStart(std::chrono::high_resolution_clock::now());
    busca->executar();
    std::chrono::time_point<std::chrono::high_resolution_clock> tEnd(std::chrono::high_resolution_clock::now());
    std::cout << std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart).count()<< "\n";
    return 0.;
}

void avaliador::operator()(){
    for(int size = 10 ; size < 51 ; size += 10){
        for(int i = 0 ; i < 1 ; i++){
            std::cout << "labirinto de tamanho " << size << " x " << size << "\n";
            labirinto l(size ,size);
            l.nova_geracao(10 + 2*size/10);
            Best_first best;
            bfsSearch bfs;
            dfsSearch dfs;
            //A_star a_star(l);
            best.setMap(l);
            bfs.setMap(l);
            dfs.setMap(l);
            std::cout << this->tempoDecorrido(&best) << "\n";
            std::cout << this->tempoDecorrido(&bfs) << "\n";
            std::cout << this->tempoDecorrido(&dfs) << "\n";
            //std::cout << this->tempoDecorrido(&a_star) << "\n";
        }
    }
}


