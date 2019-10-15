#include "interface_geral.h"
#include "interface_labirinto.h"
#include "labirinto.h"
#include "search.h"
#include "dfs.h"
#include "bfs.h"

#include <ncurses.h>
#include <functional>

#define MENU_LARGURA 15
#define COMANDOS_ALTURA 1


interfaceGeral::interfaceGeral(){};
interfaceGeral::~interfaceGeral(){};


void interfaceGeral::operator()(){
    // usa * para não visitado e visitado usa ponto.
    // não mudar a cor do fundo muda a cor do ponto.
    WINDOW *menu = newwin(LINES - COMANDOS_ALTURA , MENU_LARGURA , 0 , COLS - MENU_LARGURA);
    bool labirintoIsSet = false;
    std::array<std::string , 6> itens{"gera mapa" , "A*" , "bestSearch" , "BFS" , "DFS" , "Andar"};
    WINDOW *comandos = newwin(COMANDOS_ALTURA , COLS , LINES -COMANDOS_ALTURA , 0);
    labirinto *l = new labirinto(0,0);
    InterfaceLabirinto *iLab = new InterfaceLabirinto({0,0} ,LINES -COMANDOS_ALTURA , COLS -MENU_LARGURA , *l);
    auto executaLabirinto = [&] (Search *busca) -> void {
        bool para = true;
        auto caminhoFinal = busca->executar();
        auto caminhoPercorrido = busca->getSequenciaDeVisitados();
        for(auto &it : caminhoPercorrido){
            iLab->definiPosicao(it , RED_BLACK);
            iLab->refresh();
            if(para){
                wrefresh(comandos);
                para = wgetch(comandos) != 's';
            }
        }
        for(auto &it : caminhoFinal){
            iLab->definiPosicao(it , BLUE_BLACK);
            iLab->refresh();
        }
        wrefresh(comandos);
        wgetch(comandos);
    };
    auto geraLabirinto = [&] () -> void {
        int w, h;
        wprintw(comandos , "informe o tamanho do labirinto (<num> x <num>): ");
        wscanw(comandos , "%d x %d" , &w , &h);
        // aqui gera o labirinto
        delete l;
        l = new labirinto((char*) "../mapas/6.map");
        delete iLab;
        labirintoIsSet = true;
        iLab = new InterfaceLabirinto({0,0} ,LINES -1 , COLS -10 , *l);
        iLab->refresh();
    };
    auto executaA_star = [&] () -> void {
        if(labirintoIsSet){
            // fazer executar a A*
        }
    };
    auto executaBestFirstSearch = [&] () -> void {
        if(labirintoIsSet){
            // fazer executar a bestFirstSearch
        }
    };
    auto executaBFS = [&] () -> void {
        if(labirintoIsSet){
            bfsSearch bfs;
            bfs.setMap(*l);
            executaLabirinto(&bfs);
        }
    };
    auto executaDFS = [&] () -> void {
        if(labirintoIsSet){
            dfsSearch dfs;
            dfs.setMap(*l);
            executaLabirinto(&dfs);
        }
    };


    for(unsigned int i = 0 ; i < itens.size() ; i++){
        auto &str = itens[i];
        wmove(menu,(LINES -COMANDOS_ALTURA)/2-2+i , (MENU_LARGURA - str.size())/2 );
        wprintw(menu,"%s" , itens[i].c_str());
    }

    wrefresh(menu);
    wgetch(menu);
};
