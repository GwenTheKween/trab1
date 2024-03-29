#include "interface_labirinto.h"
#include "labirinto.h"
#include "ncurses_helpers.h"



// Outline: Ele define qual caracter deve ser usado e da as caracteríticas padrão do caracter.
char InterfaceLabirinto::printaCaracter(MAP_INFO value , bool visitado ){
    char aux = 0;
    if(value ==  FREE_SPACE){
        if(visitado){
            aux = '.';
        }else{
            aux = '*';
        }
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



InterfaceLabirinto::InterfaceLabirinto(std::pair<int,int> coordLeftUp  , int height , int width , labirinto &lab) : coordLeftUp(coordLeftUp) , size(height , width) , lab(lab), window(newpad(lab.getHeight() + 2 , lab.getWidth() + 2) , WINDOW_desctructor()) {
    keypad(this->window.get() , TRUE);
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
        auto linha = this->lab[i];
        for(int j = 0 ; j < this->lab.getWidth() ; j++){
            //attron(COLOR_PAIR(1));
            this->printaCaracter(linha[j]);
            if(linha[j] == BEGIN){
                this->actualCoord = std::make_pair(i , j);
            }
        }
    }
}

// Outline: Define a posição atual do labirinto. E printa o caracter, não atualiza a tela, necessário chamar
// InterfaceLabirinto::refresh().
void InterfaceLabirinto::definiPosicao(std::pair<int,int> coord , COLOR_MAPS color , bool visitado){
    wattron(this->window.get() , COLOR_PAIR(color));
    wmove(this->window.get() , coord.first+1 ,coord.second+1);
    this->actualCoord.first = coord.first;
    this->actualCoord.second = coord.second;
    this->printaCaracter(this->lab[coord.first][coord.second] , visitado);
}

//Outline: define a parte da tela que via ser mostrada tentando manter a posição atual no centro da tela,
//definindo qual posição do labirinto vai ficar no canto
//superior esquerdo da janela, depois disso só define os outros pontos apartir do tamanho da janela em
//que vai ser exibido o labirinto.
void InterfaceLabirinto::refresh() {
    // variaveis que são usadas para  centralizar a posição atual.
    int mh = this->size.first / 2;
    int mw = this->size.second / 2;
    int cornerLeUpY = 0;
    int cornerLeUpX = 0;
    // aqui faz a verificação se na coordenada x atual está num ponto ond enão é possível centralizar porque
    // ele está muito proximo da origem, e depois verifica se está muito proximo do fim do labirinto
    if((this->lab.getWidth()+2 > this->size.second) && (this->actualCoord.second - mw > 0)){//verificação se está no inicio
        cornerLeUpX = this->actualCoord.first - mw;
        if((cornerLeUpX + this->size.second ) > (this->lab.getWidth()+2)){ // verificação se está no final.
            cornerLeUpX = this->lab.getWidth() - this->size.second + 2;
        }
    }
    // repete a mesma coisa da coordenada x só que para y.
    if( (this->lab.getHeight()+2 > this->size.first) && (this->actualCoord.first - mh > 0) ){
        cornerLeUpY = this->actualCoord.first - mh;
        if((cornerLeUpY + this->size.first) > (this->lab.getHeight() + 2)){
            cornerLeUpY = this->lab.getHeight() - this->size.first + 2;
        }
    }
    // faz a atualização do pad para escrever na janela.
    prefresh(this->window.get() , cornerLeUpY , cornerLeUpX , this->coordLeftUp.first , this->coordLeftUp.second , this->coordLeftUp.first + this->size.first  -1, this->coordLeftUp.second + this->size.second - 1);
}


void InterfaceLabirinto::andarPeloLabirinto(){
    int cornerLeUpY = 0;
    int cornerLeUpX = 0;

    {
        int mh = this->size.first / 2;
        int mw = this->size.second / 2;
        if((this->lab.getWidth()+2 > this->size.second) && (this->actualCoord.second - mw > 0)){//verificação se está no inicio
            cornerLeUpX = this->actualCoord.first - mw;
            if((cornerLeUpX + this->size.second ) > (this->lab.getWidth()+2)){ // verificação se está no final.
                cornerLeUpX = this->lab.getWidth() - this->size.second + 2;
            }
        }
        if( (this->lab.getHeight()+2 > this->size.first) && (this->actualCoord.first - mh > 0) ){
            cornerLeUpY = this->actualCoord.first - mh;
            if((cornerLeUpY + this->size.first) > (this->lab.getHeight() + 2)){
                cornerLeUpY = this->lab.getHeight() - this->size.first + 2;
            }
        }
    }
    int caracter = 0;
    while(caracter != 27){
        caracter = wgetch(this->window.get());
        if(KEY_LEFT == caracter){
            if(cornerLeUpX > 0)
                cornerLeUpX--;
        }else if(KEY_DOWN == caracter){
            if(cornerLeUpY < this->lab.getHeight() - this->size.first +2)
                cornerLeUpY++;
        }else if(KEY_UP == caracter){
            if(cornerLeUpY > 0)
                cornerLeUpY--;
        }else if(KEY_RIGHT == caracter){
            if(cornerLeUpX < this->lab.getWidth()-this->size.second +2)
                cornerLeUpX++;
        }
        prefresh(this->window.get() , cornerLeUpY , cornerLeUpX , this->coordLeftUp.first , this->coordLeftUp.second , this->coordLeftUp.first + this->size.first  -1, this->coordLeftUp.second + this->size.second - 1);
    }
}

void InterfaceLabirinto::reset(){
    this->atualizarMapa();
}
