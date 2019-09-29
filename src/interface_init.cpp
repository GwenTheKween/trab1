#include "interface_init.h"
#include <ncurses.h>

InterfaceInit::InterfaceInit(){
    initscr();
    if(has_colors() == TRUE){
        start_color();
    }

}

InterfaceInit::~InterfaceInit(){
    endwin();
}
