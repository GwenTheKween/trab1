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

/*
 * função que calcula a média, variancia e desvio dos tempo e quantidade de passos dado nos algoritmos do labirinto.
 */
void calculaInformacoes(std::vector<uint64_t> &dados , std::vector<uint64_t> &passos){
    double media = 0;
    double mediaPassos = 0;
    for(uint32_t i = 0 ; i < dados.size() ; i++){
        media += dados[i];
        mediaPassos += passos[i];
        std::cout << dados[i] << " " << passos[i] <<  "\n";
    }
    media /= dados.size();
    mediaPassos /= dados.size();
    double variancia = 0;
    double varianciaPassos = 0;
    for(uint32_t i = 0 ; i < dados.size() ; i++){
        variancia += (dados[i] - media) * (dados[i] - media);
        varianciaPassos += (passos[i] - mediaPassos) * (passos[i] - mediaPassos);
    }
    variancia /= (dados.size() -1);
    varianciaPassos /= (dados.size() -1);
    std::cout << "média  tempo: " << media << " variancia : " << variancia << " desvio padrão : " << sqrt(variancia) << "\n";
    std::cout << "média passos : " << mediaPassos << " variancia : " << varianciaPassos << " desvio padrão : " << sqrt(varianciaPassos) << "\n";
}

// função que calcula o tempo de execução da busca
uint64_t avaliador::tempoDecorrido(Search *busca){
    // utliza a biblioteca chrono para calcular o tempo gasto para a execução do programa.
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
    // esse for é para especificar o tamanho dos labirintos.
    for(int size = 10 ; size < 101 ; size += 10){
        // vetor com os valores de cada execução do labirinto de tamanho size x size
        std::vector<std::vector<uint64_t> > tempos(QTD_ALG , std::vector<uint64_t>());
        std::vector<std::vector<uint64_t> > passos(QTD_ALG , std::vector<uint64_t>());
        std::cout << "labirinto de tamanho " << size << " x " << size << "\n";
        // esse for é quem cria os labirintos e executa as buscas.
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
            tempos[A_STAR].push_back(this->tempoDecorrido(&a_star));
            passos[A_STAR].push_back(a_star.getSequenciaDeVisitados().size());
            tempos[BEST].push_back(this->tempoDecorrido(&best));
            passos[BEST].push_back(best.getSequenciaDeVisitados().size());
            tempos[BFS].push_back(this->tempoDecorrido(&bfs));
            passos[BFS].push_back(bfs.getSequenciaDeVisitados().size());
            tempos[DFS].push_back(this->tempoDecorrido(&dfs));
            passos[DFS].push_back(dfs.getSequenciaDeVisitados().size());
        }
        std::cout.precision(17);
        std::cout << "tempo A*\n";
        calculaInformacoes(tempos[A_STAR] , passos[A_STAR]);
        // printa os resultados.
        std::cout << "tempo Best First Search\n";
        calculaInformacoes(tempos[BEST] , passos[BEST]);
        std::cout << "tempo BFS\n";
        calculaInformacoes(tempos[BFS] , passos[BFS]);
        std::cout << "tempo DFS\n";
        calculaInformacoes(tempos[DFS] , passos[DFS]);
    }
}


