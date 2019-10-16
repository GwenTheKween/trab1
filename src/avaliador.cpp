#include "avaliador.h"
/*
 * incluir outras buscas
 */
#include "labirinto.h"
#include "bfs.h"
#include "dfs.h"
#include "a_star.h"
#include "best_first_search.h"

#include <iostream>
#include <chrono>
#include <cmath>

avaliador::~avaliador(){}
avaliador::avaliador(){}

void calculaInformacoes(std::vector<uint64_t> &dados){
    double media = 0;
    for(auto &it : dados){
        media += it;
        std::cout << it << "\n";
    }
    media /= dados.size();
    std::cout << "média : " << media;
    double variancia = 0;
    for(auto &it : dados){
        variancia += (it - media) * (it - media);
    }
    variancia /= (dados.size() -1);
    std::cout << " variancia : " << variancia << " desvio padrão : " << sqrt(variancia) << "\n";
}

uint64_t avaliador::tempoDecorrido(Search *busca){
    std::chrono::time_point<std::chrono::high_resolution_clock> tStart(std::chrono::high_resolution_clock::now());
    busca->executar();
    std::chrono::time_point<std::chrono::high_resolution_clock> tEnd(std::chrono::high_resolution_clock::now());
    return std::chrono::duration_cast<std::chrono::microseconds>(tEnd - tStart).count();
}

void avaliador::operator()(){
    enum{
        A_STAR,
        BEST,
        BFS,
        DFS,
        QTD_ALG,
    };
    for(int size = 10 ; size < 101 ; size += 10){
        std::vector<std::vector<uint64_t>> tempos(QTD_ALG , std::vector<uint64_t>());
        std::cout << "labirinto de tamanho " << size << " x " << size << "\n";
        for(int i = 0 ; i < 100 ; i++){
            labirinto l(size ,size);
            l.nova_geracao(8 + 2*size/10);
            Best_first best;
            bfsSearch bfs;
            dfsSearch dfs;
            A_star a_star(l);
            best.setMap(l);
            bfs.setMap(l);
            dfs.setMap(l);
            tempos[A_STAR].push_back(this->tempoDecorrido(&a_start));
            tempos[BEST].push_back(this->tempoDecorrido(&best));
            tempos[BFS].push_back(this->tempoDecorrido(&bfs));
            tempos[DFS].push_back(this->tempoDecorrido(&dfs));
        }
        std::cout << "tempo A*\n";
        calculaInformacoes(tempos[A_STAR]);
        std::cout << "tempo Best First Search\n";
        calculaInformacoes(tempos[BEST]);
        std::cout << "tempo BFS\n";
        calculaInformacoes(tempos[BFS]);
        std::cout << "tempo DFS\n";
        calculaInformacoes(tempos[DFS]);
    }
}


