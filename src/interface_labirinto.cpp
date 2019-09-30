#include "interface_labirinto.h"
#include "labirinto.h"
#include "ncurses_helpers.h"


InterfaceLabirinto::InterfaceLabirinto(int leftUpX, int leftUpY   , int height , int width , labirinto &lab) : coordLeftUp(leftUpX , leftUpY) , size(width , height) , lab(lab), window(newpad(lab.getHeight() , lab.getWidth()) , WINDOW_desctructor()) {

    for(int i =0 ; i < this->lab.getHeight() ; i++){
        wmove(this->window.get() , i , 0);
        auto & linha = this->lab[i];
        for(int j = 0 ; j < this->lab.getWidth() ; j++){
            //attron(COLOR_PAIR(1));
            char aux = 0;
            if(linha[j] ==  FREE_SPACE){
                aux = '*';
            }else if(linha[j] == WALL){
                aux=' ';
            }else if(linha[j] == BEGIN){
                aux = 'o'; // alterar esse daqui depois para alguma cor
            }else if(linha[j] == END){
                aux = 'X'; // ese daqui também dar alguma cor
            }
            wprintw(this->window.get(), "%c" , aux);
        }
    }
    prefresh(this->window.get() ,0 , 0 , leftUpY , leftUpX, leftUpY + height , leftUpX + width );
    wgetch(this->window.get());
}

InterfaceLabirinto::~InterfaceLabirinto(){
}


