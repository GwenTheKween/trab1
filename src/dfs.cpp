#include "dfs.h"
#include "labirinto.h"

#include <stack>


dfsSearch::dfsSearch(){};

dfsSearch::~dfsSearch(){};

void dfsSearch::setMap(labirinto &map){
    this->map = &map;
}


const std::deque<std::pair<int,int> > &dfsSearch::getSequenciaDeVisitados() const{
    return  visitados;
}
bool dfsSearch::dfsRercusiva( std::vector<std::vector< std::pair<int , int > > > &mapaVisitados , std::pair<int , int> atual , std::pair< int ,int > &fim){
    if(atual == fim)
        return true;

    std::pair<int ,int> auxNaoVisitado(-1,-1);
    this->visitados.push_back(atual);

    std::vector<std::pair<int , int> > auxFilhos(8 , {0,0});
    auxFilhos[0] = {atual.first-1 , atual.second};
    auxFilhos[1] = {atual.first-1 , atual.second-1};
    auxFilhos[2] = {atual.first , atual.second-1};
    auxFilhos[3] = {atual.first+1 , atual.second-1};
    auxFilhos[4] = {atual.first+1 , atual.second};
    auxFilhos[5] = {atual.first+1 , atual.second+1};
    auxFilhos[6] = {atual.first , atual.second+1};
    auxFilhos[7] = {atual.first-1 , atual.second+1};

    for(int i = 0; i < 8 ; i++){
        if( ( auxFilhos[i].first >= 0 && auxFilhos[i].first < this->map->getHeight() ) && ( auxFilhos[i].second >= 0 && auxFilhos[i].second < this->map->getWidth() ) ){
            if(mapaVisitados[auxFilhos[i].first ][ auxFilhos[i].second] == auxNaoVisitado){
                if(this->map->operator[](auxFilhos[i]) != WALL){
                    mapaVisitados[auxFilhos[i].first ][ auxFilhos[i].second] = atual;
                    if(this->dfsRercusiva(mapaVisitados , auxFilhos[i] , fim))
                        return true;
                }
            }
        }
    }


    return false;
}


std::vector<std::pair<int,int> > dfsSearch::executar(){
    // vetor que vai ter a resposta.
    std::vector<std::pair<int,int> > resp;
    // fila da bfs
    std::stack<std::pair < int , int > > stack;
    // auxiliar de posição invpalida
    std::pair<int ,int> auxNaoVisitado(-1,-1);
    // mapa que vai gerar o caminho percorrido.
    std::vector<std::vector< std::pair<int , int > > > mapaVisitados(this->map->getHeight() , std::vector<std::pair<int , int> >(this->map->getWidth() , auxNaoVisitado));
    // posição atual da busca.
    std::pair<int,int> atual(this->map->getStart());
    // coordenada do inicio
    std::pair<int , int> inicio(atual);
    // coordenada da coordenada final
    std::pair<int,int> fim(this->map->getEnd());
    // marca que o atual chegou pelo atual. para não andar de novo aqui

    mapaVisitados[atual.first][atual.second] = atual;
    this->dfsRercusiva(mapaVisitados , atual , fim);
    atual = fim;

    // cria o vetor de resposta.
    if(mapaVisitados[atual.first][atual.second] != auxNaoVisitado){
        while(atual != inicio){
            resp.push_back(atual);
            atual = mapaVisitados[atual.first][atual.second];
        }
        resp.push_back(inicio);
    }
    return resp;
}

void dfsSearch::reset() {
    this->visitados.clear();
}

