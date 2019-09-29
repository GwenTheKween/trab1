#include "interface_geral.h"
#include <ncurses.h>

InterfaceGeral::InterfaceGeral(){
    initscr();
    if(has_colors() == TRUE){
        start_color();
    }

}

InterfaceGeral::~InterfaceGeral(){
    endwin();
}
