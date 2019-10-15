#ifndef __DFS__H__
#define __DFS__H__ value

#include "search.h"
#include "labirinto.h"

class dfsSearch : public Search{
    labirinto *map;
    std::deque<std::pair< int , int > > visitados;

    private:
        bool dfsRercusiva( std::vector<std::vector< std::pair<int , int > > > &mapaVisitados , std::pair<int , int> atual , std::pair< int ,int > &fim);

    public:

        dfsSearch();
        ~dfsSearch();

        void setMap(labirinto &map);

        const std::deque<std::pair<int,int> > &getSequenciaDeVisitados() const;

        std::vector<std::pair<int,int> > executar();

        void reset();
};


#endif /* ifndef __DFS__H__ */
