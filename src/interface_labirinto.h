#ifndef __INTERFACE__LABIRINTO_H__
#define __INTERFACE__LABIRINTO_H__ value

#include <memory>
#include <ncurses.h>
#include "ncurses_helpers.h"
#include "labirinto.h"


class InterfaceLabirinto {
    // esse argumento é para especificar a posição do labirinto na tela.
    std::pair<int, int> coordLeftUp;
    // esse é para especificar o tamanho da janela.
    std::pair<int, int> size;
    // esse armazena o labirinto que está sendo mostrado.
    labirinto &lab;
    // esse daqui é a janela do ncurses.
    std::unique_ptr<WINDOW , WINDOW_desctructor> window;

    private:

    char printaCaracter(MAP_INFO value);

    public:

    InterfaceLabirinto(int leftUpX, int leftUpY   , int height , int width , labirinto &lab);
    InterfaceLabirinto(const InterfaceLabirinto& outro);
    ~InterfaceLabirinto();

    void definiPosicao(int y , int x);

    void atualizarMapa();




};


#endif /* ifndef __INTERFACE__LABIRINTO_H__ */
