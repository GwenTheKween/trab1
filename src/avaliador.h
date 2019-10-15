#ifndef __AVALIADOR__H__
#define __AVALIADOR__H__ value


class Search;
class labirinto;

class avaliador {
    private:
        double tempoDecorrido(Search *busca);
    public:
        avaliador();
        ~avaliador();

        void operator()();
};



#endif /* ifndef __AVALIADOR__H__ */
