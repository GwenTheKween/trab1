#ifndef __INTERFACE__LABIRINTO_H__
#define __INTERFACE__LABIRINTO_H__ value

#include <memory>
#include <ncurses.h>

class labirinto;

class InterfaceLabirinto {
    // esse argumento é para especificar a posição do labirinto na tela.
    std::pair<int, int> coordLeftUp;
    // esse é para especificar o tamanho da janela.
    std::pair<int, int> size;
    // esse armazena o labirinto que está sendo mostrado.
    labirinto &lab;
    // esse daqui é a janela do ncurses.
    std::unique_ptr<WINDOW> window;


    public:

    InterfaceLabirinto(int leftUpX, int leftUpY   , int height , int width , labirinto &lab);
    InterfaceLabirinto(const InterfaceLabirinto& outro);
    ~InterfaceLabirinto();

    void definiPosição(int y , int x);




};


#endif /* ifndef __INTERFACE__LABIRINTO_H__ */
