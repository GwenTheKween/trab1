#include "interface_labirinto.h"
#include "labirinto.h"
#include "ncurses_helpers.h"



// Outline: Ele define qual caracter deve ser usado e da as caracteríticas padrão do caracter.
char InterfaceLabirinto::printaCaracter(MAP_INFO value){
    char aux = 0;
    if(value ==  FREE_SPACE){
        aux = '.';
    }else if(value == WALL){
        wattron(this->window.get() , COLOR_PAIR(BLACK_WHITE));
        aux=' ';
    }else if(value == BEGIN){
        aux = 'o';
    }else if(value == END){
        aux = 'X';
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

InterfaceLabirinto::InterfaceLabirinto(const InterfaceLabirinto &outro) : coordLeftUp(outro.coordLeftUp) , size(outro.size) , lab(outro.lab), window(newpad(lab.getHeight() , lab.getWidth()) , WINDOW_desctructor()) , actualCoord(outro.actualCoord)  {
    this->atualizarMapa();
}

//Outline: função que desenha o labirinto inteiro no pad. Começa desenhando as bordas e depois cada ponto do labirinto.
void InterfaceLabirinto::atualizarMapa(){

    // fz a borda
    wattron(this->window.get() , COLOR_PAIR(BLACK_WHITE));
    wborder(this->window.get() , ' ' , ' ', ' ', ' ', ' ', ' ' , ' ' , ' ');
    wattroff(this->window.get() , COLOR_PAIR(BLACK_WHITE));

    // printa todas as posições labirintos.
    for(int i =0 ; i < this->lab.getHeight() ; i++){
        wmove(this->window.get() , i+1 , 1);
        auto & linha = this->lab[i];
        for(int j = 0 ; j < this->lab.getWidth() ; j++){
            //attron(COLOR_PAIR(1));
            this->printaCaracter(linha[j]);
            if(linha[j] == BEGIN){
                this->actualCoord = std::make_pair(j+1 , i+1);
            }
        }
    }


    wgetch(this->window.get());
}

// Outline: Define a posição atual do labirinto. E printa o caracter, não atualiza a tela, necessário chamar
// InterfaceLabirinto::refresh().
void InterfaceLabirinto::definiPosicao(int y , int x  ,COLOR_MAPS color ){
    wattron(this->window.get() , COLOR_PAIR(color));
    wmove(this->window.get() , y+1 ,x+1);
    this->actualCoord.first = x;
    this->actualCoord.second = y;
    this->printaCaracter(this->lab[y][x]);
    wgetch(this->window.get());
}

//Outline: define a parte da tela que via ser mostrada tentando manter a posição atual no centro da tela,
//definindo qual posição do labirinto vai ficar no canto
//superior esquerdo da janela, depois disso só define os outros pontos apartir do tamanho da janela em
//que vai ser exibido o labirinto.
void InterfaceLabirinto::refresh() {
    // variaveis que são usadas para  centralizar a posição atual.
    int mh = this->size.second / 2;
    int mw = this->size.first / 2;
    int cornerLeUpY = 0;
    int cornerLeUpX = 0;
    // aqui faz a verificação se na coordenada x atual está num ponto ond enão é possível centralizar porque
    // ele está muito proximo da origem, e depois verifica se está muito proximo do fim do labirinto
    if((this->lab.getWidth()+2 > this->size.first) && (this->actualCoord.first - mw > 0)){//verificação se está no inicio
        cornerLeUpX = this->actualCoord.first - mw;
        if((cornerLeUpX + this->size.first ) > (this->lab.getWidth()+2)){ // verificação se está no final.
            cornerLeUpX = this->lab.getWidth() - this->size.first + 2;
        }
    }
    // repete a mesma coisa da coordenada x só que para y.
    if( (this->lab.getHeight()+2 > this->size.second) && (this->actualCoord.second - mh > 0) ){
        cornerLeUpY = this->actualCoord.second - mh;
        if((cornerLeUpY + this->size.second) > (this->lab.getHeight() + 2)){
            cornerLeUpY -= this->lab.getHeight() - this->size.second + 2;
        }
    }
    // faz a atualização do pad para escrever na janela.
    prefresh(this->window.get() , cornerLeUpY , cornerLeUpX , this->coordLeftUp.second , this->coordLeftUp.first , this->coordLeftUp.second + this->size.second  -1, this->coordLeftUp.first + this->size.first - 1);
}
