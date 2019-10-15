#include "interface_geral.h"
#include "interface_labirinto.h"

#include <ncurses.h>
#include <functional>
#include "labirinto.h"


interfaceGeral::interfaceGeral(){};
interfaceGeral::~interfaceGeral(){};


void interfaceGeral::operator()(){
    WINDOW *menu = newwin(LINES , 10 , 0 , COLS - 10);
    bool labirintoIsSet = false;
    WINDOW *comandos = newwin(1 , COLS , LINES -1 , 0);
    labirinto *l = new labirinto(0,0);
    InterfaceLabirinto *iLab = new InterfaceLabirinto({0,0} ,LINES -1 , COLS -10 , *l);
    //auto executaLabirinto = [&] (Search *
    auto geraLabirinto = [&] () -> void {
        int w, h;
        wprintw(comandos , "informe o tamanho do labirinto (<num> x <num>): ");
        wscanw(comandos , "%d x %d" , &w , &h);
        // aqui gera o labirinto
        delete l;
        l = new labirinto((char*) "../mapas/1.map");
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
    auto executaBestFiestSearch = [&] () -> void {
        if(labirintoIsSet){
            // fazer executar a bestFirstSearch
        }
    };
    auto executaBFS = [&] () -> void {
        if(labirintoIsSet){
        }
    };
    auto executaDFS = [&] () -> void {
        if(labirintoIsSet){
        }
    };

    wgetch(comandos);





};
