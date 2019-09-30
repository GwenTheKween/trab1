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

}

InterfaceInit::~InterfaceInit(){
    endwin();
}
