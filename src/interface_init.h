#ifndef __INTERFACE_GERAL__H__
#define __INTERFACE_GERAL__H__ value

// classe que vai cuidar da inicialização do ncurses.

enum COLOR_MAPS{
    DEFAULT,
    RED_BLACK,
    BLACK_RED,
    BLUE_GREEN,
    GREEN_BLUE,
    BLUE_BLACK,
    GREEN_BLACK
};

class InterfaceInit{
    public:

    InterfaceInit();
    ~InterfaceInit();
};

#endif /* ifndef __INTERFACE_GERAL__H__ */
