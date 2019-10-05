#include "interface_labirinto.h"
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

InterfaceLabirinto::InterfaceLabirinto(const InterfaceLabirinto &outro) : coordLeftUp(outro.coordLeftUp) , size(outro.size) , lab(outro.lab), window(newpad(lab.getHeight() , lab.getWidth()) , WINDOW_desctructor()) , coordLast(outro.coordLast)  {
    this->atualizarMapa();
}

void InterfaceLabirinto::atualizarMapa(){

    wattron(this->window.get() , COLOR_PAIR(BLACK_WHITE));
    wborder(this->window.get() , ' ' , ' ', ' ', ' ', ' ', ' ' , ' ' , ' ');
    wattroff(this->window.get() , COLOR_PAIR(BLACK_WHITE));

    for(int i =0 ; i < this->lab.getHeight() ; i++){
        wmove(this->window.get() , i+1 , 1);
        auto & linha = this->lab[i];
        for(int j = 0 ; j < this->lab.getWidth() ; j++){
            //attron(COLOR_PAIR(1));
            this->printaCaracter(linha[j]);
            if(linha[j] == BEGIN){
                this->coordLast = std::make_pair(j+1 , i+1);
            }
        }
    }


    this->refresh();
    wgetch(this->window.get());
}

void InterfaceLabirinto::definiPosicao(int y , int x  ,COLOR_MAPS color ){
    wattron(this->window.get() , COLOR_PAIR(color));
    wmove(this->window.get() , y+1 ,x+1);
    this->coordLast.first = x;
    this->coordLast.second = y;
    this->printaCaracter(this->lab[y][x]);
    this->refresh();
    wgetch(this->window.get());
}

void InterfaceLabirinto::refresh() {
    int mh = this->size.second / 2;
    int mw = this->size.first / 2;
    int cornerLeUpY = 0;
    int cornerLeUpX = 0;
    if((this->lab.getWidth()+2 > this->size.first) && (this->coordLast.first - mw > 0)){
        cornerLeUpX = this->coordLast.first - mw;
        if((cornerLeUpX + this->size.first ) > (this->lab.getWidth()+2)){
            cornerLeUpX = this->lab.getWidth() - this->size.first + 2;
        }
    }
    if( (this->lab.getHeight()+2 > this->size.second) && (this->coordLast.second - mh > 0) ){
        cornerLeUpY = this->coordLast.second - mh;
        if((cornerLeUpY + this->size.second) > (this->lab.getHeight() + 2)){
            cornerLeUpY -= this->lab.getHeight() - this->size.second + 2;
        }
    }
    prefresh(this->window.get() , cornerLeUpY , cornerLeUpX , this->coordLeftUp.second , this->coordLeftUp.first , this->coordLeftUp.second + this->size.second  -1, this->coordLeftUp.first + this->size.first - 1);
}
