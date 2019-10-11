#ifndef __INTERFACE__LABIRINTO_H__
#define __INTERFACE__LABIRINTO_H__ value

#include <memory>
#include <ncurses.h>
#include "ncurses_helpers.h"
#include "labirinto.h"
#include "interface_init.h"

// Classe que encapsula a interface que irá mostrar o labirinto.


// as coordenadas dessa classe estão todas no formato (y,x), onde y representa a linha e x a coluna.

class InterfaceLabirinto {
    // esse argumento é para especificar a posição do canto superior esquerdo do labirinto, as coordenada
    // está na forma (y,x).
    std::pair<int, int> coordLeftUp;
    // esse é para especificar o tamanho da janela, Está na forma (height,width).
    std::pair<int, int> size;
    // esse armazena o labirinto que está sendo mostrado.
    labirinto &lab;
    // esse daqui é a janela do ncurses. É utilizado o pad que permite janelas maiores do que a tela
    // dessa forma pode desenhar um labirinto maior que a tela e especificar a parte que vai ser mostrado.
    std::unique_ptr<WINDOW , WINDOW_desctructor> window;

    // marca a posição atual no labirinto,(y,x).
    std::pair<int , int > actualCoord;

    private:

    //função que cuida de printar o caracter.
    char printaCaracter(MAP_INFO value);

    public:

    /* construtor da interface do labirinto, precisa da posição em que o labirinto vai ser posicionado e do tamanho da tela
     * em que ele vai estar, mais o labirinto que ele vai mostrar.
     *
     * Argumentos:
     *  coordLeftUp -> coordenada do canto superior esquerdo da interface (y,x).
     *  height      -> altura da tela.
     *  width       -> largura da tela.
     *  lab         -> labirinto que vai ser mostrado.
     */
    InterfaceLabirinto( std::pair<int,int> coordLeftUp   , int height , int width , labirinto &lab);

    /*
     * Construtor que faz a copia da interface. Ele cria uma nova janela.
     */
    InterfaceLabirinto(const InterfaceLabirinto& outro);

    // destrutor
    ~InterfaceLabirinto();

    /*
     * Função que define a posição atual do labirinto
     *
     * Argumentos:
     *  coord   -> coordenada da nova posição atual é uma coordenada na seguinte ordem (y,x).
     *  color   -> cor em que vai ser pintado a posição atual.
     */
    void definiPosicao(std::pair<int,int> coord , COLOR_MAPS color);

    /*
     * Função para rescrever o mapa inteiro. (não marca os lugares visitados).
     */
    void atualizarMapa();

    /*
     * Função para escrever o labirinto na tela de verdade.
     */
    void refresh();




};


#endif /* ifndef __INTERFACE__LABIRINTO_H__ */
