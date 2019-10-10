#ifndef __INTERFACE__LABIRINTO_H__
#define __INTERFACE__LABIRINTO_H__ value

#include <memory>
#include <ncurses.h>
#include "ncurses_helpers.h"
#include "labirinto.h"
#include "interface_init.h"

// Classe que encapsula a interface que irá mostrar o labirinto.

class InterfaceLabirinto {
    // esse argumento é para especificar a posição do canto superior esquerdo do labirinto, as coordenada
    // está na forma (x,y).
    std::pair<int, int> coordLeftUp;
    // esse é para especificar o tamanho da janela, Está na forma (width,height).
    std::pair<int, int> size;
    // esse armazena o labirinto que está sendo mostrado.
    labirinto &lab;
    // esse daqui é a janela do ncurses. É utilizado o pad que permite janelas maiores do que a tela
    // dessa forma pode desenhar um labirinto maior que a tela e especificar a parte que vai ser mostrado.
    std::unique_ptr<WINDOW , WINDOW_desctructor> window;
    
    // marca a posição atual no labirinto,(x,y).
    std::pair<int , int > actualCoord;

    private:

    //função que cuida de printar o caracter.
    char printaCaracter(MAP_INFO value);

    public:

    /* construtor da interface do labirinto, precisa da posição em que o labirinto vai ser posicionado e do tamanho da tela
     * em que ele vai estar, mais o labirinto que ele vai mostrar.
     *
     * Argumentos:
     *  leftUpX -> coordenada x onde vai ficar o canto superior esquerdo da interface.
     *  leftUpY -> coordenada y onde via ficar o canto superior esquerdo da interface.
     *  height  -> altura da tela.
     *  width   -> largura da tela.
     *  lab     -> labirinto que vai ser mostrado.
     */
    InterfaceLabirinto(int leftUpX, int leftUpY   , int height , int width , labirinto &lab);

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
     *  y       -> posição y atual do labirinto.
     *  x       -> posição x atual do labirinto.
     *  color   -> cor em que vai ser pintado a posição atual.
     */
    void definiPosicao(int y , int x , COLOR_MAPS color);

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
