#ifndef __NCURSES__HELPERS__H__
#define __NCURSES__HELPERS__H__ value

#include <ncurses.h>

class WINDOW_desctructor {

    public:

    WINDOW_desctructor();
    void operator()(WINDOW *p);
};


#endif /* ifndef __NCURSES__HELPERS__H__ */
