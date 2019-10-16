#ifndef __AVALIADOR__H__
#define __AVALIADOR__H__ value

#include <cstdint>

class Search;
class labirinto;

class avaliador {
    private:
         uint64_t tempoDecorrido(Search *busca);
    public:
        avaliador();
        ~avaliador();

        void operator()();
};



#endif /* ifndef __AVALIADOR__H__ */
