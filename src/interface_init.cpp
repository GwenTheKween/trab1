#include "interface_init.h"
#include <ncurses.h>
#include <cstdlib>

InterfaceInit::InterfaceInit(){
    initscr();
    if(has_colors() == FALSE){
        endwin();
        printf("deu ruim não tem cores aqui\n");
        exit(1);
    }
    start_color();
    // definindo algumas cores, se quiser adicionar mais cores só por no enum que está no interface_init.h
    // inicializa eles na ordem do enum, prece que da problema inicializar fora de ordem numerica, Não testei isso.
    init_pair(RED_BLACK , COLOR_RED , COLOR_BLACK);
    init_pair(BLACK_RED , COLOR_BLACK , COLOR_RED);
    init_pair(BLUE_GREEN , COLOR_BLUE , COLOR_GREEN);
    init_pair(GREEN_BLUE , COLOR_GREEN , COLOR_BLUE);
    init_pair(BLUE_BLACK , COLOR_BLUE , COLOR_BLACK);
    init_pair(GREEN_BLACK , COLOR_GREEN , COLOR_BLACK);

}

InterfaceInit::~InterfaceInit(){
    endwin();
}
