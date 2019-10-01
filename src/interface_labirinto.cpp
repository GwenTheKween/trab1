#include "interface_labirinto.h"
#include "interface_init.h"
#include "labirinto.h"
#include "ncurses_helpers.h"


char InterfaceLabirinto::printaCaracter(MAP_INFO value){
    char aux = 0;
    if(value ==  FREE_SPACE){
        aux = '.';
    }else if(value == WALL){
        wattron(this->window.get() , COLOR_PAIR(BLACK_WHITE));
        aux=' ';
    }else if(value == BEGIN){
        aux = 'o'; // alterar esse daqui depois para alguma cor
    }else if(value == END){
        aux = 'X'; // ese daqui também dar alguma cor
    }
    wprintw(this->window.get() , "%c" , aux);
    wstandend( this->window.get());
    return aux;
}


InterfaceLabirinto::InterfaceLabirinto(int leftUpX, int leftUpY   , int height , int width , labirinto &lab) : coordLeftUp(leftUpX , leftUpY) , size(width , height) , lab(lab), window(newpad(lab.getHeight() + 2 , lab.getWidth() + 2) , WINDOW_desctructor()) {
    this->atualizarMapa();
}

InterfaceLabirinto::~InterfaceLabirinto(){
}

InterfaceLabirinto::InterfaceLabirinto(const InterfaceLabirinto &outro) : coordLeftUp(outro.coordLeftUp) , size(outro.size) , lab(outro.lab), window(newpad(lab.getHeight() , lab.getWidth()) , WINDOW_desctructor())  {
    this->atualizarMapa();
}

void InterfaceLabirinto::atualizarMapa(){

    for(int i =0 ; i < this->lab.getHeight() ; i++){
        wmove(this->window.get() , i+1 , 1);
        auto & linha = this->lab[i];
        for(int j = 0 ; j < this->lab.getWidth() ; j++){
            //attron(COLOR_PAIR(1));
            this->printaCaracter(linha[j]);
        }
    }
    prefresh(this->window.get() , this->coordLeftUp.second ,this->coordLeftUp.first , 0 , 0 , this->size.second , this->size.first);
    wgetch(this->window.get());
}

void InterfaceLabirinto::definiPosicao(int y , int x ){
}
