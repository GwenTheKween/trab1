#include "ncurses_helpers.h"

WINDOW_desctructor::WINDOW_desctructor(){};

void WINDOW_desctructor::operator()(WINDOW *p){
    delwin(p);
}
